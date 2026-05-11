#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    char* homepage;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct BrowserHistory{
    Node* curr;
} BrowserHistory;

BrowserHistory* browserHistoryCreate(char* homepage) {
    BrowserHistory* newPage = (BrowserHistory*)malloc(sizeof(BrowserHistory));
    Node* head = malloc(sizeof(Node));
    head->homepage = strdup(homepage);
    head->prev = head->next = NULL;
    newPage->curr = head;
    return newPage;
}

void browserHistoryVisit(BrowserHistory* obj, char* url) {
    // clear forward history
    Node* temp = obj->curr->next;
    while (temp != NULL) {
        Node* toFree = temp;
        temp = temp->next;
        free(toFree->homepage);
        free(toFree);
    }
    // create and link new node
    Node* newNode = malloc(sizeof(Node));
    newNode->homepage = strdup(url);
    newNode->prev = obj->curr;
    newNode->next = NULL;

    //update pointers
    obj->curr->next = newNode;
    obj->curr = newNode;  //current to the new page
}

char* browserHistoryBack(BrowserHistory* obj, int steps) {
    while (steps > 0 && obj->curr->prev != NULL){
        obj->curr = obj->curr->prev;
        steps--;
    }
    return obj->curr->homepage;
}

char* browserHistoryForward(BrowserHistory* obj, int steps) {
    while (steps > 0 && obj->curr->next != NULL){
        obj->curr = obj->curr->next;
        steps--;
    }
    return obj->curr->homepage;
}

void browserHistoryFree(BrowserHistory* obj) {
    Node* curr = obj->curr;
    while (curr->prev != NULL) curr = curr->prev; //rewind to start
    while (curr != NULL){
        Node* temp = curr->next;
        free(curr->homepage);
        free(curr);
        curr = temp;
    }
    free(curr);
}

int main(){
    return 0;
}