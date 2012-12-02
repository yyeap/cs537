/*
disk.c
 */

#include <stdio.h>
#include "disk.h"

extern void disk_init (disk* d)
{
    q_init(d->q);
    d->size = 0;
}

extern int get_IO_complete (disk* d, int clock)
{
  //return 1 if IO complete, else 0
}
