#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"

void q_init(queue* q)
{
    q->head = NULL;
    q->tail = NULL;
}

int enqueue(queue *q, struct Process *p)
{
    node *newNode =(node*) malloc(sizeof(node));
    if(NULL == p)
    {
        printf("ERROR: Cannot add null process to queue.");
        exit(-1);
    } else if (NULL == newNode)
    {
        printf("ERROR: Cannot allocate memory.");
        exit(-1);
    }

    newNode->data = (struct Process*)p;

    if (NULL == q->head) /* if queue is empty */
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
    }
    q->tail = newNode;
    q->tail->next = NULL;
    return 0;
}

struct Process* dequeue(queue* q)
{
    struct Process* data;
    node *temp;

    if (NULL == q->head)
    {
        printf("ERROR: Cannot dequeue from an empty queue.");
        return NULL;
    }

    data = q->head->data;
    temp = q->head;

    if (NULL == q->head->next)
    {
        q->head = NULL;
        q->tail = NULL;
    }
    else
    {
        q->head = q->head->next;
    }

    free(temp);
    return (struct Process*)data;
}

int q_isEmpty(queue *q)
{
    return NULL == q->head;
}

struct Process* peek (queue* q)
{
    return q->head->data;
}
