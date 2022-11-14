#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int value;
    struct Node* next;
    struct Node* previous;
};

/**
 * @brief Return value at specified index 
 * * O(n) 
 */
int value_at(struct Node* head, int index) {
    struct Node* current;
    int listIndex = 0;

    for(current = head; current != NULL; current = current->next) {
        if (listIndex == index) return current->value;

        listIndex++;
    }

    return -1;
}

/**
 * @brief Insert value at index
 * * O(n)
 */
void insert(struct Node* head, int value, int index) {
    struct Node* current;
    int listIndex = 0;

    for(current = head; current != NULL; current = current->next) {
        if (listIndex == index) {
            struct Node *newNode = malloc(sizeof(struct Node));
            newNode->value = value;
            newNode->next = current->next;
            newNode->previous = current;

            current->next = newNode;
            current->next->previous = newNode;
            break;
        }

        listIndex++;
    }
}

/**
 * @brief Append the value at the end of the list
 * * O(n)
 */
void append(struct Node* head, int value) {
    struct Node *current;

    for(current = head; current != NULL; current = current->next) {
        if(current->next == NULL) {
             struct Node *newNode = malloc(sizeof(struct Node));
             newNode->value = value;
             newNode->previous = current;
             current->next = newNode;
             break;
        }
    }
};

/**
 * @brief Extract the last element of the list
 * * O(n) -> 0(1) with tail pointer 
 */
int pop(struct Node* head) {
    struct Node *current;
    int lastValue;
    

    for (current = head; current != NULL; current = current->next) {
        lastValue = current->value;

        // On the last element, we remove his pointer from the previous element
        if (current->next == NULL) {
            current->previous->next = NULL;
            free(current);
        }
    }

    return lastValue;
};

/**
 * @brief Return the list size
 * * O(n)
 */
int size(struct Node* head) {
    struct Node* current;
    int size = 0;

    for (current = head; current != NULL; current = current->next) {
        size++;
    }

    return size;
}

/**
 * @brief Get the first value in the list
 * * O(1)
 */
int front(struct Node* head) {
    return head->value;
}

/**
 * @brief Get the last element of the list
 * * O(n) -> 0(1) with tail pointer 
 */
int back(struct Node* head) {
    struct Node* current;

   for (current = head; current != NULL; current = current->next) {
    if (current->next == NULL) return current->value;
   }

   return -1;
}

bool is_empty(struct Node* head) {
    return head->next == NULL;
}

void clear_list(struct Node* head) {
    struct Node *current;

     for(current = head; current != NULL; current = current->next) {
       free(current);
    }
}

int main() {
    struct Node *head = malloc(sizeof(struct Node));

    append(head, 200);
    append(head, 300);

    // insert(head, 22, 0);

    // int value = value_at(head, 2);

    // int last = pop(head);
    // printf("Element value is : %i\n", value);

    struct Node *current;
    printf("[ ");
    for (current = head; current != NULL; current = current->next) printf("%i, ", current->value);
    printf("]\n");

    printf("Linked list informations : { size: %i, is_empty : %s }\n", size(head), is_empty(head) ? "true" : "false");

    clear_list(head);

    return 0;
};