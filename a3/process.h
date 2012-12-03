#include <stdio.h>

typedef struct process {
    char* name;
    int arrival;
    int cpu;
    int IO_count;
    int cpu_remaining;
    int IO_remaining;
    int IO_interval;
    int IO_operations;
    int IO_complete;
} Process;

extern Process* CreateProcess(char* name, int arrival, int cpu, int IO_count);

extern void DestroyProcess(Process* p);
