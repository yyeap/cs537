#include "scheduler.h"
/*
stcp.c
*/
void add_process(process* new_p, void* q) {
  //insert with priority being smallest CPU
}

process* get_process(void* q) {
  //pop off the smallest element and return
}

int get_timeslice(int time, void* q) {
  // return time + CPU time of shortest process
}

void* init_q() {
  // initialize rb tree and return rb tree pointer 
}
