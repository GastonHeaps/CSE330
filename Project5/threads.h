#ifndef THREADS_H
#define THREADS_H

#include "q.h"

TCB_t* RunQ;

void start_thread(void (*function)(int), int id) { 
    //allocate a stack (via malloc) of a certain size (choose 8192)
    void *stack = (void *)malloc(8192);

    //allocate a TCB (via malloc)
    TCB_t *tcb = NewItem();
    //call init_TCB with appropriate arguments
    init_TCB(tcb, function, stack, 8192, id);

    //call addQ to add this TCB into the “runQ” which is a global header pointer
    AddQueue(&RunQ, tcb);
}

void run() {	// real code
    ucontext_t parent;	// get a place to store the main context, for faking
    getcontext(&parent);	// magic sauce
    swapcontext(&parent, &(RunQ->context));	// start the first thread
}

// similar to run
void yield() {
    //rotate the run Q;
    ucontext_t from, to;
    getcontext(&from);
    RunQ->context = from;
    RotateQ(&RunQ);
    
    to = RunQ->context;
    if (RunQ->next != RunQ) {
        swapcontext(&(RunQ->prev->context), &to);

    }
}

#endif