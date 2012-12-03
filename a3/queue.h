
typedef struct node {
    struct node *next;
    struct Process* data;
}node;

typedef struct queue {
    struct node *head;
    struct node *tail;
}queue;

void q_init(queue* q);

int enqueue(queue *q, struct Process *p);

struct Process* dequeue(queue *q);

int q_isEmpty(queue* q);

struct Process* peek (queue* q);
