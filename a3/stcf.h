/*
Yuen Lye Yeap
Lee Yerkes


stcf.h
 */

void stcf_add_process(struct Process*);

struct Process* stcf_get_process();

long stcf_get_timeslice(long, int*);

void stcf_init_q();
