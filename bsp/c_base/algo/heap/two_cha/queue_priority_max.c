#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct key_value_struct KeyValue;
struct key_value_struct
{
      int key;
      void *value;
};
KeyValue *key_value_new(int key, void *value);
void key_value_free(KeyValue *kv, void (*freevalue)(void *));

#define PRIORITY_MAX 1
#define PRIORITY_MIN 2
typedef struct priority_queue_struct PriorityQueue;
struct priority_queue_struct
{
      KeyValue **node;
      int cnt;
      int capacity;

      int priority;
};
static void priority_queue_realloc(PriorityQueue *pq);

static void priority_queue_adjust_head(PriorityQueue *pq);

static void priority_queue_adjust_tail(PriorityQueue *pq);

static int priority_queue_compare(PriorityQueue *pq,
                                                  int pos1,
                                                  int pos2);
static void priority_queue_swap(KeyValue **nodes,
                                                int pos1,
                                                int pos2);

KeyValue *key_value_new(int key, void *value)
{
      KeyValue *pkv = (KeyValue *)malloc(sizeof(KeyValue));
      pkv->key = key;
      pkv->value = value;
      return pkv;
}

void key_value_free(KeyValue *kv, void (*freevalue)(void *))
{
      if(kv) {
            if(freevalue) {
                  freevalue(kv->value);
            }
            free(kv);
      }
}


PriorityQueue *priority_queue_init(int priority, int maxSize)
{
      PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
      pq->capacity = maxSize;
      pq->cnt = 0;
      pq->priority = priority;
      pq->node = (KeyValue **)malloc(sizeof(KeyValue *) * pq->capacity);
      return pq;
}

void priority_queue_free(PriorityQueue *pq, void (*freevalue)(void *))
{
      int i;
      if(pq) {
            for(i = 0; i < pq->cnt; ++i)
                  key_value_free(pq->node[i], freevalue);
            free(pq->node);
            free(pq);
      }
}

const KeyValue *priority_queue_top(PriorityQueue *pq)
{
      if(pq->cnt > 0)
            return pq->node[0];
      return NULL;
}

KeyValue *priority_queue_pop(PriorityQueue *pq)
{
      KeyValue *pkv = NULL;
      if(pq->cnt > 0) {
            pkv = pq->node[0];
            priority_queue_adjust_head(pq);
      }
      return pkv;
}

void priority_queue_push(PriorityQueue *pq, KeyValue *kv)
{
      printf("add key:%d\n", kv->key);
      pq->node[pq->cnt] = kv;
      priority_queue_adjust_tail(pq);
      if(pq->cnt >= pq->capacity)
            priority_queue_realloc(pq);
}

int priority_queue_size(PriorityQueue *pq)
{
      return pq->cnt;
}

int priority_queue_empty(PriorityQueue *pq)
{
      return pq->cnt <= 0;
}

void priority_queue_print(PriorityQueue *pq)
{
      int i;
      KeyValue *kv;
      printf("data in the pq->node\n");
      for(i = 0; i < pq->cnt; ++i)
            printf("%d ", pq->node[i]->key);
      printf("\n");

      printf("dequeue all data\n");
      while(!priority_queue_empty(pq)) {
            kv = priority_queue_pop(pq);
            printf("%d ", kv->key);
      }
      printf("\n");
}

static void priority_queue_realloc(PriorityQueue *pq)
{
      pq->capacity = pq->capacity * 2;
      pq->node = realloc(pq->node, sizeof(KeyValue *) * pq->capacity);
}

static void priority_queue_adjust_head(PriorityQueue *pq)
{
      int i, j, parent, left, right;

      i = 0, j = 0;
      parent = left = right = 0;
      priority_queue_swap(pq->node, 0, pq->cnt - 1);
      pq->cnt--;
      while(i < (pq->cnt - 1) / 2) {
            parent = i;

            left = i * 2 + 1;
            right = left + 1;
            j = left;
            if(priority_queue_compare(pq, left, right) > 0)
                  j++;
            if(priority_queue_compare(pq, parent, j) > 0) {
                  priority_queue_swap(pq->node, i, j);
                  i = j;
            }
            else
                  break;

      }

}

static void priority_queue_adjust_tail(PriorityQueue *pq)
{
      int i, parent, child;

      i = pq->cnt - 1;
      pq->cnt++;
      while(i > 0) {
            child = i;
            parent = (child - 1) / 2;

            if(priority_queue_compare(pq, parent, child) > 0) {
                  priority_queue_swap(pq->node, child, parent);
                  i = parent;
            }
            else
                  break;

      }
}


static int priority_queue_compare(PriorityQueue *pq,
                                                  int pos1,
                                                  int pos2)
{
      int adjust = -1;
      int r = pq->node[pos1]->key - pq->node[pos2]->key;
      if(pq->priority == PRIORITY_MAX)
            r *= adjust;
      return r;
}

static void priority_queue_swap(KeyValue **nodes,
                                                int pos1,
                                                int pos2)
{
      KeyValue *temp = nodes[pos1];
      nodes[pos1] = nodes[pos2];
      nodes[pos2] = temp;
}


int main(int argc, char **argv)
{
      int i;
      PriorityQueue *pq = priority_queue_init(PRIORITY_MAX, 20);


      int a[]={1, 9, 7, 8, 5, 4, 3, 2, 1, 100, 50, 17};

      for(i = 0; i < sizeof(a)/ sizeof(int); ++i)
      {
            KeyValue *kv = key_value_new(a[i], NULL);
            priority_queue_push(pq, kv);
      }

      priority_queue_print(pq);
      priority_queue_free(pq, NULL);
      return 0;
}
