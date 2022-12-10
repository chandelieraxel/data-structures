#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int value;
    struct Node *next;
};

struct Queue {
    struct Node *startPtr, *endPtr;
};

struct Queue* createQueue() {
    struct Queue *q =  malloc(sizeof(struct Queue));
    q->startPtr = NULL;
    q->endPtr = NULL;

    return q;
};

void enqueue(struct Queue* q, int value) {
    struct Node *node = malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;

    // Init case
    if (q->startPtr == NULL && q->endPtr == NULL) {
        q->startPtr = node;
        q->endPtr = node;
    } else {
        // Enqueue at the end to avoid traversal from start
        q->endPtr->next = node;
        q->endPtr = node;
    }
}

int dequeue(struct Queue* q) {
    if (q->startPtr == NULL && q->endPtr == NULL) {
        printf("Queue is empty, cannot dequeue\n");
        return -1;
    }

    struct Node* nodeToDelete = q->startPtr;
    int valueToReturn = nodeToDelete->value;

    // If this is the last element of the queue
    if (!q->startPtr->next) {
        q->endPtr = NULL;
        q->startPtr = NULL;
    } else {
        // Otherwise dequeue from start
        q->startPtr = q->startPtr->next;
    }

    free(nodeToDelete);

    return valueToReturn;
}

void clearQueue(struct Queue* q) {
    while (q->startPtr != NULL) dequeue(q);

    free(q);
}


int main() {
    int choice = 0;
    int buffer= 0;

    struct Queue *queue = createQueue();

    printf("This is a queue implementation. What do you wish to do ?\n");
    while (1) {
        printf("\n");
        printf("-----------------------------------------------------------\n");
        printf("1 -> Insert an element into the queue\n");
        printf("2 -> Process the next element (print to stdout and remove it)\n");
        printf("3 -> Exit\n");
        printf("-----------------------------------------------------------\n");
        printf("\n");
        printf("Your choice : ");
        scanf("%i", &choice);

        switch (choice)
        {
        case 1:
            printf("Please enter the integer you wish to add : ");
            scanf("%i", &buffer);
            enqueue(queue, buffer);
            printf("\n");
            break;
        case 2:
            printf("%i has been removed from the queue\n", dequeue(queue));
            break;
        case 3:
            clearQueue(queue);
            exit(0);
            break;
        default:
            exit(-1);
            break;
        }

    }
}