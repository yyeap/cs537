#include "process.h"
/*
Yuen Lye Yeap
Lee Yerkes


scheduler.h
 */

void add_process(process* new_p, void* q);

process* get_process(void* q);

int get_timeslice(int time, void* q);

void* init_q();
