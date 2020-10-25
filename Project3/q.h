#ifndef Q_H
#define Q_H

#include <stdlib.h> 
#include "tcb.h"

#define ALLOC(t) (t*) calloc(1, sizeof(t))

typedef struct Queue {
    struct TCB_t* head;
} Queue;

Queue * runQ;

struct TCB_t* newItem() {
    TCB_t * item = ALLOC(struct TCB_t);
    item->prev = NULL;
    item->next = NULL;
    return item;
}

struct Queue * initQueue() {
    return ALLOC(struct Queue);
}

void addQueue(struct Queue* queue, struct TCB_t* item) {
    if(queue->head == NULL)
    {
        queue->head = item;
        queue->head->prev = queue->head;
        queue->head->next = queue->head;
    }
    else
    {
        TCB_t * tail = queue->head->prev;
        tail->next = item;
        item->prev = tail;
        tail = tail->next;

        tail->next = queue->head;
        queue->head->prev = tail;
    }
}

struct TCB_t* delQueue(struct Queue* queue) {
    if(queue->head == NULL)
    {
        return NULL;
    }
    else if (queue->head->next == queue->head)
    {
        TCB_t * temp = queue->head;
        queue->head = NULL;
        return temp;
    }
    else
    {
        TCB_t * temp = queue->head;
        TCB_t * tail = queue->head->prev;
        if(queue->head->next == queue->head)
        {
            queue->head = NULL;
        }
        else
        {
            queue->head = queue->head->next;
            queue->head->prev = tail;
            tail->next = queue->head;
        }
        return temp;
    }
}

void rotateQueue(struct Queue* queue) {
    queue->head = queue->head->next;
}

void freeItem(struct TCB_t* item) {
    free(item);
}

void printQueue(TCB_t * head)
{
   if(head == NULL)
   {
      puts("Queue is NULL");
      return;
   }
   if(head->next == head)
   {
      printf("%p\n", head);
   }
   else
   {
    printf("%d,", head->thread_id);
      TCB_t * current = head->next;
      while(current != head)
      {
         printf("%d,", current->thread_id);
         current = current->next;
      }
      printf("\n");
   }
}

#endif