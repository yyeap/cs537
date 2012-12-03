/*
disk.h
*/

typedef struct disk {
    struct queue* q;
    int IO_remain;
} disk;

void init_disk();

void io_add_process(struct Process *p);

void update_io_remain (int stepTime);

struct Process* get_next_io();

long get_IO_complete();
