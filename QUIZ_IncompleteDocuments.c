#include <stdio.h>
#include <stdlib.h>

//DLL node structure
typedef struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

//queue structure
typedef struct Queue{
    Node* front;
    Node* rear;
} Queue;

Queue* initQueue(int n){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    
    //as required by the problem, 1 till N
    for (int i = 1; i <= n; i++){
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = i;
        newNode->prev = q->rear;
        newNode->next = NULL;
        
        //the usual insertion of DLL node
        if (q->rear == NULL){ //if queue is empty, set front and rear to new node (FIRST NODE)
            newNode->prev = NULL;
            q->front = q->rear = newNode;
        } else{ //if not, link the new node to the rear and update the rear (SUBSEQUENT NODES)
            newNode->prev = q->rear;
            q->rear->next = newNode;
            q->rear = newNode;
        }
    }
    return q;
}

void moveBack(Queue* q, int target){
    Node* curr = q->front;

    //find target node by traversing
    while (curr != NULL && curr->data != target){
        curr = curr->next;
    }

    //if node not found or already at the back
    if (curr == NULL || curr == q->rear) return;

    //detach node from current spot
    if (curr == q->front){
        //if its at the front, update it to the next node
        q->front = curr->next;
        if (q->front) q->front->prev = NULL;
    } else{
        //if at the middle, link the prev node to the next node
        curr->prev->next = curr->next;
        if (curr->next) curr->next->prev = curr->prev;
    }

    //attach node to rear
    q->rear->next = curr;
    curr->prev = q->rear;
    curr->next = NULL;
    q->rear = curr;
}

void displayQueue(Queue* q){
    Node* curr = q->front;
    while (curr != NULL){
        printf("%d", curr->data);
        if (curr->next != NULL) printf(" ");
        curr = curr->next;
    }
}

int main(){
    int n, p;
    scanf("%d %d", &n, &p);
    Queue* q = initQueue(n);

    for (int i = 0; i < p; i++){
        int a;
        scanf("%d", &a);
        moveBack(q, a);
        displayQueue(q);
    }
    return 0;
}