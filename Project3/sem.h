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
		if (RunQ == NULL) {
			exit(0);
		}
        TCB_t * tcb = DelQueue(&RunQ);
		if (tcb->thread_id < 0) {
			printf("\n Consumer %d is waiting \n\n",-tcb->thread_id);
		} else if (tcb->thread_id > 0) {
			printf("\n Producer %d is waiting \n\n",tcb->thread_id);
		}
		AddQueue(&(semaphore->semQ),tcb);
		swapcontext(&(tcb->context), &(RunQ->context));
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