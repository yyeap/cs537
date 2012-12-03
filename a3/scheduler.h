/*
Yuen Lye Yeap
Lee Yerkes


scheduler.h
 */

void add_process(struct Process*, void*);

struct Process* get_process(void*);

int get_timeslice(long, void*);

void init_q(void*);
