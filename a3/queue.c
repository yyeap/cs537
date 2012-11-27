#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

extern void q_init(q* q)
{
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

extern int enqueue(q* q, Process* p)
{
    if(NULL == p)
    {
        printf("ERROR: Cannot add null process to queue.");
        return -1;
    }

    if (NULL == q->head) /* if queue is empty */
    {
        q->head = p;
        q->head->next = NULL;
        q->head->prev = NULL;
        q->tail->prev = NULL;
    }
    else if (1 == q->size)
    {
        q->head->next = p;
        q->tail->prev = q->head;
    }
    else
    {
        q->tail->next = p;
        q->tail->next->prev = p;
    }
    q->tail = p;
    q->tail->next = NULL;
    q->size++;
    return 0;
}

extern Process* dequeue(q* q)
{
    Process* temp = NULL;

    if (NULL == q->head)
    {
        printf("ERROR: Cannot dequeue from an empty queue.");
        return NULL;
    }

    if (1 == q->size)
    {
        temp = q->head;
        q->head = NULL;
        q->tail = NULL;
    }
    else
    {
        temp = q->tail;
        q->tail = q->tail->prev;
        q->tail->next = NULL;
    }
    q->size--;
    return temp;
}

extern int isEmpty(q* q)
{
    return 0 == q->size;
}

extern void q_destroy(q* q)
{
    free(q->head);
    free(q->tail);
}
