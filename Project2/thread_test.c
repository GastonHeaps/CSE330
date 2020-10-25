//Gaston Heaps

#include <unistd.h>
#include "threads.h"

int global = 0;

void f(int id, int thread_exec_lim) {
    int local = 0;
    for(int i = 0; i < thread_exec_lim; i++) {
        local++;
        global += id;

        printf("\n This is %d th execution of thread %d with global var value %d \n", local, id, global);

        yield();
    }
    return;
}

int main() {
    int thread_tot = 0, thread_exec_lim = 0;
    scanf("%d,%d", &thread_tot, &thread_exec_lim);

    if (thread_tot == 0) {
        printf("\n No Threads \n");
        return 0;
    }

    RunQ = (struct Queue*) malloc(sizeof(struct Queue));

    initQueue(RunQ);

    for(int id = 1; id <= thread_tot; id++) {
        start_thread(f, id, thread_exec_lim);
    }
    
    run();

    return 0;
}