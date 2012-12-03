#include "scheduler.h"
#include "red_black_tree.h"
/*
stcp.c
*/

/*Process cpu time comparison for rb tree*/
int pCompare(const void* a, const void* b){
  const Process* x = a;
  const Process* y = b;
  if(x->cpu < y->cpu) return 1;
  return 0;
} 

/*insert into rb tree with priority CPU time*/
void add_process(Process* new_p, void* q) {
  RBTreeInsert((rb_red_blk_tree*)q, (void*)new_p, NULL);
}

Process* get_process(void* q) {
  /*examine smallest element and return process pointer*/
  Process* p;
  p = (Process*)RBPop((rb_red_blk_tree*)q);
  return p;
}

long get_timeslice(long time, void* q) {
  /*return time + CPU time of shortest process*/
  Process* p;
  p = (Process*)RBPeek((rb_red_blk_tree*)q);
  return p->cpu_remaining + time;
}

void init_q(void* q) {
  /*initialize priority queue*/
  q = (void*)RBTreeCreate(pCompare, NullFunction, NullFunction, NullFunction, NullFunction);
}
