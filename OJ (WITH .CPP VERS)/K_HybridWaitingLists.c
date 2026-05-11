#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//node structure for a linked list
typedef struct Node{
    int data;
    struct Node* next;
} Node;

//structure for queue
typedef struct{
    Node* front;
    Node* rear;
} Queue;

//function to create a node of a linked list
Node* createNode(int x){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        return NULL;
    }
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

//function to create a queue
void createQueue(Queue* q){
    q->front = q->rear = NULL;
}

//function to insert an element at the end of the queue
void enqueue(Queue* q, int x){
    Node* newNode = createNode(x);
    if (newNode == NULL) return;

    if (q->rear == NULL){
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

//merge both online and walkin for final serving order (AKA hybrid queue)
Queue* hybridQueue(Queue* online, Queue* walkIn, Queue* hybrid){
    if (online == NULL || walkIn == NULL || hybrid == NULL){
        return NULL;
    }

    Node* o = online->front;    //pointer to online list
    Node* wi = walkIn->front;   //pointer to walk-in list

    //start with online first
    while (o != NULL || wi != NULL){
        //take online if available
        if (o != NULL){
            enqueue(hybrid, o->data);
            o = o->next;
        }

        //take from walkin if available
        if (wi != NULL){
            enqueue(hybrid, wi->data);
            wi = wi->next;
        }
    }
    return hybrid;
}

//delete cancelled IDs (specific)
void cancelledQueue(Queue* q, int val){
    if (q->front == NULL) return;

    Node* temp = q->front, *prev = NULL;

    //if head node itself holds the value to be deleted
    if (temp != NULL && temp->data == val){
        q->front = temp->next;
        if (q->front == NULL) q->rear = NULL;
        free(temp);
        return;
    }

    //search for the value to be deleted
    while (temp != NULL && temp->data != val){
        prev = temp;
        temp = temp->next;
    }

    //if value was not present
    if (temp == NULL) return;

    //unlink the node
    prev->next = temp->next;

    //if node to be deleted was the rear node
    if (temp == q->rear){
        q->rear = prev;
    }
    free(temp);
}

//print remaining hybridQueue order
void displayQueue(Queue *q){
    //traverse queue and print each element
    Node* temp = q->front;
    while (temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

//function to free queue memory
void freeQueue(Queue* q){
    if (q == NULL) return;
    Node* curr = q->front;

    while (curr != NULL){
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    q->front = q->rear = NULL;
}

int main(){
    //initialize values of n and m
    int n, m, id, l;
    scanf("%d %d", &n, &m);

    //initialize queues
    Queue online, walkIn, hybrid;
    createQueue(&online);
    createQueue(&walkIn);
    createQueue(&hybrid);

    //read online
    for (int i = 0; i < n; i++){
        scanf("%d", &id);
        enqueue(&online, id);
    }
    
    //read walk-in
    for (int j = 0; j < m; j++){
        scanf("%d", &id);
        enqueue(&walkIn, id);
    }

    //read number of cancellations
    scanf("%d", &l);

    //create hybrid queue
    hybridQueue(&online, &walkIn, &hybrid);

    //process cancellation
    for (int i = 0; i < l; i++){
        int cancelID;
        scanf("%d", &cancelID);
        cancelledQueue(&hybrid, cancelID);
    }

    //display finished hybrid queue
    displayQueue(&hybrid);

    //free queues
    freeQueue(&online);
    freeQueue(&walkIn);
    freeQueue(&hybrid);
    return 0;
}