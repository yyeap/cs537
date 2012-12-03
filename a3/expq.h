/*
Yuen Lye Yeap
Lee Yerkes


expq.h
 */

void expq_add_process(struct Process*);

struct Process* expq_get_process();

long expq_get_timeslice(long, int*);

void expq_init_q();
