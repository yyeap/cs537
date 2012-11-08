#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "munch2.h"
#include "synchq.h"

void * munch2 (void * q)
{
    sq** queues = (sq**)q;
    /* get string from the queue */
    char *inputString, *curr;
    while(!sq_isDone(queues[1]) || !sq_isEmpty(queues[1]))
    {
        if (NULL == (inputString = sq_deq(queues[1])))
        {
            printf("ERROR: Input is empty.");
            return NULL;
        }

        curr = inputString;

        while (*curr != '\0'){
            *curr = toupper(*curr);
            curr = curr + (sizeof(char));
        }
        /* push modified string to the queue */
        sq_enq(queues[2], inputString);
    }
    sq_done(queues[2]); /* set done flag on the next queue */
    return NULL;
}
