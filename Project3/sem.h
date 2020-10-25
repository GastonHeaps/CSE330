#ifndef SEM_H
#define SEM_H

#include "threads.h"

typedef struct Semaphore {
	int value;
	struct Queue *semQ;
} Semaphore;

Semaphore *  initSem(int value)
{
	Semaphore * semaphore = ALLOC(Semaphore);
    semaphore->value = value;
    semaphore->semQ = initQueue();
    return semaphore;
}

void P(Semaphore * semaphore)
{
    semaphore->value--;
    if(semaphore->value < 0)
    {
        
        TCB_t * tcb = delQueue(runQ);
		if (tcb->thread_id < 0) {
			printf("\n Consumer %d is waiting \n\n",-tcb->thread_id);
		} else if (tcb->thread_id > 0) {
			printf("\n Producer %d is waiting \n\n",tcb->thread_id);
		}
		
		addQueue(semaphore->semQ,tcb);
		//while (runQ->head == NULL); {
			swapcontext(&tcb->context, &runQ->head->context);
		//}
		
        
	}
}

void V(Semaphore * semaphore)
{
	semaphore->value++;
	if (semaphore->value <= 0) {
		TCB_t * tcb = delQueue(semaphore->semQ);
        addQueue(runQ, tcb);
	}
	if (runQ->head == NULL) {
		exit(1);
	} else {
		yield();
	}
	
}


#endif