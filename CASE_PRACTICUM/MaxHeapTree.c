//ABOUT HEAP
#include <stdio.h>
#include <stdlib.h>

typedef struct Heap{
    int* arr;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int* nums, int capacity){
    Heap* newHeap = (Heap*)malloc(sizeof(Heap));
    if (newHeap == NULL) return NULL;
    newHeap->size = 0;
    newHeap->capacity = capacity;
    newHeap->arr = (int*)malloc(sizeof(int));
    if (newHeap->arr == NULL) return NULL;
    for (int i = 0; i < capacity; i++){
        newHeap->arr[i] = nums[i];
    }
    return newHeap;
}

void insertHelper(){

}

void maxHeapify(){

}

void insert(){

}

void pop(){
    
}

void printHeap(){

}

void menu(){
    int choice;
    do{
        printf("MAX HEAP TREE\n");
        printf("=============\n");
        printf("1. Insert\n");
        printf("2. View\n");
        printf("3. Pop\n");
        printf("4. Exit\n");
        if (scanf("%d", &choice) != 1) return 1;

        switch (choice){
        case 1:
            /* code */
            break;
        
        default:
            break;
        }
    } while (choice != 5);
}

int main(){
    menu();
    return 0;
}