/*
Yuen Lye Yeap
Lee Yerkes
stats.h

Header file for statistics functions
*/

typedef struct stats{
	int total_ct;
	int min_ct;
	int max_ct;
	int jobs;
	int total_time;
}stats;

extern void stats_init (stats* data);

extern void updateStats (stats* data, Process* p, int clock);

extern void displayStats (stats* data, int clock);
/*Average Completion Time*/
/*Minimum Completion Time*/
/*Maximum Completion Time*/
/*Throughput (jobs per second)*/
/*Utilization*/
