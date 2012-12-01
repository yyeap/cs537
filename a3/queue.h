#include <stdio.h>
#include <stdlib.h>
#include "process.h"

typedef struct node {
    struct node *next;
    Process* data;
}node;

typedef struct queue {
    struct node *head;
    struct node *tail;
}queue;

extern void q_init(queue* q);

extern int enqueue(queue* q, Process* p);

extern Process* dequeue(queue* q);

extern int isEmpty(queue* q);

extern Process* peek (queue* q);
