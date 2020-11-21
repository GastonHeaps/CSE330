#ifndef SEM_H
#define SEM_H

#include "threads.h"

typedef struct Semaphore {
	int val;
	TCB_t* semQ;
} Semaphore;

void initSem(Semaphore* semaphore, int value)
{
	semaphore->semQ = NULL;
	semaphore->val = value;
}

void P(Semaphore * semaphore)
{
    if(semaphore->val <= 0)
    {
        TCB_t * tcb = DelQueue(&RunQ);
		/*
		if (tcb->thread_id < 0) {
			
		} else if (tcb->thread_id > 0) {
			//Wait would have gone here for project 3
		}
		*/
		AddQueue(&(semaphore->semQ),tcb);
		swapcontext(&(semaphore->semQ->prev->context), &(RunQ->context));
	} else {
		semaphore->val--;
	}
}

void V(Semaphore * semaphore)
{
	if (semaphore->semQ != NULL) {
		TCB_t * tcb = DelQueue(&(semaphore->semQ));
        AddQueue(&RunQ, tcb);
	}
	semaphore->val++;
}


#endif