#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int val;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int val){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

Node* insert(Node* head, int val){
    Node* newNode = createNode(val);
    if (head == NULL){
        return newNode;
    } else if (head->prev == NULL){ //insert at front
        newNode->next = head;
        head->prev = newNode;
        return newNode;
    } else if (head->next == NULL){ //insert at back
        head->next = newNode;
        newNode->prev = head;
        return newNode;
    } else{ //insert at middle
        Node* temp = head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode;
    }
    return newNode;
}

//pop sum on DLL
/* EXAMPLE:
Input : 4 5 2 1 3
Target sum = 3
Output 4 5 3
*/
Node* popSum(Node* head, int target){
    Node* curr = head;
    
    while (curr != NULL && curr->next != NULL){
        //check if adjacent pair sums to target
        if (curr->val + curr->next->val == target){
            int sum = curr->val + curr->next->val;
            
            //create new node with the sum
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->val = sum;
            
            //connect newNode in place of the pair
            newNode->prev = curr->prev;
            newNode->next = curr->next->next;
            
            //update surrounding nodes
            if (curr->prev != NULL){
                curr->prev->next = newNode;
            } else{
                head = newNode;  //new head if removing first two nodes
            }
            
            if (curr->next->next != NULL){
                curr->next->next->prev = newNode;
            }
            
            //free old pair
            free(curr);
            free(curr->next);
            
            //continue checking from newNode (or its previous)
            curr = newNode;
        } else{
            curr = curr->next;
        }
    }
    return head;
}

void display(Node* head){
    Node* curr = head;
    while (curr != NULL){
        printf("%d ", curr->val);
        curr = curr->next;
    }
    printf("\n");
}

void freeList(Node* head){

}

int main(){
    return 0;
}