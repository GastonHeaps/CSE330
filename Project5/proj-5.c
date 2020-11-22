#include "sem.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int A = 0; //Number of chopsticks
int B = 0; //Number of entries
Semaphore *ch = 0;

void philosopher(int id);

void main(char** args) {
	scanf("%d,%d", &A, &B);

	ch = (Semaphore*) malloc(A * sizeof(Semaphore));

	for (int i = 0; i < A; i++) {
		initSem(&ch[i], 1);
	}
	InitQueue(&RunQ);

    for(int i = 0; i < B; i++) {
		int id;
        scanf("%d", &id);
		start_thread(philosopher, id);
    }

	run();
}

void philosopher(int id) {
	Semaphore *right = &ch[(id - 1) % A];
	Semaphore *left = &ch[id % A];

	//Grab right chopstick
	P(right);
	yield();

	//Grab left chopstick
	P(left);
	//if (RunQ == NULL) {
		//exit(0);
	//}
	yield();

	//Eating
	printf("\n Philosopher %d is eating \n", id);

	//Drop right chopstick
	V(right);
	//Drop left chopstick
	V(left);

	TCB_t *current = DelQueue(&RunQ);
	swapcontext(&(current->context), &(RunQ->context));
}