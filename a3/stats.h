#include "process.h"
/*
Yuen Lye Yeap
Lee Yerkes
stats.h

Header file for statistics functions
*/

typedef struct{
	long total_ct;
	long min_ct;
	long max_ct;
	long jobs;
	long total_time;
}stats;

extern void stats_init (stats* data);

extern void updateStats (stats* data, Process* p, long clock);

extern void displayStats (stats* data, long clock);
