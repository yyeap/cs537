#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "process.h"
#include "input.h"

#define CMD_SIZE 10
#define MAXINT 20
#define BASE 10
#define MILLI 1000
#define IOSIZE 8192

static struct Process *p;
static int eof;
static int hasNewProcess = 1;

/* Initialize private member in input */
void input_init()
{
    p = (struct Process*)malloc(sizeof(struct Process));

    if (NULL == p)
    {
        printf("Error allocating process.");
        fflush(stdout);
        exit(-1);
    }
    eof = 0;
    hasNewProcess = 1;
}

/* get the next tracefile line */
void get_next_line()
{
    char c, cmd[CMD_SIZE], start[MAXINT], CPU[MAXINT], IONum[MAXINT];
    int ct, nameFlag, startFlag, cpuFlag, ioCountFlag;
    long arrival, ioOps, cpuRemain, ioBytes;
    double cpu;

    /* initialize line segment flags */
    nameFlag = 0;
    startFlag = 0;
    cpuFlag = 0;
    ioCountFlag = 0;
    ct = 0;

    /* read command name */
    while(1)
    {
        c = fgetc(stdin);

        /* set EOF flag if reach end of file */
        if (feof(stdin))
        {
            eof = 1;
        }

        /* break if EOF */
        if (eof)
        {
            return;
        }

        if (' ' == c || '\t' == c)
        {
            cmd[ct] = '\0';

            /* skip all spaces between input segments */
            while (' ' == c || '\t' == c)
            {
                c = fgetc(stdin);
            } /* c will contain the first character of arrival time at the end of the last iteration */

            nameFlag = 1;
        }
        else
        {
            cmd[ct++] = c;
        }

        if (nameFlag)
        {
            break;
        }
    } /* end of command name while loop */

    ct = 0; /* reset segment start index */

    /* read arrival time */
    while(1)
    {
        if (' ' == c || '\t' == c)
        {
            start[ct] = '\0';

            while (' ' == c || '\t' == c)
            {
                c = fgetc(stdin);
            } /* c contains first character of CPU time */

            startFlag = 1;
        }
        else
        {
            start[ct++] = c;
            c = fgetc(stdin);
        }

        if (startFlag)
        {
            break;
        }
    } /* end of arrival time while loop */

    ct = 0; /* reset segment start index */

    /* read CPU time */
    while (1)
    {
        if (' ' == c || '\t' == c)
        {
            CPU[ct] = '\0';

            while (' ' == c || '\t' == c)
            {
                c = fgetc(stdin);
            }

            cpuFlag = 1;
        }
        else
        {
            CPU[ct++] = c;
            c = fgetc(stdin);
        }

        if (cpuFlag)
        {
            break;
        }
    }

    ct = 0; /* reset segment start index */

    /* read IO count */
    while (1)
    {
        if ('\n' == c)
        {
            IONum[ct] = '\0';
            ioCountFlag = 1;
        }
        else
        {
            IONum[ct++] = c;
            c = fgetc(stdin);
        }

        if (ioCountFlag)
        {
            break;
        }
    } /* end of IO count loop */

    /* sanitize input buffers */
    arrival = strtol(start, NULL, BASE);
    cpu = strtod (CPU, NULL);
    cpuRemain = cpu * MILLI;
    ioBytes = strtol(IONum, NULL, BASE);

    /* perform relevant calculations for process fields */
    ioOps = (long)((ioBytes + IOSIZE - 1) / IOSIZE);

    if (ioOps > cpuRemain)
    {
        p->next_io_time = 1;
        p->IO_interval = 1;
    }
    else
    {
        /* if there is no IO operations */
        if (0 == ioOps)
        {
            p->next_io_time = -1;
            p->IO_interval = -1;
        }

        /* IO should occur in the middle */
        /* divide by 2 to make it happen */
        else if (1 == ioOps)
        {
            p->next_io_time = cpuRemain / 2;
            p->IO_interval = cpuRemain / 2;
        }

        /* if IO operatios does not divide evenly */
        else if (!(cpuRemain % ioOps))
        {
            p->next_io_time = (cpuRemain - (cpuRemain % ioOps)) / ioOps;
            p->IO_interval = (cpuRemain - (cpuRemain % ioOps)) / ioOps;
        }

        else
        {
            p->next_io_time = cpuRemain / ioOps;
            p->IO_interval = cpuRemain / ioOps;
        }
    }

    p->arrival = arrival;
    p->cpu_remaining = cpuRemain;
    p->IO_remaining = ioOps;
    p->lastRunTime = 0;
    p->priority = 0;
}

/* get the arrival time of next process. Returns -1 if EOF */
long get_arrival()
{
    /* if a new process arrives, get next tracefile line */
    if (hasNewProcess)
    {
        p = (struct Process*)malloc(sizeof(struct Process));

        if (NULL == p)
        {
            printf("ERROR: Fail to malloc new process.");
            exit(-1);
        }

        p->arrival = 0;
        p->cpu = 0;
        p->IO_count = 0;
        p->priority = 0;
        p->lastRunTime = 0;
        p->cpu_remaining = 0;
        p->IO_remaining = 0;
        p->IO_interval = 0;
        p->IO_operations = 0;
        p->IO_complete = 0;
        p->next_io_time = 0;
        p->completion_time = 0;

        get_next_line();
        hasNewProcess = 0;
        if (eof)
        {
            return -1;
        }
    }
    return p->arrival;
}

struct Process* get_next_process()
{
    hasNewProcess = 1;
    return p;
}

void input_destroy()
{
    free(p);
}
