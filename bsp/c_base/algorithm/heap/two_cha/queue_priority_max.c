/*
             ÓÅÏÈ¶ÓÁÐ£¨priority_queue)ºÍÒ»°ã¶ÓÁÐ(queue)µÄº¯Êý½Ó¿ÚÒ»ÖÂ£¬²»Í¬µÄÊÇ£¬ÓÅÏÈ¶ÓÁÐÃ¿´Î³öÁÐµÄÊÇÕû¸ö¶ÓÁÐÖÐ

×îÐ¡£¨»òÕß×î´ó£©µÄÔªËØ¡£

             ±¾ÎÄ¼òÒª½éÉÜÒ»ÖÖ»ùÓÚÊý×é¶þ²æ¶ÑÊµÏÖµÄÓÅÏÈ¶ÓÁÐ£¬¶¨ÒåµÄÊý¾Ý½á¹¹ºÍÊµÏÖµÄº¯Êý½Ó¿ÚËµÃ÷ÈçÏÂ£º

Ò»¡¢¼üÖµ¶Ô½á¹¹Ìå£ºKeyValue

// =============KeyValue Struct==================================
typedef struct key_value_struct KeyValue;
struct key_value_struct
{
 int _key;
 void *_value;
};
KeyValue *key_value_new(int key, void *value);
void key_value_free(KeyValue *kv, void (*freevalue)(void *));

¼üÖµ¶Ô×÷ÎªÓÅÏÈ¶ÓÁÐµÄÖÐÊý¾ÝµÄ±£´æÐÎÊ½£¬ÆäÖÐkeyÓÃÓÚ±£´æÓÅÏÈ¼¶£¬_valueÓÃÓÚÖ¸ÏòÊµ¼ÊµÄÊý¾Ý¡£

key_value_newÓÃÓÚ´´½¨Ò»¸öKeyValue½á¹¹Ìå£»key_value_freeÓÃÓÚÊÍ·ÅÒ»¸öKeyValue½á¹¹ÌåµÄÄÚ´æ£¬

²ÎÊýfreevalueÓÃÓÚÊÍ·ÅÊý¾ÝÖ¸Õë_valueÖ¸ÏòµÄÄÚ´æ¡£



¶þ¡¢ÓÅÏÈ¶ÓÁÐ½á¹¹Ìå£ºPriorityQueue

// =============PriorityQueue Struct==============================
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

1)  ÆäÖÐnodes×Ö¶ÎÊÇ¶þ²æ¶ÑÊý×é£¬_capacityÊÇnodesÖ¸ÏòµÄKeyValue*Ö¸ÕëµÄ¸öÊý£¬_sizeÊÇnodesÖÐÊµ¼Ê´æ´¢µÄÔªËØ¸öÊý¡£

     _priority¿ÉÒÔÊÇPRIORITY_MAX»òPRIORITY_MIN£¬·Ö±ð±íÊ¾×î´óÔªËØÓÅÏÈºÍ×îÐ¡ÔªËØÓÅÏÈ¡£

2)  priority_queue_newºÍpriority_queue_free·Ö±ðÓÃÓÚ´´½¨ºÍÊÍ·ÅÓÅÏÈ¶ÓÁÐ¡£

3)  priority_queue_topÓÃÓÚÈ¡µÃ¶ÓÁÐÍ·²¿ÔªËØ£¬

4£©priority_queue_dequeueÓÃÓÚÈ¡µÃ¶ÓÁÐÍ·²¿ÔªËØ²¢½«ÔªËØ³öÁÐ¡£

                       ÆäÊµÏÖµÄ»ù±¾Ë¼Â·£¬ÒÔ×î´óÓÅÏÈ¶ÓÁÐËµÃ÷ÈçÏÂ£º

                       ¢Ù½«¶ÓÁÐÊ×²¿nodes[0]±£´æ×÷Îª·µ»ØÖµ

                       ¢Ú½«¶ÓÁÐÎ²²¿nodes[_size-1]ÖÃÓÚnodes[0]Î»ÖÃ£¬²¢Áî_size=_size-1

                       ¢ÛÁîµ±Ç°¸¸½Úµãparent(nodes[i])µÈÓÚÐÂµÄ¶ÓÁÐÊ×²¿(i=0)ÔªËØ£¬

                              parentÖ¸ÏòÔªËØµÄ¶ù×Ó½ÚµãÎªleft = nodes[2 * i + 1]ºÍrigth = nodes[2 * i + 2]£¬

                              ±È½ÏleftºÍrightµÃµ½ÓÅÏÈ¼¶¸ßµÄ¶ù×Ó½Úµã,ÉèÎªnodes[j](j = 2 *i + 1»ò2 *i + 2)£¬

                        ¢ÜÈç¹ûµ±Ç°¸¸½ÚµãparentµÄÓÅÏÈ¼¶¸ßÓÚnodes[j]£¬½»»»nodes[i]ºÍnodes[j]£¬²¢¸üÐÂµ±Ç°¸¸½Úµã,

                                  ¼´Áîi=j,²¢Ñ­»· ¢Û£»

                            Èç¹ûµ±Ç°¸¸½ÚµãµÄÓÅÏÈ¼¶µÍÓÚnodes[j],´¦Àí½áÊø¡£

5£©priority_queue_enqueueÓÃÓÚ½«KeyValueÈëÁÐ

                         ÆäÊµÏÖµÄ»ù±¾Ë¼Â·£¬ÒÔ×î´óÓÅÏÈ¶ÓÁÐËµÃ÷ÈçÏÂ£º

                         ¢ÙÉèÖÃnodes[_size] ÎªÐÂµÄKeyValue,²¢Áî_size++

                         ¢ÚÁîµ±Ç°¶ù×Ó½Úµãchild(nodes[i])ÎªÐÂµÄ¶ÓÁÐÎ²²¿½Úµã£¨i=_size-1)£¬childµÄ¸¸½ÚµãparentÎªnodes[j],

                             ÆäÖÐj=  (i - 1) / 2

                         ¢ÛÈç¹ûµ±Ç°¶ù×Ó½ÚµãchildµÄÓÅÏÈ¼¶¸ßÓÚparent, ½»»»nodes[i]ºÍnodes[j]£¬²¢¸üÐÂµ±Ç°¶ù×Ó½Úµã

                                     ¼´Áîi = j,²¢Ñ­»·¢Û;

                             Èç¹ûµ±Ç°¶ù×Ó½ÚµãµÄÓÅÏÈ¼¶µÍÓÚparent,´¦Àí½áÊø¡£

6)  priority_queue_sizeÓÃÓÚÈ¡µÃ¶ÓÁÐÖÐÔªËØ¸öÊý£¬priority_queue_emptyÓÃÓÚÅÐ¶Ï¶ÓÁÐÊÇ·ñÎª¿Õ¡£

7£©priority_queue_printÓÃÓÚÊä³ö¶ÓÁÐÖÐµÄÄÚÈÝ¡£



               ÎÄ¼þpq.h¸ø³öÁËÊý¾Ý½á¹¹ºÍº¯ÊýµÄÉùÃ÷£¬ÎÄ¼þpq.c¸ø³öÁË¾ßÌåÊµÏÖ£¬main.cÎÄ¼þÓÃÓÚ²âÊÔ¡£ËäÈ»ÊÇÊ¹ÓÃ

¹ý³Ì»¯±à³ÌµÄCÓïÑÔ£¬¿ÉÒÔ¿´µ½¾ßÌåµÄ±àÂëÖÐÓ¦ÓÃÁË»ùÓÚ¶ÔÏóµÄË¼Ïë£¬ÎÒÃÇ¶ÔÊý¾Ý½á¹¹ºÍÏà¹Øº¯Êý×öÁËÒ»¶¨³Ì¶ÈµÄ

¾Û¼¯ºÍ·â×°¡£
*/
/*
*File: pq.h
*purpose: declaration of priority queue in C
*Author:puresky
*Date:2011/04/27
*/
#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

// =============KeyValue Struct==================================
typedef struct key_value_struct KeyValue;
struct key_value_struct
{
      int _key;
      void *_value;
};
KeyValue *key_value_new(int key, void *value);
void key_value_free(KeyValue *kv, void (*freevalue)(void *));

// =============PriorityQueue Struct==============================
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

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

//Functions of KeyValue Struct
KeyValue *key_value_new(int key,
                                    void *value)
{
      KeyValue *pkv = (KeyValue *)malloc(sizeof(KeyValue));
      pkv->_key = key;
      pkv->_value = value;
      return pkv;
}
void key_value_free(KeyValue *kv,
                              void (*freevalue)(void *))
{
      if(kv)
      {
            if(freevalue)
            {
                  freevalue(kv->_value);
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
      printf("add key:%d\n", kv->_key);
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
            printf("%d ", pq->_nodes[i]->_key);
      printf("\n");

      printf("dequeue all data\n");
      while(!priority_queue_empty(pq))
      {
            kv = priority_queue_dequeue(pq);
            printf("%d ", kv->_key);
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
      int r = pq->_nodes[pos1]->_key - pq->_nodes[pos2]->_key;
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

      system("pause");
      return 0;
}