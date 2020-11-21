//https://github.com/smithtrenton/CSE430Projects/blob/master/Project4/proj-4.c

#include "sem.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int r = 0, w = 0, rwc = 0, rc = 0, wwc = 0, wc = 0, i = 0;
Semaphore *rsem, *wsem;

void reader(int readerID);
void reader_entry();
void reader_exit();
void writer(int writerID);
void writer_entry();
void writer_exit();

void main(char** args) {
	rsem = malloc(sizeof(Semaphore));
	wsem = malloc(sizeof(Semaphore));

	initSem(rsem, 0);
	initSem(wsem, 0);
	InitQueue(&RunQ);

   	scanf("%d,%d", &r, &w);
    for(int i = 0; i < r + w; i++) {
        int id;
        scanf("%d", &id);
        if(id > 0) {
            start_thread(reader, id);
        } else if (id < 0) {
            start_thread(writer, id);
        }
    }

	run();
}

void reader(int readerID) {
    	reader_entry();
		
		printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
		yield();
		printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i);

        reader_exit();

		TCB_t *current = DelQueue(&RunQ);
		if (RunQ == NULL) {
			exit(0);
		}
		swapcontext(&(current->context), &(RunQ->context));

}

void reader_entry() {
	if (wwc > 0 || wc > 0) {
		rwc++;
		P(rsem);
		rwc--;
	}
	rc++;
}

void reader_exit() {
	rc--;
	if (rc == 0 && wwc > 0) {
		V(wsem);
	}



}

void writer(int writerID) {
		writer_entry();

		i = -writerID;
		printf("\n This is the %d th writer writing value i = %d \n", -writerID, i );
		yield();
		printf("\n This is the %d th writer verifying value i = %d \n", -writerID, i );

		writer_exit();

		TCB_t *current = DelQueue(&RunQ);
		if (RunQ == NULL) {
			exit(0);
		}
		swapcontext(&(current->context), &(RunQ->context));
        		                                
}

void writer_entry() {
	if (rc > 0 || wc > 0 || rwc > 0 || wwc > 0) {
		wwc++;
 
		P(wsem);

		wwc--;
	}
	wc++;


}

void writer_exit() {
	wc--;
	if (rwc > 0) {
        for(int i = 0; i < rwc; i++) {
		    V(rsem);
        }

	}
	else if (wwc > 0) {
		V(wsem);
	}
}