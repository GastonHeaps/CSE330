#include <stdio.h>
#include <unistd.h> // Used for sleep()
#include "sem.h"

#define SLEEP_TIME 1 // in seconds

int buffer_size = 1;
int iteration_limit = 2; // number of times producers and consumers run their while loop
int producers = 6;
int consumers = 1;


int *buffer = 0;
int in, out = 0;
Semaphore *full;
Semaphore *empty;
Semaphore *mutexC;
Semaphore *mutexP;

void producer(int id)
{
    for(int i = 1; i <= iteration_limit; i++) 
    {

        P(empty);
        P(mutexP);


        buffer[in] = id;
        in = (in + 1) % buffer_size;
        if (buffer[in] != 0) {
            printf("\n Producer %d is producing item number %d \n\n", id, i);
        }

        sleep(SLEEP_TIME);

       V(mutexP);
        V(full);
    }
}

void consumer(int id)
{
    for(int i = 1; i <= iteration_limit; i++) 
    {
        P(full);
       P(mutexC); 
            
    if (buffer[out] != 0) {
        printf("\n Consumer %d is consuming item generated by Producer %d \n\n", -(id), buffer[out]);
    } else {
        //printf("\n Consumer %d is waiting \n\n",-id);
    }

        buffer[out] = 0;
        out = (out + 1) % buffer_size;

        sleep(SLEEP_TIME);

       V(mutexC);
        V(empty);
    }
}

int main()
{

    scanf("%d,%d,%d,%d", &buffer_size, &producers, &consumers, &iteration_limit);

    buffer = (int*) malloc(buffer_size * sizeof(int));

    runQ = initQueue();

    full = initSem(0); 
    empty = initSem(buffer_size);
    mutexP = initSem(1);
    mutexC = initSem(1);

    // Initialize buffer
    for (int i = 0; i < buffer_size; i++) {
        buffer[i] = 0;
    }

    for(int i = 0; i < producers+consumers; i++) {
        int id;
        scanf("%d", &id);
        if(id > 0) {
            start_thread(producer, id);
        } else {
            start_thread(consumer, id);
        }
    }

    /*start_thread(consumer, -1);
    start_thread(consumer, -2);
    start_thread(consumer, -3);
    start_thread(consumer, -4);*/

    run();

    return 0;
}