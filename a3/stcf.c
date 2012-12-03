#include "process.h"
#include "stcf.h"
#include "red_black_tree.h"
/*
stcf.c
*/

rb_red_blk_tree* q;

/*struct Process cpu time comparison for rb tree*/
int pCompare(const void* a, const void* b){
  const struct Process* x = a;
  const struct Process* y = b;
  if(x->cpu_remaining < y->cpu_remaining) return 1;
  return 0;
} 

/*insert into rb tree with priority CPU time*/
void stcf_add_process(struct Process* new_p) {
  RBTreeInsert(q, (void*)new_p, 0);
}

struct Process* stcf_get_process() {
  /*examine smallest element and return Process pointer*/
  struct Process* p;
  p = (struct Process*)RBPop(q);
  return p;
}

long stcf_get_timeslice(long clock, int* reason) {
  /*return time + CPU time of shortest Process or IO time if sooner*/
  struct Process* p;
  long timeslice;
  p = (struct Process*)RBPeek(q);

  if(NULL == p) {
    /*tree is empty*/
    return -1;
  }

  if(p->IO_remaining == 0 || p->cpu_remaining < p->time_until_io){
    *reason = 0;
    timeslice = p->cpu_remaining;
  } else {
    *reason = 2;
    timeslice = p->time_until_io;
    p->time_until_io = p->IO_interval;
  }
  return timeslice;
}

void stcf_init_q() {
  /*initialize priority queue*/
  q = RBTreeCreate(pCompare, NullFunction, NullFunction, NullFunction, NullFunction);
}
