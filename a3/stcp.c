#include "scheduler.h"
/*
stcp.c
*/

//Process cpu time comparison for rb tree
int pCompare(const void* a, const void* b){
  if(a->cpu < b->cpu) return 1;
  return 0;
} 

//insert into rb tree with priority CPU time
void add_process(process* new_p, void* q) {
  pq_enqueue((pq_t)q, (pq_data_t)new_p, NULL);
}

process* get_process(void* q) {
  // examine smallest element and return process pointer
  process* p;
  p = (process*)pq_dequeue((pq_t)q, NULL);
  return p;
}

int get_timeslice(int time, void* q) {
  // return time + CPU time of shortest process
  process* p;
  p = (process*)pq_inspect_next((pq_t)q, NULL);
  return p->cpu_remaining + time;
}

void init_q(void* q) {
  // initialize priority queue
  pq_status_t status;
  q = (void*)pq_new_queue(0, pCompare, status);
}
