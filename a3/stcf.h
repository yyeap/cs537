/*
Yuen Lye Yeap
Lee Yerkes

stcf.h
 */

/*
stcf implementation of the add_process function used in main

takes a Process pointer and adds it to the ready queue
*/
void stcf_add_process(struct Process*);

/*
stcf implementation of the get_process function used in main

takes no arguments
returns the next Process from the ready queue
*/
struct Process* stcf_get_process();

/*
stcf implementation of the get_timeslice function used in main

input: long clock - the simulation clock
output: int* reason - reason for timeslice (0 - done; 1 - timeslice end; 2 - io)
*/
long stcf_get_timeslice(long, int*);

/*
stcf implementation of the init_q function used in main

initializes the ready queue
takes no parameters
*/
void stcf_init_q();
