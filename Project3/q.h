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
	if (del == NULL) {
        return NewItem();
    }
    else if (del->next == del) {
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

}

void RotateQ(TCB_t** head) {

    *head = (*head)->next;
}

#endif