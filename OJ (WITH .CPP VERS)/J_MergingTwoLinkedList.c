#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* createNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

struct Node* insert(struct Node** head, int x){
    struct Node* newNode = createNode(x);

    //if the list is empty, return new node as head
    if (*head == NULL){
        *head = newNode; 
        return *head;
    }

    //traverse to the last node
    struct Node* last = *head;
    while (last->next != NULL){
        last = last->next;
    }
    last->next = newNode;
    newNode->prev = last;
    return newNode;
}

void mergeLists(struct Node** A, struct Node** B){
    //if A is empty, A becomes B
    if (*A == NULL){
        *A = *B;
        *B = NULL;
        return;
    }

    //if B is empty, nothing
    if (*B == NULL){
        return;
    }

    //find the last node of A
    struct Node* temp = *A;
    while (temp->next != NULL){
        temp = temp->next;
    }

    //connect last node of A to the first node of B
    temp->next = *B;
    if (*B != NULL){
        (*B)->prev = temp;
    }

    //make B empty
    *B = NULL;
}

void displayList(struct Node* head){
    struct Node* curr = head;
    int first = 1; //for proper spacing

    while (curr != NULL){
        if (!first){
            printf(" ");
        }
        printf("%d", curr->data);
        curr = curr->next;
        first = 0;
    }
    printf("\n");
}

//free memory to prevent leaks
void freeList(struct Node* head){
    struct Node* temp = head;

    while (head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(){
    struct Node* A = NULL;
    struct Node* B = NULL;
    int n, m;

    //read N and M
    if (scanf("%d %d", &n, &m) != 2){
        fprintf(stderr, "Error reading N and M\n");
        return 1;
    }

    //read list A
    for (int i = 0; i < n; i++){
        int x;
        if (scanf("%d", &x) != 1){
            fprintf(stderr, "Error reading values for list A\n");
            freeList(A);
            return 1;
        }
        insert(&A, x); //pass address of A
    }

    //read list B
    for (int j = 0; j < m; j++){
        int x;
        if (scanf("%d", &x) != 1){
            fprintf(stderr, "Error reading values for list B\n");
            freeList(A);
            freeList(B);
            return 1;
        }
        insert(&B, x); //pass address of B
    }

    //merge lists of A and B
    mergeLists(&A, &B);

    //print/display list
    displayList(A);

    /*just for debugging
    if (B == NULL){
        printf("B is now empty as required\n");
    }*/
    freeList(A);
    return 0;
}