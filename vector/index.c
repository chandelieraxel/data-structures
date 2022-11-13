#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BASE_VECTOR_CAPACITY 4
#define MAX_VECTOR_SIZE 1024

struct Vector {
    int size;
    int capacity;
    int* array;
};

struct Vector* initVector() {
    struct Vector* vector = (struct Vector*)malloc(sizeof(struct Vector));
    int* array = malloc(BASE_VECTOR_CAPACITY * sizeof(int));
    
    vector->capacity = BASE_VECTOR_CAPACITY;
    vector->size = 0;
    vector->array = array;

    return vector;
};

bool is_empty(struct Vector* vector) {
    if (vector->size == 0) return true;
    return false;
};

bool is_out_of_bounds(struct Vector* vector, int index) {
    if (index < 0 || index > vector->size - 1) return true;
    return false;
};

/**
 * @brief Double the array size by 2, and reallocate all informations
 *  * O(n)
 * @return int : 0 If increased, 1 if aborted
 */
int increase_capacity_if_needed(struct Vector* vector) {
    if (vector->capacity == MAX_VECTOR_SIZE) {
        printf("Vector reached max size, aborting increase_capacity_if_needed\n");
        return 1;
    }

    if (vector->size != vector->capacity) return 1;

    int newCapacity = vector->capacity * 2;

    int* newArray = malloc(newCapacity * sizeof(int));
    int i;

    for (i = 0; i < vector->size; i++) {
        newArray[i] = vector->array[i];
    };

    free(vector->array);

    vector->capacity = newCapacity;
    vector->array = newArray;

    return 0;
};

/**
  * @brief Divide the array size by 2, and reallocate all informations
 *  * O(n)
 * @return int : 0 If increased, 1 if aborted 
 */
int decrease_capacity_if_needed(struct Vector* vector) {
      if (vector->capacity == BASE_VECTOR_CAPACITY) {
        printf("Vector reached min size, aborting decrease_capacity_if_needed\n");
        return 1;
    }

    int halfCapacity = vector->capacity / 2;

    if (vector->size > halfCapacity) return 1;

    int newCapacity = halfCapacity;

    int* newArray = malloc(newCapacity * sizeof(int));
    int i;
    
    for (i = 0; i < vector->size; i++) {
        newArray[i] = vector->array[i];
    };

    free(vector->array);

    vector->capacity = newCapacity;
    vector->array = newArray;

    return 0;
};

/**
 * @brief Push at the end of the array
 *  * 0(1);
 */
void push(struct Vector* vector, int element) {
    increase_capacity_if_needed(vector);

    vector->array[vector->size] = element;
    vector->size += 1;
};

/**
 * @brief Insert element at given index
 *  * 0(n);
 */
void insert(struct Vector* vector, int index, int element) {
    if (is_out_of_bounds(vector, index)) {
        printf("Out of bounds of the array !\n");
        abort();
    }

    int i;

    increase_capacity_if_needed(vector);

    // We need to loop backward to push elements to the right
    for(i = vector->size; i >= index; i--) {
        if (i >= index) vector->array[i] = vector->array[i - 1]; 
        if (i == index) vector->array[i] = element;
    }

    vector->size += 1;
};

void prepend(struct Vector* vector, int element) {
    insert(vector, 0, element);
}

/**
 * @brief Delete element at given index
 *  * O(n);
 */
void delete(struct Vector* vector, int index) {
     if (is_out_of_bounds(vector, index)) {
        printf("Out of bounds of the array !");
        abort();
    }

    int i;

    for(i = 0; i <= vector->size - 1; i++) {
        if (i >= index) vector->array[i] = vector->array[i + 1];
    };

    vector->size -= 1;

    decrease_capacity_if_needed(vector);
};

/**
 * @brief Get and remove the last element of the array
 *  * O(1);
 */
int pop(struct Vector* vector) {
    if (is_empty(vector)) {
        printf("Array is empty !");
        abort();
    };

    int value = vector->array[vector->size - 1];
    vector->size -= 1;

    decrease_capacity_if_needed(vector);

    return value;
};

/**
 * @brief Get element at given index
 *  * O(1);
 */
int get(struct Vector* vector, int index) {
    if (is_out_of_bounds(vector, index)) {
        printf("Out of bounds of the array !\n");
        abort();
    }

    return vector->array[index];
};

/**
 * @brief Find the index of a given element
 *  * O(n)
 * @return int Index of the value is found, -1 otherwise
 */
int find(struct Vector* vector, int value) {
    int i;
 
    for (i = 0; i <= vector->size - 1 ; i++) {
        if (vector->array[i] == value) return i;
    }

    return -1;
}

/**
 * @brief Delete all occurences of the given value
 * * O(n^2) ? Bad implementation ?
 */
void removeValue(struct Vector* vector, int value) {
    int i;
    for (i = 0; i <= vector->size - 1 ; i++) {
        if (vector->array[i] == value) {
            delete(vector, i);
            i--; // Continue from the deleted index, value may appear again
        }
    }

}

void clear_vector(struct Vector* vector) {
    free(vector->array);
    free(vector);
}

/**
 * @brief A vector is a mutable array of varying size in memory.
 * It'll basically double is size every time it reach full capacity.
 */
int main() {
   struct Vector* vector = initVector();

    int i;
    int j;

    for (j = 0; j <= 7; j++) push(vector, j + 1); 

    if (is_empty(vector)){
        printf("Vector is empty\n");
        return 0;
    }

    printf("[ ");
    for (i = 0; i < vector->size; i++) printf("%i, ", vector->array[i]); 
    printf("]\n");

    printf("Final vector informations { capacity: %i, size: %i }\n", vector->capacity, vector->size);

    clear_vector(vector);
    return 0;
};