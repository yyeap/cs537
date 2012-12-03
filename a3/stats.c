/*
Yuen Lye Yeap
Lee Yerkes
stats.c

Header file for statistics functions
*/
#include <stdio.h>
#include <limits.h> /* for min and max int values */
#include "stats.h"
#include "process.h"

extern void stats_init (stats* data)
{
    data->total_ct = 0;
    data->min_ct = INT_MIN;
    data->max_ct = INT_MAX;
    data->jobs = 0;
    data->total_time = 0;
}

extern void updateStats(stats* data, Process* p, int clock)
{
    int ct;

    ct = clock - p->arrival;
    data->total_ct += ct;

    if (ct < data->min_ct)
    {
        data->min_ct = ct;
    }

    if (ct > data->max_ct)
    {
        data->max_ct = ct;
    }

    data->jobs++;
    data->total_time += p->cpu;

    free(p);
}

extern void displayStats (stats* data, int clock)
{
    printf("Average completion time: %.2f\n", (float)data->total_ct / data->jobs);
    printf("Minimum completion time: %d\n", data->min_ct);
    printf("Maximum completion time: %d\n", data->max_ct);
    printf("Throughput: %.2f\n", (float)(data->jobs / clock) / 1000);
    printf("Utilization: %d\tPercent utilization: %.2f\n", data->total_time, (float)data->total_time / clock);

    /* free up data structures */
    free(data);
}
