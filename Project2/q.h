#ifndef Q_H
#define Q_H

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include "tcb.h"

struct Queue {
    struct TCB_t* head;
};

struct TCB_t* newItem() {
    struct TCB_t* temp = (struct TCB_t*)malloc(sizeof(struct TCB_t));
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

void initQueue(struct Queue* head) {
    head->head = NULL;
}

void addQueue(struct Queue* head, struct TCB_t* item) {
    if (head->head == NULL) {
        item->prev = item;
        item->next = item;
        head->head = item;
    } else {
        item->prev = head->head->prev;
        item->next = head->head;
        head->head->prev->next = item;
        head->head->prev = item;
    }
}

struct TCB_t* delQueue(struct Queue* head) {
    struct TCB_t *delElement = head->head;
    if (head->head != NULL) {
        if (head->head != head->head->next) {
            head->head->prev->next = head->head->next;
            head->head->next->prev = head->head->prev;
            head->head = head->head->next;
        } else {
            head->head = NULL;
        }
        delElement->prev = delElement;
        delElement->next = delElement;

    }
    return delElement;
}

void rotateQueue(struct Queue* head) {
    addQueue(head, delQueue(head));
}

void freeItem(struct TCB_t* item) {
    free(item);
}

#endif