/*
disk.h
*/

void init_disk();

void io_add_process(struct Process *p);

void update_io_remain (int stepTime);

struct Process* get_next_io();

long get_IO_complete();
