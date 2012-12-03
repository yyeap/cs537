/*
Yuen Lye Yeap
Lee Yerkes


stcf.h
 */

void stcf_add_process(struct Process*, void*);

struct Process* stcf_get_process(void*);

long stcf_get_timeslice(long, void*, int*);

void stcf_init_q(void*);
