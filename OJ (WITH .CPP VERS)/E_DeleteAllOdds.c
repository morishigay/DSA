#include <stdio.h>
#include <stdlib.h>

//node structure for a double linked list
struct Node{
    int data;
    struct Node* prev;
    struct Node* next;  
};

//function to create a new node
struct Node* createNode(int x){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

//function to delete a node
struct Node* deleteNode(struct Node* head, struct Node*delNode){
    if (head == NULL || delNode == NULL) return;
    
    //if deleting the head node
    if (head == delNode) head = delNode->next;

    //update the prev node next pointer
    if (delNode->next != NULL) delNode->next->prev = delNode->prev;

    //update the next node prev pointer
    if (delNode->prev != NULL) delNode->prev->next = delNode->next;
    free(delNode); //free old memory of a deleted node
    return head;
}

/*void deleteNode(struct Node** head, struct Node* delNode){
    if (*head == NULL || delNode == NULL) return;
    if (*head == delNode) *head = delNode->next;
    if (delNode->next != NULL) delNode->next->prev = delNode->prev;
    if (delNode->prev != NULL) delNode->prev->next = delNode->next;
    free(delNode);
}*/

int main(){
    int n;
    scanf("%d", &n);

    struct Node* head = NULL;
    struct Node* tail = NULL; 
    struct Node* temp = NULL;

    //read and create the double linked list
    for (int i = 0; i < n; i++){
        int value;
        scanf("%d", &value);

        struct Node* newNode = createNode(value);

        if (head == NULL){
            head = newNode;
            tail = newNode;
        } else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    //traverse and delete all odd nodes
    struct Node* curr = head;
    struct Node* nextNode = NULL;

    while (curr != NULL){
        nextNode = curr->next; //store next before possibly deleting

        if (curr->data % 2 != 0){ //check if odd
            head = deleteNode(head, curr);
        }
        curr = nextNode;
    }

    //output result
    if (head == NULL){
        printf("-1\n");
    } else{
        struct Node* temp = head;
        while (temp != NULL){
            printf("%d", temp->data);
            if (temp->next != NULL){
                printf(" ");
            }
            temp = temp->next;
        }
        printf("\n");
    }

    //free remaining nodes
    while (head != NULL){
        struct Node* toFree = head;
        head = head->next;
        free(toFree);
    }
    return 0;
}