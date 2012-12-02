#include "scheduler.h"
/*
stcp.c
*/

//Process cpu time comparison for rb tree
int pCompare(const void* a, const void* b){
  if(a->CPU_time > b->CPU_time) return 1;
  if(a->CPU_time < b->CPU_time) return -1;
  return 0;
} 
// empty function for rb tree
void infoprint(void* a) {
  ;
}
// empty function for rb tree
void keyprint(void* a) {
  ;
}
// emtpy function for rb tree
void infodest(void* a) {
  ;
}

void add_process(process* new_p, void* q) {
  // insert with priority being smallest CPU
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
  q = (void*)RBTreeCreate(pCompare, DestroyProcess, infodest, keyprint, infoprint);
}
