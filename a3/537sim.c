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
#include "queue.h"

int main (int argc, char* argv[]){
  struct Process* current_process = NULL;
  struct Process* next_process = NULL;
  disk* disk;
  queue* q;
  stats* stats;
  int eof = 0;
  long clock = 0;
  long io;
  long ts;
  long ar;
  FILE* tracefile;
  int reason;
  int done = 0;

  if (2 != argc){
    printf("ERROR: Wrong number of parameter. Need one argument.");
    return -1;
  }

  init_stats(stats);
  init_disk(disk);
  init_queue(q);

  /* read tracefile from input module */

  while(!eof) {
    if (NULL != current_process) {
      clock++;
      update_io_remain(disk, 1); 
    }

    io = get_IO_Complete(disk, clock);
    ts = get_timeslice(q, reason);
    ar = get_arrival(FILE, process_buffer);
        
    if(io == 1) {

    if(io <= ts && io <= ar) {
      clock += io;
      update_io_remain(disk, io);
      add_process(q, get_next_io(disk));
    }
    else if (ts <= io && ts <= ar) {
      clock += ts;
      /*determine reason for timeslice
      if IO, add process to disk*/
      if(reason == 2){
	io_add_process(disk, get_process(q));
      }
      else if (reason == 0) {
	/*if done, collect statistics*/
      }
      else if(reason == 1) {
	/*if timeslice ended, return to queue*/
      }
      update_io_remain(disk, ts);
    } 
    else {
      clock += ar;
      update_io_remain(disk, ar);
      add_process(q, get_next_process());
      
    }
    else {
      clock += ar;
    }
  }
  return 0;
}
