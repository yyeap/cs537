#include <stdio.h>

typedef struct process {
    char* name;
    long arrival;
    long cpu;
    long IO_count;
    long priority;
    long lastRunTime;
    long cpu_remaining;
    long IO_remaining;
    long IO_interval;
    long IO_operations;
    long IO_complete;
    long next_io_time;
    long completion_time;
} Process;

extern Process* CreateProcess(char* name, long arrival, long cpu, long IO_count);

extern void DestroyProcess(Process *p);
