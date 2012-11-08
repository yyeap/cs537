#include <semaphore.h>

typedef struct synchq {
  char** data;
  int head;
  int size;
  int done;
  sem_t open;
  sem_t filled;
  sem_t mutex;
} sq;

/*
* sq_init
*
* initializes the given queue
*
* in: q - sq* - a sq pointer to the queue to be initialized
*/
extern void sq_init(sq* q);

/*
* sq_enq
*
* performs the enqueue operation on a given queue
*
* in: q - sq* - a sq pointer to the queue to be enqueued upon
*     new_item - char* - char* to be enqueued
*/
extern void sq_enq(sq* q, char* new_item);

/*
* sq_deq
*
* performs the dequeue operation on a given queue
*
* in: q - sq* - a sq pointer to the given queue
* returns: char* value that was dequeued
*/
extern void* sq_deq(sq* q);

/*
* sq_isEmpty
*
* performs the dequeue operation on a given queue
*
* in: q - sq* - a sq pointer to the given queue
* returns: true if q is empty, otherwise false
*/
extern int sq_isEmpty(sq* q);

/*
* sq_destroy
*
* destroys the given queue
*
* in: q - sq* - a sq pointer to the given queue
*/
extern void sq_destroy(sq* q);

/*
* sq_done
*
* sets the queue's 'done' flag to 1
*
* in: q - sq* - a sq pointer to the given queue
*/
extern void sq_done(sq* q);

/*
* sq_isDone
*
* returns queue's 'done' flag value
*
* in: q - sq* - a sq pointer to the given queue
* return: value of 'done'
*/
extern int sq_isDone(sq* q);
