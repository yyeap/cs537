#include "process.h"
/*
Yuen Lye Yeap
Lee Yerkes


scheduler.h
 */

void add_process(Process*, void*);

Process* get_process(void*);

int get_timeslice(long, void*, int*);

void init_q(void*);
