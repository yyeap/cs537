#include "process.h"
/*
Yuen Lye Yeap
Lee Yerkes


scheduler.h
 */

void add_process(Process* new_p, void* q);

Process* get_process(void* q);

int get_timeslice(int time, void* q);

void init_q(void* q);
