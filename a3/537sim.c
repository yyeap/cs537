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
#include "input.h"

int main (int argc, char* argv[]){
  struct Process* current_process = NULL;
  struct Process* next_process = NULL;
  disk* disk;
  void* q;
  stats* stats;
  long clock = 0;
  long io;
  long ts;
  long ar;
  int* reason;

  if (2 != argc){
    printf("ERROR: Wrong number of parameter. Need one argument.");
    return -1;
  }

  init_stats(stats);
  init_disk(disk);
  init_q(q);
  
  while(1) {
    if (NULL != current_process) {
      clock++;
      update_io_remain(disk, 1); 
    }

    io = get_IO_complete(disk, clock);
    ts = get_timeslice(clock, q, reason);
    ar = get_arrival();

    /*EVENT simulation completed*/
    if(ar == -1 && ts == -1) {
      //display stats, destroy and exit
      exit(0);
    }
    
    /*EVENT io has been completed*/
    if(io == 1) {
      clock += io;
      update_io_remain(disk, io);
      add_process(q, get_next_io(disk));
    }
    /*EVENT timeslice ends next*/
    else if (ts <= io && ts <= ar) {
      clock += ts;
      /*determine reason for timeslice
	if IO, add process to disk*/
      if(*reason == 2){
	io_add_process(disk, get_process(q));
      }
      else if (*reason == 0) {
	/*if done, collect statistics*/
      }
      else if(*reason == 1) {
	/*if timeslice ended, return to queue*/
      }
      update_io_remain(disk, ts);
    } 
    /*EVENT new process arrival*/
    else {
      clock += ar;
      update_io_remain(disk, ar);
      add_process(q, get_next_process());
      
    }
  }
  return 0;
}
