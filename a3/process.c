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
}

extern void setName (Process* p, char* name)
{
    p->name = name;
}

extern char* getProcessName(Process* p)
{
    return p->name;
}

extern void setArrival (Process* p, int arrival)
{
    p->arrival = arrival;
}

extern int getArrival (Process* p)
{
    return p->arrival;
}

extern void setCpu (Process* p, int cpu)
{
    p->cpu = cpu;
}

extern int getCput (Process* p)
{
    return p->cpu;
}

extern void setIO_count (Process* p, int io)
{
    p->IO_count = io;
}

extern int getIO_count (Process* p)
{
    return p->IO_count;
}

extern void setCpu_remaining (Process* p, int remain)
{
    p->cpu_remaining = remain;
}

extern int getCpu_remaining (Process* p)
{
    return p->cpu_remaining;
}

extern void setIO_remaining (Process* p, int remain)
{
    p->IO_remaining = remain;
}

extern int getIO_remaining (Process* p)
{
    return p->IO_remaining;
}

extern void setIO_interval (Process* p, int interval)
{
    p->IO_interval = interval;
}

extern int getIO_interval (Process* p)
{
    return p->IO_interval;
}

extern void setIO_operations (Process* p, int op)
{
    p->IO_operations = op;
}

extern int getIO_operations (Process* p)
{
    return p->IO_operations;
}

extern void setNext(Process* p, Process* next)
{
    p->next = next;
}

extern Process* getNext(Process* p)
{
    return p->next;
}

extern void setPrev(Process* p, Process* prev)
{
    p->prev = prev;
}

extern Process* getPrev(Process* p)
{
    return p->prev;
}
