#include <stdio.h>
#include <stdlib.h>
#include "process.h"

typedef struct queue {
    Process* head;
    Process* tail;
    int size;
}q;

extern void q_init(q* q);

extern int enqueue(q* q, Process* p);

extern Process* dequeue(q* q);

extern int isEmpty(q* q);

extern void q_destroy(q* q);
