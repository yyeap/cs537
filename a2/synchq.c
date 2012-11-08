#include <stdio.h>
#include <stdlib.h>
#include "synchq.h"

#define MAX_SIZE 10

void sq_init(sq* q)
{
  if(NULL == (q->data = (char**)malloc(MAX_SIZE * sizeof(char*))))
  {
    printf("Error initializing queue.\n");
    return;
  }
  q->head = 0;
  q->size = 0;
  q->done = 0;

  if(0 > sem_init(&q->open, 0, MAX_SIZE))
  {
    printf("Error initializing sem open\n");
    return;
  }
  if (0 > sem_init(&q->filled, 0, 0))
  {
    printf("Error initializing sem filled\n");
    return;
  }
  if (0 > sem_init(&q->mutex, 0, 1))
  {
    printf("Error initializing sem mutex\n");
    return;
  }
}

void sq_enq(sq* q, char* new_item)
{
  sem_wait(&q->open); /*wait for space for an element*/
  sem_wait(&q->mutex); /*enter critical section*/

  /*enqueue the new item*/
  q->data[(q->head + q->size) % MAX_SIZE] = new_item;
  q->size++;

  /*indicate that a space was filled*/
  sem_post(&q->mutex); /*leave critical section*/
  sem_post(&q->filled);
}

void* sq_deq(sq* q)
{
  int loc;
  
  sem_wait(&q->filled); /*wait for an available item*/
  sem_wait(&q->mutex); /*enter critical section*/

  /*dequeue the item*/
  loc = q->head;
  q->size--;
  q->head = (q->head + 1) % MAX_SIZE;
 
  sem_post(&q->mutex); /*leave critical section*/
  sem_post(&q->open); /*indicate that space for an element was opened*/

  return (void*)q->data[loc];
}

int sq_isEmpty(sq* q)
{
  return 0 == q->size;
}

void sq_destroy(sq* q)
{ 
  sem_destroy(&q->mutex);
  sem_destroy(&q->open);
  sem_destroy(&q->filled);
  free(q);
}

void sq_done(sq* q)
{
  q->done = 1;
}

int sq_isDone(sq* q)
{
  return q->done;
}
