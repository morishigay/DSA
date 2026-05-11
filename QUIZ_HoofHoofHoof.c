#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Train{
    char type;
    float val;
    struct Train* prev;
    struct Train* next;
} Train;

Train* createTrain(char type, int val){
    Train* newTrain = (Train*)malloc(sizeof(Train));
    newTrain->type = type;
    newTrain->val = val;
    newTrain->prev = newTrain->next = NULL;
    return newTrain;
}

typedef struct TrainQueue{
    Train* front;
    Train* rear;
} TrainQueue;

TrainQueue* createQueue(){
    TrainQueue* q = (TrainQueue*)malloc(sizeof(TrainQueue));
    q->front = q->rear = NULL;
    return q;
}

void appendBack(TrainQueue* q, Train* newCarriage){
    if (q->rear == NULL){
        q->front = q->rear = newCarriage;
    } else{
        q->rear->next = newCarriage;
        newCarriage->prev = q->rear;
        q->rear = newCarriage;
    }
}

/*void appendFront(TrainQueue* q, Train* newCarriage){
    if (q->front == NULL){
        q->front = q->rear = newCarriage;
    } else{
        q->front->prev = newCarriage;
        newCarriage->next = q->front;
        q->front = newCarriage;
    }
}*/

Train* processTrain(TrainQueue* q, float* lostWeight){
    Train* curr = q->front;
    while (curr != NULL){
        Train* nextNode = curr->next; //to avoid issues during deletion and insertion

        if (curr->type == 'F'){ //FULL
            float newVal = curr->val / 2.0f;
            curr->val = newVal;
            curr->type = 'N'; //NEW
            Train* newN = createTrain('N', newVal); //new carriage gets another half

            //insertion logic for split carriage
            if (curr->prev == NULL && curr->next == NULL){ //if only one carriage
                appendBack(q, newN);
            } else if (curr->prev == NULL){ //insert at back (FIRST CARRIAGE TO THE BACK)
                newN->next = curr->next;
                if (curr->next) curr->next->prev = newN;
                curr->next = newN;
                newN->prev = curr;
            } else if (curr->next == NULL){ //insert at front (LAST CARRIAGE TO THE LEFT)
                newN->prev = curr->prev;
                curr->prev->next = newN;
                newN->next = curr;
                curr->prev = newN;
                if (newN->prev == NULL) q->front = newN;
            } else{ //insert at middle based on proximity
                float diffPrev = fabsf(curr->prev->val - newVal);
                float diffNext = fabsf(curr->next->val - newVal);
                
                if (diffPrev <= diffNext){ //insert after curr (behind)
                    newN->next = curr->next;
                    newN->prev = curr;
                    curr->next->prev = newN;
                    curr->next = newN;
                } else{ //insert before curr (front)
                    newN->prev = curr->prev;
                    newN->next = curr;
                    curr->prev->next = newN;
                    curr->prev = newN;
                    if (newN->prev == NULL) q->front = newN;
                }
            }
        } else if (curr->type == 'X'){ //BROKEN
            *lostWeight += curr->val; //accumulate lost weight

            //delete node
            if (curr->prev) curr->prev->next = curr->next;
            if (curr->next) curr->next->prev = curr->prev;
            
            //update front/rear if needed
            if (curr == q->front) q->front = curr->next;
            if (curr == q->rear) q->rear = curr->prev;
            free(curr);
        }
        curr = nextNode;
    }
    return q;
}

void displayTrain(TrainQueue* q){
    Train* curr = q->front;
    while (curr != NULL){
        printf("%.2f %c", curr->val, curr->type);
        if (curr->next != NULL) printf("\n");
        curr = curr->next;
    }
    printf("\n");
}

/*void freeQueue(TrainQueue* q){
    Train* curr = q->front;
    while (curr != NULL){
        Train* temp = curr->next;
        free(curr);
        curr = temp;
    }
}*/

int main(){
    TrainQueue* q = createQueue();
    int n;
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++){
        char type;
        float val;
        scanf("%f %c", &val, &type);
        Train* newTrain = createTrain(type, val);
        appendBack(q, newTrain);
    }

    float lostWeight = 0;
    q = processTrain(q, &lostWeight);
    printf("Total lost: %.2f\n", lostWeight);
    displayTrain(q);
    return 0;
}