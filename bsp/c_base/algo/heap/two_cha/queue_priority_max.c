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
      KeyValue **_nodes;
      int _size;
      int _capacity;

      int _priority;
};
PriorityQueue *priority_queue_new(int priority);
void priority_queue_free(PriorityQueue *pq, void (*freevalue)(void *));
const KeyValue *priority_queue_top(PriorityQueue *pq);
KeyValue *priority_queue_dequeue(PriorityQueue *pq);
void priority_queue_enqueue(PriorityQueue *pq, KeyValue *kv);
int priority_queue_size(PriorityQueue *pq);
int priority_queue_empty(PriorityQueue *pq);
void priority_queue_print(PriorityQueue *pq);



//Private Functions
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
void key_value_free(KeyValue *kv,
                              void (*freevalue)(void *))
{
      if(kv)
      {
            if(freevalue)
            {
                  freevalue(kv->value);
            }
            free(kv);
      }
}


//Functions of PriorityQueue Struct
PriorityQueue *priority_queue_new(int priority)
{
      PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
      pq->_capacity = 11; //default initial value
      pq->_size = 0;
      pq->_priority = priority;

      pq->_nodes = (KeyValue **)malloc(sizeof(KeyValue *) * pq->_capacity);
      return pq;
}

void priority_queue_free(PriorityQueue *pq,
                                     void (*freevalue)(void *))
{
      int i;
      if(pq)
      {
            for(i = 0; i < pq->_size; ++i)
                  key_value_free(pq->_nodes[i], freevalue);
            free(pq->_nodes);
            free(pq);
      }
}

const KeyValue *priority_queue_top(PriorityQueue *pq)
{
      if(pq->_size > 0)
            return pq->_nodes[0];
      return NULL;
}

KeyValue *priority_queue_dequeue(PriorityQueue *pq)
{
      KeyValue *pkv = NULL;
      if(pq->_size > 0)
      {
            pkv = pq->_nodes[0];
            priority_queue_adjust_head(pq);
      }
      return pkv;
}

void priority_queue_enqueue(PriorityQueue *pq,
                                          KeyValue *kv)
{
      printf("add key:%d\n", kv->key);
      pq->_nodes[pq->_size] = kv;
      priority_queue_adjust_tail(pq);
      if(pq->_size >= pq->_capacity)
            priority_queue_realloc(pq);
}

int priority_queue_size(PriorityQueue *pq)
{
      return pq->_size;
}

int priority_queue_empty(PriorityQueue *pq)
{
      return pq->_size <= 0;
}

void priority_queue_print(PriorityQueue *pq)
{
      int i;
      KeyValue *kv;
      printf("data in the pq->_nodes\n");
      for(i = 0; i < pq->_size; ++i)
            printf("%d ", pq->_nodes[i]->key);
      printf("\n");

      printf("dequeue all data\n");
      while(!priority_queue_empty(pq))
      {
            kv = priority_queue_dequeue(pq);
            printf("%d ", kv->key);
      }
      printf("\n");
}

static void priority_queue_realloc(PriorityQueue *pq)
{
      pq->_capacity = pq->_capacity * 2;
      pq->_nodes = realloc(pq->_nodes, sizeof(KeyValue *) * pq->_capacity);
}

static void priority_queue_adjust_head(PriorityQueue *pq)
{
      int i, j, parent, left, right;

      i = 0, j = 0;
      parent = left = right = 0;
      priority_queue_swap(pq->_nodes, 0, pq->_size - 1);
      pq->_size--;
      while(i < (pq->_size - 1) / 2)
      {
            parent = i;

            left = i * 2 + 1;
            right = left + 1;
            j = left;
            if(priority_queue_compare(pq, left, right) > 0)
                  j++;
            if(priority_queue_compare(pq, parent, j) > 0)
            {
                  priority_queue_swap(pq->_nodes, i, j);
                  i = j;
            }
            else
                  break;

      }

}

static void priority_queue_adjust_tail(PriorityQueue *pq)
{
      int i, parent, child;

      i = pq->_size - 1;
      pq->_size++;
      while(i > 0)
      {
            child = i;
            parent = (child - 1) / 2;

            if(priority_queue_compare(pq, parent, child) > 0)
            {
                  priority_queue_swap(pq->_nodes, child, parent);
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
      int r = pq->_nodes[pos1]->key - pq->_nodes[pos2]->key;
      if(pq->_priority == PRIORITY_MAX)
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

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
      int i;
      PriorityQueue *pq = priority_queue_new(PRIORITY_MAX);


      int a[]={1, 9, 7, 8, 5, 4, 3, 2, 1, 100, 50, 17};

      for(i = 0; i < sizeof(a)/ sizeof(int); ++i)
      {
            KeyValue *kv = key_value_new(a[i], NULL);
            priority_queue_enqueue(pq, kv);
      }

      priority_queue_print(pq);
      priority_queue_free(pq, NULL);
      return 0;
}
