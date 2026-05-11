#include <stdio.h>
#include <stdlib.h>

//node structure for a linked list
typedef struct Node{
    int data;
    struct Node* next;
} Node;

//structure for stack
typedef struct Stack{
    Node* top;
} Stack;

//structure for queue
typedef struct Queue{
    int size;
    Node* front;
    Node* rear;
} Queue;

//create a node of the SLL
Node* createNode(int x){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

//queue operations
Queue* createQueue(){ //create a queue
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

void enqueue(Queue* q, int x){ //insertion on a queue
    Node* newNode = createNode(x);
    if (q->front == NULL){
        q->front = q->rear = newNode;
    } else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

int dequeue(Queue* q){ //deletion on a queue
    if (q == NULL || q->front == NULL){
        return -1; //queue empty
    }
    Node* temp = q->front;
    int removed = temp->data;
    q->front = q->front->next;
    if (q->front == NULL){
        q->rear = NULL;
    }
    free(temp);
    q->size--;
    return removed;
}

int isEmptyQueue(Queue* q){ //check if queue is empty
    return (q->front == NULL);
}

int getFront(Queue* q){ //returns the value at the front of the queue
    if (isEmptyQueue(q)){
        return -1;
    }
    return q->front->data;
}

//stack operations
Stack* createStack(){ //create a stack
    Stack* st = (Stack*)malloc(sizeof(Stack));
    if (st == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    st->top = NULL;
    return st;
}

void push(Stack* st, int x){ //insertion on a stack
    Node* newNode = createNode(x);
    if (st == NULL){
        st->top = newNode;
    }
    newNode->next = st->top;
    st->top = newNode;
}

int pop(Stack* st){ //deletion on a stack
    if (st->top == NULL){
        return -1; //stack empty
    }
    Node* temp = st->top;
    int removed = temp->data;
    st->top = st->top->next;
    free(temp);
    return removed;
}

int peek(Stack* st){ //returns the value at the top of the stack
    if (st == NULL || st->top == NULL){
        return -1;
    }
    return st->top->data;
}

int isEmptyStack(Stack* st){ //check if stack is empty
    return (st->top == NULL);
}

//free functions to avoid memory leak
void freeQueue(Queue* q){
    if (q == NULL){
        return;
    }
    Node* curr = q->front;
    while (curr != NULL){
    	Node* temp = curr;
    	curr = curr->next;
    	free(temp);
	}
	free(q);
}

void freeStack(Stack* st){
    if (st == NULL){
        return;
    }
    Node* curr = st->top;
    while (curr != NULL){
    	Node* temp = curr;
    	curr = curr->next;
    	free(temp);
	}
	free(st);
}

int main(){
    Stack* st = createStack(); 
    Queue* q = createQueue();
    int n;
    scanf("%d", &n);

    //read developers (queue)
    for (int i = 0; i < n; i++){
        int pref;
        scanf("%d", &pref);
        enqueue(q, pref);
    }

    //read projects (stack) 
    int* projects = (int*)malloc(n * sizeof(int));
    if (projects == 0){
    	printf("Memory allocation failed\n");
    	return 1;
	}
    for (int i = 0; i < n; i++){
        scanf("%d", &projects[i]);
    }

    //push to stack in reverse order so that projects[0] becomes top
    for (int i = n - 1; i >= 0; i--){
        push(st, projects[i]);
    }
    free(projects);

    //matching logic
    int consecutiveRejects = 0; //to count how many times we have moved a dev to the end of the queue without a match
    int originalSize = q->size; //store original size
    
    while (!isEmptyStack(st) && !isEmptyQueue(q)){
    	int topProj = peek(st); //get the top project for comparison
    	int currDev = getFront(q); //get the curr dev at the front of the queue for comparison
    	
    	if (currDev == topProj){ //if it matches, GET THEY ASS OUTTA HERE
            dequeue(q);
    		pop(st);
    		consecutiveRejects = 0;
		} else{ //move to end of the queue
            currDev = dequeue(q);
			enqueue(q, currDev);
			consecutiveRejects++;
			if (consecutiveRejects >= originalSize){ //if there are still remainings
				break; 
			}
		}
	}

    //output number of unassigned developers
    printf("%d\n", q->size);

    //free memory here
    freeStack(st);
    freeQueue(q);
    return 0;
}
