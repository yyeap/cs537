#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "reader.h"
#include "munch1.h"
#include "munch2.h"
#include "writer.h"
#include "synchq.h"

#define THREADS 4
#define QUEUES 4

int main(int argc, char **argv)
{
  int i;
  pthread_t thr[THREADS];
  void* q[QUEUES];
  sem_t input_ready;

  /* initialize queues */
  i = 0;
  while (i < QUEUES - 1)
  {
    if (NULL == (q[i] = (sq*)malloc(sizeof(sq))))
    {
        printf("Error initializing queue.\n");
        return -1;
    }
    sq_init(q[i]);
    i++;
  }

  if(0 > sem_init(&input_ready, 0, 1))
  {
    printf("Error initializing semaphore\n");
    return -1;
  }
  q[3] = &input_ready;

  /* create threads */
  if(pthread_create(&thr[0], NULL, &reader, q))
  {
    printf("Could not create reader\n");
    return -1;
  }

  if(pthread_create(&thr[1], NULL, &munch1, q))
  {
    printf("Could not create munch1\n");
    return -1;
  }

  if(pthread_create(&thr[2], NULL, &munch2, q))
  {
    printf("Could not create munch2\n");
    return -1;
  }

  if(pthread_create(&thr[3], NULL, &writer, q))
  {
    printf("Could not create writer\n");
    return -1;
  }

  /* join threads */
  if(pthread_join(thr[0], NULL))
  {
    printf("Could not join reader\n");
    return -1;
  }

  if(pthread_join(thr[1], NULL))
  {
    printf("Could not join munch1\n");
    return -1;
  }

  if(pthread_join(thr[2], NULL))
  {
    printf("Could not join munch2\n");
    return -1;
  }

  if(pthread_join(thr[3], NULL))
  {
    printf("Could not join writer\n");
    return -1;
  }

  /* destroy synchronized queues and input semaphore */
  i = 0;
  while(i < 3)
  {
    sq_destroy(q[i]);
    free((void*)q[i]);
    i++;
  }
  sem_destroy(q[3]);
  free((void*)q[3]);
  pthread_exit(NULL);
  return 0;
}
