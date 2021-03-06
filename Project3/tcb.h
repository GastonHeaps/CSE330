#ifndef TCB_H
#define TCB_H

#include <ucontext.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct TCB_t {
    struct TCB_t*     next;
    struct TCB_t*     prev;
    ucontext_t      context;
    int thread_id;
} TCB_t;

int global_thread_id = 0;

void init_TCB (TCB_t *tcb, void (*function), void *stackP, int stack_size, int arg1)
{
    memset(tcb, '\0', sizeof(TCB_t));       // wash, rinse
    getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    tcb->thread_id = arg1;
    makecontext(&tcb->context, function, 1, arg1);// context is now cooked
}

#endif