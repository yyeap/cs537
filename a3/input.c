/*
Yuen Lye Yeap
Lee Yerkes
cs537 Project 3

input.c
*/

void parseTrace(char* line, char* name, int* start_time, int* cpu_time, int* io_count)
{
  name = strtok(line, " ");
  start_time = atoi(strtok(NULL, " "));
  cpu_time = atoi(strtok(NULL, " "));
  io_count = atoi(strtok(NULL, " "));
}
