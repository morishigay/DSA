//LEETCODE 232: QUEUE WITH STACKS
//NOTE TO SELF: Stacks are LIFO while Queues are FIFO
#include <stdlib.h>
#include <stdbool.h>

typedef struct MyQueue{
    int* st1;
    int* st2;
    int st1Capacity;
    int st2Capacity;
    int st1Top;
    int st2Top;
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue* q = (MyQueue*)malloc(sizeof(MyQueue));
    q->st1Capacity = q->st2Capacity = 1000;
    q->st1Top = q->st2Top = -1;
    q->st1 = (int*)malloc(q->st1Capacity * sizeof(int));
    q->st2 = (int*)malloc(q->st2Capacity * sizeof(int));
    return q;
}

void myQueuePush(MyQueue* obj, int x) {
    obj->st1[++(obj->st1Top)] = x;
}

int myQueuePop(MyQueue* obj) {
    if (obj->st2Top == -1){ //if stack 2 is empty, move everything from stack 1 to stack 2
        while (obj->st1Top != -1){
            obj->st2[++(obj->st2Top)] = obj->st1[(obj->st1Top)--];
        }
    }
    if (obj->st2Top == -1) return -1;
    return obj->st2[(obj->st2Top)--];
}

int myQueuePeek(MyQueue* obj) {
    if (obj->st2Top == -1){
        while (obj->st1Top != -1){
            obj->st2[++(obj->st2Top)] = obj->st1[(obj->st1Top)--];
        }
    }
    return (obj->st2Top == -1) ? -1 : obj->st2[obj->st2Top];
}

bool myQueueEmpty(MyQueue* obj) {
    return (obj->st1Top == -1 && obj->st2Top == -1);
}

void myQueueFree(MyQueue* obj) {
    free(obj->st1);
    free(obj->st2);
    free(obj);
}

int main(){
    return 0;
}
