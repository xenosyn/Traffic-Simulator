#include "Queue.h"

static node_t *head (int val);

/*struct that contains the value of the time and pointer to the next*/


/* queues the vehicle by pointing it to the previous car/start of the queue*/
extern void enqueue(node_t **head, int val) {
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) return;

    new_node->val = val;
    new_node->next = *head;

    *head = new_node;
}

/* removes the vehicle from the queue and returns the time of entry*/
extern int dequeue(node_t **head) {
    node_t *current, *prev = NULL;
    int retval = -1;

    if (*head == NULL) return -1;

    current = *head;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    retval = current->val;
    free(current);
    
    if (prev)
        prev->next = NULL;
    else
        *head = NULL;

    return retval;
}

/* checks if queue is empty */
extern int isEmpty(node_t **head){
    if (*head == NULL)
        return 1;
    else
       return 0;

}