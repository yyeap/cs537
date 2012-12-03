/*
disk.c
 */

#include <stdio.h>
#include "disk.h"

#define IOTIME 10

extern void disk_init (disk* d)
{
    q_init(d->q);
}

extern void io_add_process (disk *d, Process *p)
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

extern void update_io_remain(disk *d, int stepTime)
{
    d->IO_remain = d->IO_remain - stepTime;
}

extern Process* get_next_io(disk *d)
{
    Process* p;

    p = dequeue(d->q);

    p->IO_remaining--;
    p->next_io_time = p->IO_interval;
    d->IO_remain = IOTIME;

    return p;
}

extern long get_IO_complete (disk* d, long clock)
{
    return (q_isEmpty(d->q))? -1 : (long)d->IO_remain + clock;
}
