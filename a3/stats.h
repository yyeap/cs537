/*
Yuen Lye Yeap
Lee Yerkes
stats.h

Header file for statistics functions
*/

typedef struct stats{
	long total_ct;
	long min_ct;
	long max_ct;
	long jobs;
	long total_time;
}stats;

void init_stats ();

void updateStats (struct Process *p, long clock);

void displayStats (long clock);
