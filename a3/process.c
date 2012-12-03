#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "process.h"

extern Process* CreateProcess(char* name, int arrival, int cpu, int IOCount){
    Process *p = (Process*)malloc(sizeof(Process));
    if(NULL == p){
        printf("ERROR: Cannot allocate memory in malloc.");
        return NULL;
    }

    setName(p, name);
    setArrival(p, arrival);
    setCpu(p, cpu);
    setIO_count(p, IOCount);
    setIO_operations(p, trunc((IOCount + 8191) / 8192));
    return p;
}

extern void DestroyProcess(Process* p)
{
    free(p);
    /*is there nothing else to do with this? pretty sure we need to deallocate each member*/
}
