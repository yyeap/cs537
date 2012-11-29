/*
Yuen Lye Yeap
Lee Yerkes

537sim.c

Contains implementation of simulator main loop and stuff.
*/

/*INITIALIZATION

Process* current_process = NULL;
stats* stats;
init_stats(stats);
queue* q;
init_queue(q);
int clock = 0;
int io;
int ts; 
int ar;
*/
int main (int argc, char* argv[]){
  if (2 != argc){
    printf("ERROR: Wrong number of parameter. Need one argument.");
    return -1;
  }
  while(!done) {
    if (NULL != current_process) {
      clock++;
    }
    
    io = get_IO_Complete();
    ts = get_timeslice(q);
    ar = get_arrival();
    
    clock += min(io, ts, ar);
    
    if(io <= ts && io <= ar) {
      clock += io;
    }
    else if (ts <= io && ts <= ar) {
      clock += ts;
    } 
    else {
      clock += ar;
      current_process;
    }
  }

  return 0;
}
