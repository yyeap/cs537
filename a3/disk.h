/*
disk.h
*/

#include <stdio.h>
#include "queue.h"

typedef struct disk {
    queue* q;
    int IO_remain;
} disk;

extern void disk_init(disk* d);

extern void io_add_process(disk *d, Process *p);

extern void update_io_remain (disk *d, int stepTime);

extern Process* get_next_io(disk *d);

extern long get_IO_complete(disk* d, long clock);
