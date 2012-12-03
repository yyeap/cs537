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
#include "disk.h"
#include "input.h"

void (*add_process)(struct Process*, void*);
struct Process* (*get_process)(void*);
long (*get_timeslice)(long, void*, int*);
void (*init_q)(void*);

int main (int argc, char* argv[]){
  struct Process* current_process;
  void* q;
  stats* stats;
  long clock = 0;
  long io = 0;
  long ts = 0;
  long ar = 0;
  int* reason;

  /*use STCF by default*/
  add_process = stcf_add_process;
  get_process = stcf_get_process;
  get_timeslice = stcf_get_timeslice;
  init_q = stcf_init_q;

  if (2 < argc){
    printf("ERROR: 537sim only takes one argument.");
    exit(-1);
  }

  /*use EXPQ algorithm functions if specified*/
  /*if user passes bad parameter, just use STCF*/
  /*
  if(!strncmp(argv[1], "expq", 4)){
    add_process = expq_add_process;
    get_process = expq_get_process;
    get_timeslice = expq_get_timeslice;
    init_q = expq_init_q;
    printf("Running simulator with EXPQ");
  } else {
    printf("Running simulator with STCF");

  }*/

  init_stats(stats);
  init_disk();
  init_q(q);
  current_process = NULL;
  reason = NULL;

  while(1) {
    if (NULL != current_process) {
      clock++;
      update_io_remain(1);
    }

    io = get_IO_complete();
    ts = get_timeslice(clock, q, reason);
    ar = get_arrival();

    /*EVENT simulation completed*/
    if(ar == -1 && ts == -1) {
      /*display stats, destroy and exit*/
      exit(0);
    }

    /*EVENT io has been completed*/
    if(io <= ts && io <= ar-clock) {
      clock += io;
      update_io_remain(io);
      add_process(q, get_next_io());
    }
    /*EVENT timeslice ends next*/
    else if (ts <= io && ts <= ar-clock) {
      clock += ts;
      /*determine reason for timeslicet
	if IO, add process to disk*/
      if(*reason == 2){
	io_add_process(get_process(q));
      }
      else if (*reason == 0) {
	/*if done, collect statistics*/
      }
      else if(*reason == 1) {
	/*if timeslice ended, return to queue*/
      }
      update_io_remain(ts);
    }
    /*EVENT new process arrival*/
    else {
      clock += ar-clock;
      update_io_remain(ar-clock);
      add_process(q, get_next_process());
    }
  }
  return 0;
}
