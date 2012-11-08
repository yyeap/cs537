#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "synchq.h"

#define ARRAY_SIZE 64

void * reader(void *q)
{
  sq **queues = (sq**)q; /* cast to array of queues */
  FILE *in;
  char *input, c;
  int count, nullErr, atEOF, lineComplete;
  /*
    loop for input one line at a time
    loop inside this loop for each character individually
  */  
  in = stdin;
  while (!feof(in) /* && !ferror(in)*/)
  {
    /*
      create array to hold input
      create flags and counters
    */
    count = 0;
    nullErr = 0;
    atEOF = 0;
    lineComplete = 0;
    if(NULL == (input = (char*)malloc(ARRAY_SIZE * sizeof(char))))
    {
      printf("ERROR: Failure to allocate input buffer.\n");
      return NULL;
    }

    /* wait to prompt user for input */
    sem_wait((sem_t*)queues[3]);
    printf("Input string: ");
    /* loop for character */
    while ((!lineComplete && !nullErr) && !atEOF)
    {
      c = fgetc(in);
      if (EOF == c)
      {
        lineComplete = 1;
        atEOF = 1;
      }
      else if ('\0' == c)
      {
        nullErr = 1;
      }
      else if ('\n' == c)
      {
        lineComplete = 1;
      }
      else if(count < ARRAY_SIZE)
      {
        input[count] = c;
        count++;
      }
    }
    if(!nullErr)
    {
      input[count] = '\0';
      sq_enq(queues[0], input);
    }
  }
  sq_done(queues[0]);
  fclose(in);
  exit(1);
}
