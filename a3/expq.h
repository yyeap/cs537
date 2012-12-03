/*
Yuen Lye Yeap
Lee Yerkes


expq.h
 */

void expq_add_process(struct Process*, void*);

struct Process* expq_get_process(void*);

long expq_get_timeslice(long, void*, int*);

void expq_init_q(void*);
