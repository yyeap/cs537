#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "writer.h"
#include "synchq.h"

void* writer(void *q)
{
    sq** queues = (sq**)q; /* cast to array of queues */
    int count = 0;
    char *inputString;

    /* while not end of file, keep dequeue and print output */
    while (!sq_isDone(queues[2]) || !sq_isEmpty(queues[2]))
    {
        inputString = sq_deq(queues[2]);
        printf("Output: %s\n", inputString);
        count++;
        free(inputString); /* frees up buffer */
        /* show output and notify reader */
        sem_post((sem_t*)queues[3]);
    }

    /* after end of file */
    printf("Total number of lines: %d \n", count);
    return NULL;
}
