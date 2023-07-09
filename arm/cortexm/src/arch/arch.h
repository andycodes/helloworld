#ifndef __ARCH_H__
#define __ARCH_H__

#if defined (CORTEX_M7)
  #include "core_cm7.h"
#elif defined (CORTEX_M4)
  #include "core_cm4.h"
#elif defined (CORTEX_M3)
  #include "ARMCM3.h"
  #include "core_cm3.h"
  #define NVIC_PENDSV_PRI     0x000000FF
#elif defined (CORTEX_M55)
  #include "ARMCM55.h"
  #include "core_cm55.h"
  #define NVIC_PENDSV_PRI     0x000000FF
#else
  #error "Processor not specified or unsupported."
#endif

#endif /*__ARCH_H__*/
