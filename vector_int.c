#include "vector_int.h"
#include <stdio.h>
#include <stdlib.h>

void init_vector(vectorInt* v){
    v->capacity = 4;
    v->data = malloc(v->capacity*sizeof(int));

    if(v->data == NULL) {
        fprintf(stderr, "Memory allocation failed in init_vector.\n");
        exit(EXIT_FAILURE);
    }

    v->size = 0;
} //creating a vector

void push_back(vectorInt* v, int value){
    if(v->size == v->capacity){
        int new_capacity = v->capacity * 2;

        int* temp = realloc(v->data, new_capacity * sizeof(int));

        if(temp == NULL) {
            fprintf(stderr, "Memory reallocation failed!\n");
            exit(EXIT_FAILURE);
        }

        v->data = temp;
        v->capacity = new_capacity;
    }

    v->data[v->size] = value; 
    v->size++;
} //in C++ the vector has many functions, but here I only need push_back. Dynamically adding an element in the tail of the array

void clear_vector(vectorInt* v){
    free(v->data);
    v->data = NULL;
    v->size = 0;
} //clearing up the vector, not to have any memory leaks