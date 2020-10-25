#ifndef THREADS_H
#define THREADS_H

#include "q.h"

struct Queue *RunQ;

void start_thread(void (*function)(int, int), int id, int b) { 
    //allocate a stack (via malloc) of a certain size (choose 8192)
    void *stack = (void *)malloc(8192);

    //allocate a TCB (via malloc)
    TCB_t *tcb = newItem();
    //call init_TCB with appropriate arguments
    init_TCB(tcb, function, stack, 8192, id, b);

    //call addQ to add this TCB into the “RunQ” which is a global header pointer
    addQueue(RunQ, tcb);
}

void run() {	// real code
    ucontext_t parent;	// get a place to store the main context, for faking
    getcontext(&parent);	// magic sauce
    swapcontext(&parent, &(RunQ->head->context));	// start the first thread
}

// similar to run
void yield() {
    //rotate the run Q;
    ucontext_t from, to;
    getcontext(&from);
    RunQ->head->context = from;
    rotateQueue(RunQ);
    
    //swap the context, from previous thread to the thread pointed to by RunQ
    to = RunQ->head->context;
    swapcontext(&from, &to);
}

#endif