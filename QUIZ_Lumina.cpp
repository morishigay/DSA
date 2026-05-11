#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	char name[1004];
	int val;
	struct Node* prev;
	struct Node* next;
} Node;

Node* createNode(char* name, int val){
	Node* newNode = (Node*)malloc(sizeof(Node));
	strcpy(newNode->name, name);
	newNode->val = val;
	newNode->prev = newNode->next = NULL;
	return newNode;
}

typedef struct Queue{
	Node* front;
	Node* rear;
} Queue;

Queue* createQueue(){
	Queue* newQ = (Queue*)malloc(sizeof(Queue));
	newQ->front = newQ->rear = NULL;
	return newQ;	
}

//FOR UTILITY
int isEmpty(Queue* q){
	return q->front == NULL;
}

//ADD = Add a customer with the given name and priority number to the waiting list
void enqueue(Queue* q, char name[], int val){
	Node* newNode = createNode(name, val);
	if (isEmpty(q)){
		q->front = q->rear = newNode;
	}
	if (val <= newNode->val){
		q->front->prev = newNode;
		newNode->next = q->front;
		q->front = newNode;
		return;
	} else if (val >= newNode->val){
		q->rear->next = newNode;
		newNode->prev = q->rear;
		q->rear = newNode;
		return;
	} else{
		Node* curr = q->front;
		while (curr != NULL){
			curr = curr->next;
		}
		newNode->prev = curr->prev;
		newNode->next = curr;
		curr->prev->next = newNode;
		curr->prev = newNode;
	}
}

//COUNT = Display the number of customers currently in the waiting list
int count(Queue* q){
	int count = 0;
	Node* curr = q->front;
	while (curr != NULL){
		count++;
		curr = curr->next;
	}
	return count;
}

//DISPLAY = Display all customers in the waiting list ordered by priority
void display(Queue* q){
	if (isEmpty(q)){
		printf("DOUBLE LINKED LIST EMPTY\n");
		return;
	}
	printf("Waiting List: \n");
	Node* curr = q->front;
	while (curr != NULL){
		printf("%s (%d)\n", curr->name, curr->val);
		if (curr->next != NULL) printf("\n");
		curr = curr->next;
	}
}

//DELETE = Remove the customer with the given name from the waiting list
void dequeue(Queue* q, char name[]){
	if (isEmpty(q)){
		printf("DOUBLE LINKED LIST EMPTY\n");
		return;
	}
	Node* temp = q->front;
	while (temp != NULL && (strcmp(name, q->front->name) != 0)){
		temp = temp->next;
	}
	if (temp->prev){
		temp->prev->next = temp->next;
	} else{
		q->front = temp->next; //removing front
	}
	if (temp->next){
		temp->next->prev = temp->prev;
	} else{
		q->rear = temp->prev;
	}
	free(temp);
	return;
}

//NEXT = Display the customer that will be served next (highest priority)
void next(Queue* q){
	if (isEmpty(q)){
		printf("DOUBLE LINKED LIST EMPTY\n");
		return;
	}
	printf("Next customer: %s (%d)\n", q->front->name, q->front->val);
}

//SERVE = Serve (remove) the customer with the highest priority (lowest priority number)
void serve(Queue* q){
	if (isEmpty(q)){
		printf("DOUBLE LINKED LIST EMPTY\n");
		return;
	}
	Node* served = q->front;
	printf("Served customer: %s (%d)", served->name, served->val);

	//remove served
	q->front = q->front->next;
	if (q->front){
		q->front->prev = NULL;
	} else{
		q->rear = NULL;
	}
	free(served);
}

void freeQueue(Queue* q){
	Node* curr = q->front;
	while (curr != NULL){
		Node* temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(q);
}

int main(){
	/*
	3
	ADD JOKO 2
	ADD BUDI 1
	DISPLAY
	*/
	Queue* q = createQueue();
	int n, prio;
	char op[1004], name[1004];
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%s", &op);	
		if (strcmp(op, "ADD") == 0){
			scanf("%s %d", name, &prio);
			enqueue(q, name, prio);	
		} else if (strcmp(op, "SERVE") == 0){
			serve(q);
		} else if (strcmp(op, "NEXT") == 0){
			next(q);
		} else if (strcmp(op, "COUNT") == 0){
			int num = count(q);
			printf("Number of customers: %d\n", num);
		} else if (strcmp(op, "DISPLAY") == 0){
			display(q);
		} else if (strcmp(op, "DELETE") == 0){
			char target[1004];
			scanf("%s", target);
			dequeue(q, target);
			printf("Deleted customer: %s\n", target);
		}
	}
	return 0;
}
