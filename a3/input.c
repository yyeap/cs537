#include <string.h>

/*
Yuen Lye Yeap
Lee Yerkes
cs537 Project 3

input.c
*/

Process*  traceToProcess(char* line)
{
  name = strtok(line, " ");
  start_time = atoi(strtok(NULL, " "));
  cpu_time = atoi(strtok(NULL, " "));
  io_count = atoi(strtok(NULL, " "));

  Process* p = CreateProcess(name, start_time, cpu_time, io_count);
  
  return p;
}
