#include "process.h"
#include "scheduler.h"
#include "red_black_tree.h"
/*
stcp.c
*/

/*struct Process cpu time comparison for rb tree*/
int pCompare(const void* a, const void* b){
  const struct Process* x = a;
  const struct Process* y = b;
  if(x->cpu_remaining < y->cpu_remaining) return 1;
  return 0;
} 

/*insert into rb tree with priority CPU time*/
void add_process(struct Process* new_p, void* q) {
  RBTreeInsert((rb_red_blk_tree*)q, (void*)new_p, NULL);
}

struct Process* get_process(void* q) {
  /*examine smallest element and return Process pointer*/
  struct Process* p;
  p = (struct Process*)RBPop((rb_red_blk_tree*)q);
  return p;
}

long get_timeslice(long time, void* q, int* reason) {
  /*return time + CPU time of shortest Process or IO time if sooner*/
  struct Process* p;
  long timeslice;
  p = (struct Process*)RBPeek((rb_red_blk_tree*)q);
  
  if(p->IO_remaining == 0 || p->cpu_remaining < p->time_until_io){
    *reason = 0;
    timeslice = p->cpu_remaining + time;
  } else {
    *reason = 2;
    timeslice = p->time_until_io + time;
    p->time_until_io = p->IO_interval;
  }
  return timeslice;
}

void init_q(void* q) {
  /*initialize priority queue*/
  q = (void*)RBTreeCreate(pCompare, NullFunction, NullFunction, NullFunction, NullFunction);
}
