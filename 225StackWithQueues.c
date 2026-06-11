//LEETCODE 225: STACKS WITH QUEUES
//NOTE TO SELF: Stacks are LIFO while Queues are FIFO
#include <stdlib.h>
#include <stdbool.h>

typedef struct MyStack{
    int* q1;
    int* q2;
    int q1Size;
    int q2Size;
    int q1Capacity;
    int q2Capacity;
} MyStack;

MyStack* myStackCreate() {
    MyStack* st = (MyStack*)malloc(sizeof(MyStack));
    st->q1Size = st->q2Size = 0;
    st->q1Capacity = st->q2Capacity = 1000;
    st->q1 = (int*)malloc(st->q1Capacity * sizeof(int));
    st->q2 = (int*)malloc(st->q2Capacity * sizeof(int));
    return st;
}

void myStackPush(MyStack* obj, int x) {
    obj->q1[(obj->q1Size)++] = x;
}

int myStackPop(MyStack* obj) {
    if (obj->q1Size == 0){ //underflow condition
        return -1;
    }

    while (obj->q1Size > 1){
        obj->q2[obj->q2Size++] = obj->q1[0]; //move elements from q1 to q2 until only one element is left
        for (int i = 0; i < obj->q1Size; i++){
            obj->q1[i] = obj->q1[i + 1];
        }
        obj->q1Size--;
    }
    //pop last element
    int poppedEle = obj->q1[0];
    obj->q1Size--;

    //swap queues
    int* temp = obj->q1;
    obj->q1 = obj->q2;
    obj->q2 = temp;

    int tempSize = obj->q1Size;
    obj->q1Size = obj->q2Size;
    obj->q2Size = tempSize;
    return poppedEle;
}

int myStackTop(MyStack* obj) {
    return obj->q1[obj->q1Size - 1];
}

bool myStackEmpty(MyStack* obj) {
    return obj->q1Size == 0;
}

void myStackFree(MyStack* obj) {
    free(obj->q1);
    free(obj->q2);
    free(obj);
}

int main(){
    MyStack* myStack = myStackCreate();
    myStackPush(myStack, 1);
    myStackPush(myStack, 2);
    myStackTop(myStack); // return 2
    myStackPop(myStack); // return 2
    myStackEmpty(myStack); // return False
    return 0;
}
