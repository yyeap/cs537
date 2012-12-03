/*
Yuen Lye Yeap
Lee Yerkes

537sim.c

Contains implementation of simulator main loop and stuff.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "stcf.h"
#include "expq.h"
#include "stats.h"
#include "scheduler.h"
#include "disk.h"
#include "input.h"

int main (int argc, char* argv[]){
  struct Process* current_process = NULL;
  struct Process* next_process = NULL;
  disk* disk = NULL;
  void* q = NULL;
  stats* stats = NULL;
  long clock = 0;
  long io = 0;
  long ts = 0;
  long ar = 0;
  int* reason = NULL;

  /*use STCF by default*/
  void (*add_process)(struct Process* p, void* q) = stcf_add_process;
  struct Process* (*get_process)(void* q) = stcf_get_process;
  long (*get_timeslice)(long c, void* q, long* r) = stcf_get_timeslice;
  void (*init_q)(void* q) = stcf_init_q;
  
  if (2 < argc){
    printf("ERROR: 537sim only takes one argument.");
    exit(-1);
  }

  /*use EXPQ algorithm functions if specified*/
  /*if user passes bad parameter, just use STCF*/
  if(!strncmp(argv[1], "expq", 4)){
    void (*add_process)(struct Process* p, void* q) = expq_add_process;
    struct Process* (*get_process)(void* q) = expq_get_process;
    long (*get_timeslice)(long c, void* q, long* r) = expq_get_timeslice;
    void (*init_q)(void* q) = expq_init_q;
    printf("Running simulator with EXPQ");
  } else {
    printf("Running simulator with STCF");
  }
  
  init_stats(stats);
  init_disk(disk);
  init_q(q);
  
  while(1) {
    if (NULL != current_process) {
      clock++;
      update_io_remain(disk, 1); 
    }

    io = get_IO_complete(disk);
    ts = get_timeslice(clock, q, reason);
    ar = get_arrival();

    /*EVENT simulation completed*/
    if(ar == -1 && ts == -1) {
      //display stats, destroy and exit
      exit(0);
    }
    
    /*EVENT io has been completed*/
    if(io <= ts && io <= ar-clock) {
      clock += io;
      update_io_remain(disk, io);
      add_process(q, get_next_io(disk));
    }
    /*EVENT timeslice ends next*/
    else if (ts <= io && ts <= ar-clock) {
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
      clock += ar-clock;
      update_io_remain(disk, ar-clock);
      add_process(q, get_next_process());
    }
  }
  return 0;
}
