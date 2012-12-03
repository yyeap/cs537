/*
disk.c
 */

#include <stdio.h>
#include "process.h"
#include "queue.h"
#include "disk.h"

#define IOTIME 10

void disk_init (disk* d)
{
    q_init(d->q);
}

void io_add_process (disk *d, struct Process *p)
{
    /* if IO queue is empty, reset IO completion time */
    if (q_isEmpty(d->q))
    {
        enqueue(d->q, p);
        d->IO_remain = IOTIME;
    }
    else
    {
        enqueue(d->q, p);
    }
}

void update_io_remain(disk *d, int stepTime)
{
    d->IO_remain = d->IO_remain - stepTime;
}

struct Process* get_next_io(disk *d)
{
    struct Process* p;

    p = (struct Process*)dequeue(d->q);

    p->IO_remaining--;
    p->next_io_time = p->IO_interval;
    d->IO_remain = IOTIME;

    return p;
}

long get_IO_complete (disk* d, long clock)
{
    return (q_isEmpty(d->q))? -1 : (long)d->IO_remain + clock;
}
