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

void (*add_process)(struct Process*);
struct Process* (*get_process)(void);
long (*get_timeslice)(long, int*);
void (*init_q)(void);

int main (int argc, char* argv[]){
  struct Process* current_process;
  struct Process* temp_process;
  long clock = 0;
  long io = 0;
  long ts = 0;
  long ar = 0;
  long stepTime = 0;
  int reason;

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

  if(!strncmp(argv[1], "expq", 4)){
    add_process = expq_add_process;
    get_process = expq_get_process;
    get_timeslice = expq_get_timeslice;
    init_q = expq_init_q;
    printf("Running simulator with EXPQ\n");
  } else {
    printf("Running simulator with STCF\n");
  }

  init_stats();
  init_disk();
  init_q();
  current_process = NULL;
  temp_process = NULL;
  reason = 0;

  while(1) {
    if (NULL != current_process) {
      clock++;
      update_io_remain(1);
    }

    io = get_IO_complete();
    ts = get_timeslice(clock, &reason);
    ar = get_arrival();

    /*EVENT simulation completed*/
    if(ar == -1 && ts == -1) {
      /*display stats, destroy and exit*/
      displayStats(clock);
      free(current_process);
      free(temp_process);
        exit(0);
    }

    if (ar <= clock)
    {
        if (current_process != NULL)
        {
            current_process = get_process();
            current_process->cpu_remaining -= (ar - clock);
            current_process->lastRunTime += (ar - clock);
            add_process(current_process);
        }
        /* fetch new process from trace */
        current_process = get_next_process();
        add_process(current_process);
    }
    else
    {
        /* stepTime = min (io, ts, ar - clock) */
        if (io <= ts && io <= (ar - clock))
        {
            stepTime = io;
        }

        else if (ts <= io && ts <= (ar - clock))
        {
            stepTime = ts;
        }

        else
        {
            stepTime = ar - clock;
        }

        if (stepTime == io && stepTime != -1)
        {
            temp_process = get_next_io();
            add_process(temp_process);
            clock += stepTime + 1;
        }

        else if (stepTime == ts)
        {
            switch (reason)
            {
                case 0:
                    temp_process = get_process();
                    temp_process->cpu_remaining -= ts + 1;
                    temp_process->lastRunTime += ts;
                    io_add_process(temp_process);
                    clock += ts + 1;
                    break;
                case 1:
                    current_process = get_process();
                    updateStats(current_process, clock);
                    break;

                case 2:
                    temp_process = get_process();
                    temp_process->cpu_remaining -= ts;
                    temp_process->lastRunTime += ts;
                    add_process(temp_process);
                    break;
                default:
                    printf("Unexpected error\n");
                    exit(-1);
            }
        }
    }
  }
  return 0;
}
