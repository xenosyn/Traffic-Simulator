#ifndef __QUEUE__
#define __QUEUE__ 1

#include <stdio.h>
#include <stdlib.h>

/*----- structure definition -------------------------------------------------*/

struct node {
    int val;
    struct node *next;
};

typedef struct node node_t;
/*----- function prototypes --------------------------------------------------*/
extern void enqueue(node_t **, int);
extern int dequeue(node_t **);
extern int isEmpty(node_t **);

#endif


