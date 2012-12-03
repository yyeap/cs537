#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "process.h"

extern Process* CreateProcess(char* name, long arrival, long cpu, long IOCount){
    Process *p = (Process*)malloc(sizeof(Process));
    if(NULL == p){
        printf("ERROR: Cannot allocate memory in malloc.");
        return NULL;
    }

    p->name = name;
    p->arrival = arrival;
    p->cpu = cpu;
    p->IO_count = IOCount;
    return p;
}

extern void DestroyProcess (Process *p)
{
    free(p);
    /* might need to deallocate more resource */
}
