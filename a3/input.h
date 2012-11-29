/*
Yuen Lye Yeap
Lee Yerkes
cs537 Project 3

input.h

*/
#include <string.h>
#include "process.h"

/*
parseTrace

this function parses one line of a trace file

in:
char* line - a line from the trace file to be parsed

out:
char* name - the name of job
int* start_time - start time of job
int* cpu_time - cpu time of job
int* io_count - number of bytes of IO done by job

return:
none
 */
void parseTrace(char* line, char* name, int* start_time, int* cpu_time, int* io_count);

process* get_arrival(FILE* f, Process* buffer);
