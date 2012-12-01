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
    struct process *next;
    struct process *prev;
} Process;

extern Process* CreateProcess(char* name, int arrival, int cpu, int IO_count);

extern void DestroyProcess(Process* p);

extern void setName (Process* p, char* name);

extern char* getName (Process* p);

extern void setArrival (Process* p, int arrival);

extern int getArrival (Process* p);

extern void setCpu(Process*p, int cpu);

extern int getCpu (Process* p);

extern void setIO_count (Process* p, int io);

extern int getIO_count (Process* p);

extern void setCpu_remaining (Process* p, int remain);

extern int getCpu_remaining (Process* p);

extern void setIO_remaining (Process* p, int remain);

extern int getIO_remaining (Process* p);

extern void setIO_interval (Process* p, int interval);

extern int getIO_interval (Process* p);

extern void setIO_operations (Process* p, int op);

extern int getIO_operations (Process* p);

extern void setIO_complete (Process* p, int clock);

extern int getIO_complete (Process* p);

extern void setNext (Process*p, Process* next);

extern Process* getNext (Process* p);

extern void setPrev (Process* p, Process* prev);

extern Process* getPrev(Process* p);
