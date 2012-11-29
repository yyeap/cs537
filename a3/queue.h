#include <stdio.h>
#include <stdlib.h>
#include "process.h"

typedef struct queue {
    Process* head;
    Process* tail;
    int size;
}queue;

extern void q_init(queue* q);

extern int enqueue(queue* q, Process* p);

extern Process* dequeue(queue* q);

extern int isEmpty(queue* q);

extern void q_destroy(queue* q);
