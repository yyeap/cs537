/*
expq.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "expq.h"

#define NUM_QUEUE 8
#define BASE_TIMESLICE 10

static queue q[NUM_QUEUE];
static int timeSlices[NUM_QUEUE];

void expq_init_q()
{
    int i;

    /* initialize all queues */
    for (i = 0; i < NUM_QUEUE; i++)
    {
        q_init(&q[i]);
    }

    /* set all time slices according to priority */
    timeSlices[0] = BASE_TIMESLICE;

    for (i = 1; i < NUM_QUEUE; i++)
    {
        timeSlices[i] = 2 * timeSlices[i - 1];
    }
}

void expq_add_process (struct Process *p)
{
    long elapsedTime, timeSlice;
    int priority;

    if (NULL == p)
    {
        printf("ERROR: Cannot add null process to queue.");
        fflush(stdout);
        exit(-1);
    }

    priority = p->priority;
    if (priority < 0 || priority >= NUM_QUEUE)
    {
        printf("ERROR: Invalid priority value.");
        exit(-1);
    }

    elapsedTime = p->lastRunTime;
    timeSlice = timeSlices[priority];

    /* if process use up entire time slice */
    if (elapsedTime >= timeSlice)
    {
        /* if current timeslice is not the largest */
        if (priority < NUM_QUEUE - 1)
        {
            p->priority = priority + 1;
        }
    }
    /* increase process priority if use less than half timeslice */
    else if (elapsedTime < timeSlice / 2.0)
    {
        if (priority > 0)
        {
            p->priority = priority - 1;
        }
    }

    p->lastRunTime = 0;
    if (enqueue(&q[p->priority], p) != 0)
    {
        printf("Unexpected error.");
        exit(-1);
    }
}

struct Process* expq_get_process()
{
    int i;
    struct Process *next;

    /* lookup all priority, dequeue from highest */
    for (i = 0; i < NUM_QUEUE; i++)
    {
        if (!q_isEmpty(&q[i]))
        {
            next = (struct Process*)dequeue(&q[i]);
            return next;
        }
    }

    /* if queue is empty, return NULL */
    return NULL;
}

long expq_get_timeslice (long time, int *reason)
{
    long i;
    struct Process *temp;

    temp = NULL;
    /* lookup all priority, peek from highest */
    for (i = 0; i < NUM_QUEUE; i++)
    {
        if (!q_isEmpty(&q[i]))
        {
            temp = (struct Process*)peek(&q[i]);
            break;
        }
    }

    if (NULL != temp)
    {
        /* process completes */
        if (temp->cpu_remaining == 0)
        {
            *reason = 1;
            return temp->cpu_remaining;
        }

        /* IO starts */
        if(temp->time_until_io <= temp->cpu_remaining
            && temp->time_until_io <= timeSlices[temp->priority])
        {
            *reason = 1;
            return temp->time_until_io;
        }

        /* timeslice is up */
        if (temp->lastRunTime >= timeSlices[temp->priority])
        {
            *reason = 2;
            return timeSlices[temp->priority];
        }
        *reason = 3;
        return temp->lastRunTime;
    }
    return -1;
}
