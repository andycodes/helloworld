
#include "base_type.h"

//  Memory Pool Header structure
typedef struct mem_head_s {
  uint32_t size;                // Memory Pool size
  uint32_t used;                // Used Memory
} mem_head_t;

//  Memory Block Header structure
typedef struct mem_block_s {
  struct mem_block_s *next;     // Next Memory Block in list
  uint32_t            info;
} mem_block_t;

#define MB_INFO_LEN_MASK        0xFFFFFFFCU
#define MB_INFO_TYPE_MASK       0x00000003U


void * g_mem_phy_addr	= NULL;


//  ==== Library functions ====

/// Initialize Memory Pool with variable block size.
/// \param[in]  mem             pointer to memory pool.
/// \param[in]  size            size of a memory pool in bytes.
/// \return 1 - success, 0 - failure.
__WEAK uint32_t osRtxMemoryInit (void *mem, uint32_t size)
{
	mem_head_t  *head;
	mem_block_t *ptr;

	if ((mem == NULL) || ((U64)mem & 7U) || (size & 7U) ||
	(size < (sizeof(mem_head_t) + 2*sizeof(mem_block_t)))) {
		return 0U;
	}

	head = (mem_head_t *)mem;
	head->size = size;
	head->used = sizeof(mem_head_t) + sizeof(mem_block_t);

	ptr = (mem_block_t *)((U64)mem + sizeof(mem_head_t));
	ptr->next = (mem_block_t *)((U64)mem + size - sizeof(mem_block_t));
	ptr->next->next = NULL;
	ptr->info = 0U;

	g_mem_phy_addr = mem;

	return 1U;
}

/// Allocate a memory block from a Memory Pool.
/// \param[in]  mem             pointer to memory pool.
/// \param[in]  size            size of a memory block in bytes.
/// \return allocated memory block or NULL in case of no memory is available.
__WEAK void *akmem_alloc (uint32_t size) {
  mem_block_t *p, *p_new, *ptr;
  uint32_t     hole_size;

  if ((g_mem_phy_addr == NULL) || (size == 0U) ) {
    return NULL;
  }

  // Add header to size
  size += sizeof(mem_block_t);
  // Make sure that block is 8-byte aligned
  size = (size + 7U) & ~((uint32_t)7U);

  // Search for hole big enough
  p = (mem_block_t *)((U64)g_mem_phy_addr + sizeof(mem_head_t));
  for (;;) {
    hole_size  = (U64)p->next - (U64)p;
    hole_size -= p->info & MB_INFO_LEN_MASK; /*Info: length = <31:2>:'00', type = <1:0>*/
    if (hole_size >= size) {
      // Hole found
      break;
    }
    p = p->next;
    if (p->next == NULL) {
      // Failed (end of list)
      return NULL;
    }
  }

  ((mem_head_t *)g_mem_phy_addr)->used += size;

  if (p->info == 0U) {
    // No block allocated, set info of first element
    p->info = size;
    ptr = (mem_block_t *)((U64)p + sizeof(mem_block_t));
  } else {
    // Insert new element into the list
    p_new = (mem_block_t *)((U64)p + (p->info & MB_INFO_LEN_MASK));
    p_new->next = p->next;
    p_new->info = size;
    p->next = p_new;
    ptr = (mem_block_t *)((U64)p_new + sizeof(mem_block_t));
  }


  return ptr;
}

/// Return an allocated memory block back to a Memory Pool.
/// \param[in]  mem             pointer to memory pool.
/// \param[in]  block           memory block to be returned to the memory pool.
/// \return 1 - success, 0 - failure.
__WEAK uint32_t akmem_free (void *block) {
  mem_block_t *p, *p_prev, *ptr;

  if ((g_mem_phy_addr == NULL) || (block == NULL)) {
    return 0U;
  }

  ptr = (mem_block_t *)((U64)block - sizeof(mem_block_t));

  // Search for header
  p_prev = NULL;
  p = (mem_block_t *)((U64)g_mem_phy_addr + sizeof(mem_head_t));
  while (p != ptr) {
    p_prev = p;
    p = p->next;
    if (p == NULL) {
      // Not found
      return 0U;
    }
  }

  ((mem_head_t *)g_mem_phy_addr)->used -= p->info & MB_INFO_LEN_MASK;

  if (p_prev == NULL) {
    // Release first block, only set info to 0
    p->info = 0U;
  } else {
    // Discard block from chained list
    p_prev->next = p->next;
  }


  return 1U;
}
