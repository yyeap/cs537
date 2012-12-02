#include "scheduler.h"
/*
stcp.c
*/

//Process cpu time comparison for rb tree
int pCompare(const void* a, const void* b){
  if(a->cpu > b->cpu) return 1;
  if(a->cpu < b->cpu) return -1;
  return 0;
} 

//insert into rb tree with priority CPU time
void add_process(process* new_p, void* q) {
  RBTreeInsert((rb_red_blk_tree*)q, new_p, 0);
}

process* get_process(void* q) {
  // examine smallest element and return process pointer
  rb_red_blk_node* newNode;
  
}

int get_timeslice(int time, void* q) {
  // return time + CPU time of shortest process
}

void init_q(void* q) {
  // initialize rb tree and assign to pointer 
  q = (void*)RBTreeCreate(pCompare, NullFunction, NullFunction, NullFunction, NullFunction);
}
