#include "priority_queue.h"
#include "vector_int.h"
#include <stdlib.h>
#include <stdio.h>

//main algorithm of min-heap which I implemented requires two functions: bubble_up and bubble_down
//which operate when pushing or popping elements in the queue

void bubble_up(PriorityQueue* pq, int index){
    while(index > 0){
        int parent = (index-1) / 2;

        if(pq->data[parent].dist > pq->data[index].dist){
            PQNode temp = pq->data[parent];
            pq->data[parent] = pq->data[index];
            pq->data[index] = temp; 
            index = parent; //continuing the process linearly, not recursively
        } else break;
    }
} 

void bubble_down(PriorityQueue* pq, int index){
    while(1){
        int l = index*2 + 1;
        int r = index*2 + 2;
        int mn = index; //getting the children indexes
        
        if(l < pq->size && pq->data[l].dist < pq->data[mn].dist)
            mn = l;

        if(r < pq->size && pq->data[r].dist < pq->data[mn].dist)
            mn = r; //comparing to both children

        if(mn != index){
            PQNode temp = pq->data[mn];
            pq->data[mn] = pq->data[index];
            pq->data[index] = temp; //manually swapping

            index = mn; //continuing the process linearly, not recursively
        } else break;
    }
}

void pq_init(PriorityQueue* pq, int capacity){
    pq->size = 0;
    pq->capacity = capacity;
    pq->data = malloc(capacity * sizeof(PQNode));

    if(pq->data == NULL){
        fprintf(stderr, "Memory allocation failed in pq_init.\n");
        exit(EXIT_FAILURE);
    }
}

void pq_push(PriorityQueue* pq, int distance, int node) {
    if(pq->size == pq->capacity){
        int new_capacity = pq->capacity * 2;
        PQNode* temp = realloc(pq->data, new_capacity * sizeof(PQNode));

        if(temp == NULL) {
            fprintf(stderr, "Memory reallocation failed!\n");
            exit(EXIT_FAILURE);
        }

        pq->data = temp;
        pq->capacity = new_capacity;
    } //same technique as in vector_int implementation for O(1)

    pq->data[pq->size].dist = distance;
    pq->data[pq->size].node = node;

    bubble_up(pq, pq->size); //pushing an element into the tail of the constructor, then bubbling up and adjusting the correct order

    pq->size++;
}

void pq_pop(PriorityQueue* pq){
    if(pq->size == 0)
        return;

    pq->size--;
    pq->data[0] = pq->data[pq->size];

    bubble_down(pq, 0); //popping the top element, replacing it with bottom element and then adjusting the correct order using bubbling down
}

PQNode pq_top(PriorityQueue* pq){
    return pq->data[0];
}

int pq_empty(PriorityQueue* pq){
    return pq->size == 0;
}

void pq_free(PriorityQueue* pq){
    free(pq->data);
    pq->data = NULL;
    pq->size = 0;
    pq->capacity = 0;
}