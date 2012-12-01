/*
disk.h
*/

#include <stdio.h>
#include "queue.h"

typedef struct disk {
    queue* q;
    int size;
} disk;

extern void disk_init (disk* d);

extern int get_IO_complete(disk* d, int clock);
