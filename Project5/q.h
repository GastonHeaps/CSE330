#ifndef Q_H
#define Q_H

#include <stdlib.h> 
#include "tcb.h"

struct TCB_t* NewItem() {
    TCB_t * item = malloc(sizeof(TCB_t));
    return item;
}

void InitQueue(TCB_t** head) {
    *head = NULL;
}

void AddQueue(TCB_t** head, struct TCB_t* item) {
    if(*head == NULL)
    {
        *head = item;
        (*head)->prev = *head;
        (*head)->next = *head;
    }
    else
    {
        TCB_t* tail = (*head)->prev;
        tail->next = item;
        item->prev = tail;
        item->next = *head;
        (*head)->prev = item;
    }
}

struct TCB_t* DelQueue(TCB_t** head) {
	TCB_t* del = *head;
	if (del->next == del) {
		*head = NULL;
	} else {
        *head = (*head)->next;
        del = (*head)->prev;
        (*head)->prev->prev->next = *head;
        (*head)->prev = (*head)->prev->prev;
        del->prev = del;
        del->next = del;
	}
	return del;

    if(*head == NULL)
    {
        return NULL;
    }
    else if ((*head)->next == *head)
    {
        TCB_t* item = malloc(sizeof(TCB_t));
        item->context = (*head)->context;
        *head = NULL;
        return item;
    }
    else
    {
        TCB_t* item = malloc(sizeof(TCB_t));
        item->context = (*head)->context;

        TCB_t* temp = (*head)->next;
        TCB_t* tail = (*head)->prev;
        tail->next = temp;
        temp->prev = tail;
        *head = (*head)->next;

        return item;
    }
}

void RotateQ(TCB_t** head) {
    if (*head != NULL) {
        *head = (*head)->next;
    }
}

#endif