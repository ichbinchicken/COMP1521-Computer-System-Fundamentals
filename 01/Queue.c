// Written by John Shepherd, July 2017
// Modified by Ziming Zheng 5052592

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Queue.h"

typedef struct QueueNode {
   int jobid;  // unique job ID
   int size;   // size/duration of job
   struct QueueNode *next;
} QueueNode;

struct QueueRep {
   int nitems;      // # of nodes
   QueueNode *head; // first node
   QueueNode *tail; // last node
};

static void destroyNode(QueueNode *curr);
static void destroyNode(QueueNode *curr);

// remove the #if 0 and #endif
// once you've added code to use this function

// create a new node for a Queue
static QueueNode *makeQueueNode(int id, int size)
{
   QueueNode *new;
   new = malloc(sizeof(struct QueueNode));
   assert(new != NULL);
   new->jobid = id;
   new->size = size;
   new->next = NULL;
   return new;
}




// make a new empty Queue
Queue makeQueue()
{
   Queue new;
   new = malloc(sizeof(struct QueueRep));
   assert(new != NULL);
   new->nitems = 0; new->head = new->tail = NULL;
   return new;
}

// release space used by Queue
void  freeQueue(Queue q)
{
   assert(q != NULL);
   QueueNode *curr = q->head; QueueNode*after = q->head;
  while (curr != NULL) {
       after = curr->next;
       destroyNode(curr);
       curr = after;
   }
}

static void destroyNode(QueueNode *curr) {
   assert(curr != NULL);
   free(curr);
}

// add a new item to tail of Queue
void  enterQueue(Queue q, int id, int size)
{
   assert(q != NULL);
   QueueNode *new = makeQueueNode(id, size);
   if (q->head == NULL) q->head = q->tail = new;
   else {
       q->tail->next = new;
       q->tail = new;
   }
   q->nitems ++;
}

// remove item on head of Queue
int   leaveQueue(Queue q)
{
   assert(q != NULL);
   if (q->head == NULL) return -1;
   else {
       int id = q->head->jobid;
       QueueNode *old = q->head;
       q->head = old->next;
       if (q->head == NULL) q->tail = NULL;
       free(old);
       q->nitems --;
       return id;   
   }
}

// count # items in Queue
int   lengthQueue(Queue q)
{
   assert(q != NULL);
   return q->nitems;
}

// return total size in all Queue items
int   volumeQueue(Queue q)
{
   assert(q != NULL);
   QueueNode *curr = q->head;
   int totalSize = 0;
   if (q->head == NULL) {}
   else {
       while (curr != NULL) {
           totalSize += curr->size;
           curr = curr->next;
       }
   }
   return totalSize; 
}

// return size/duration of first job in Queue
int   nextDurationQueue(Queue q)
{
   assert(q != NULL);
   int size = 0;
   if (q->head == NULL){}
   else {
       size = q->head->size;
   } 
   return size;
}


// display jobid's in Queue
void showQueue(Queue q)
{
   QueueNode *curr;
   curr = q->head;
   while (curr != NULL) {
      printf(" (%d,%d)", curr->jobid, curr->size);
      curr = curr->next;
   }
}
