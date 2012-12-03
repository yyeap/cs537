/*
disk.h
*/

typedef struct disk {
    struct queue* q;
    int IO_remain;
} disk;

void disk_init(disk* d);

void io_add_process(disk *d, struct Process *p);

void update_io_remain (disk *d, int stepTime);

struct Process* get_next_io(disk *d);

long get_IO_complete(disk* d, long clock);
