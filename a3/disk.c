/*
disk.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "queue.h"
#include "disk.h"

#define IOTIME 10

static queue* d;
static int IO_remain;

void init_disk ()
{
    d = (queue*)malloc(sizeof(queue));

    if (NULL == d)
    {
        printf("Error allocating disk queue.");
        fflush(stdout);
        exit(-1);
    }
    q_init(d);
    IO_remain = 0;
}

void io_add_process (struct Process *p)
{
    /* if IO queue is empty, reset IO completion time */
    if (q_isEmpty(d))
    {
        enqueue(d, p);
        IO_remain = IOTIME;
    }
    else
    {
        enqueue(d, p);
    }
}

void update_io_remain(int stepTime)
{
    IO_remain = IO_remain - stepTime;
}

struct Process* get_next_io()
{
    struct Process* p;

    p = (struct Process*)dequeue(d);

    p->IO_remaining--;
    p->next_io_time = p->IO_interval;
    IO_remain = IOTIME;

    return p;
}

long get_IO_complete ()
{
    if (q_isEmpty(d)){
        return -1;
    }
    return (long)IO_remain;
}
