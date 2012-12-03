/*
Yuen Lye Yeap
Lee Yerkes


scheduler.h
 */

void add_process(struct Process*, void*);

struct Process* get_process(void*);

long get_timeslice(long, void*, int*);

void init_q(void*);
