#include <string.h>
#include <stdio.h>
#include <strings.h>
#include "munch1.h"
#include "synchq.h"

void *munch1 (void* q)
{
    sq** queues = (sq**)q;

    /*get string from q0 */
    char *str, *curr;

    while(!sq_isDone(queues[0]) || !sq_isEmpty(queues[0])) /* while not EOF */
    {
        if (NULL == (str = sq_deq(queues[0])))
        {
            printf("ERROR: Failed to get string from q1.");
            return NULL;
        }
        curr = index(str, ' ');
        while (NULL != curr)
        {
            *curr = '*';
            curr = index(str, ' ');
        }
        /* put string on q1 */
        sq_enq(queues[1], str);
    }
    sq_done(queues[1]); /* set done flag on the next queue */
    return NULL;
}

