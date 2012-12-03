
/*
Yuen Lye Yeap
Lee Yerkes

537sim.c

Contains implementation of simulator main loop and stuff.
*/

#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "stats.h"
#include "scheduler.h"
#include "disk.h"

int main (int argc, char* argv[]){
  Process* current_process = NULL;
  Process* next_process = NULL;
  disk* disk;
  queue* q;
  stats* stats;
  long clock = 0;
  long io;
  long ts; 
  long ar;
  FILE* tracefile;
  
  if (2 != argc){
    printf("ERROR: Wrong number of parameter. Need one argument.");
    return -1;
  }

  init_stats(stats);
  init_disk(disk);
  init_queue(q);
  
  tracefile = fopen(arg[1],"r");
  if(NULL == tracefile) {
    printf("ERROR: bad trace file path");
    exit(-1);
  }
 
  while(!done) {
    if (NULL != current_process) {
      clock++;
    }
    
    io = get_IO_Complete(disk, clock);
    ts = get_timeslice(q);
    ar = get_arrival(FILE, process_buffer);
    
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
