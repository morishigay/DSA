//LEETCODE 705: DESIGN HASHSET
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUCKET_SIZE 1009

typedef struct Node{
    int key;
    struct Node* next;
} Node;

typedef struct MyHashSet{
    Node* bucket[BUCKET_SIZE];
} MyHashSet;

static int hashFunction(int key){
    if (key < 0) key = -key; //handle negative keys
    return key % BUCKET_SIZE;
}

MyHashSet* myHashSetCreate() {
    MyHashSet* set = (MyHashSet*)malloc(sizeof(MyHashSet));
    if (!set){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < BUCKET_SIZE; i++){
        set->bucket[i] = NULL;
    }
    return set;
}

void myHashSetAdd(MyHashSet* obj, int key) {
    int idx = hashFunction(key);
    Node* curr = obj->bucket[idx];

    while (curr){
        if (curr->key == key) return; //key already exists
        curr = curr->next;
    }

    //insert at head of list
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->key = key;
    newNode->next = obj->bucket[idx];
    obj->bucket[idx] = newNode;
}

void myHashSetRemove(MyHashSet* obj, int key) {
    int idx = hashFunction(key);
    Node* curr = obj->bucket[idx];
    Node* prev = NULL;

    while (curr){
        if (curr->key == key){
            if (prev) prev->next = curr->next;
            else obj->bucket[idx] = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

bool myHashSetContains(MyHashSet* obj, int key) {
    int idx = hashFunction(key);
    Node* curr = obj->bucket[idx];
    while (curr){
        if (curr->key == key) return true;
        curr = curr->next;
    }
    return false;
}

void myHashSetFree(MyHashSet* obj) {
    for (int i = 0; i < BUCKET_SIZE; i++){
        Node* curr = obj->bucket[i];
        while (curr){
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(obj);
}

int main(){
    MyHashSet* myHashSet = myHashSetCreate();
    myHashSetAdd(myHashSet, 1);      // set = [1]
    myHashSetAdd(myHashSet, 2);      // set = [1, 2]
    myHashSetContains(myHashSet, 1); // return True
    myHashSetContains(myHashSet, 3); // return False, (not found)
    myHashSetAdd(myHashSet, 2);      // set = [1, 2]
    myHashSetContains(myHashSet, 2); // return True
    myHashSetRemove(myHashSet, 2);   // set = [1]
    myHashSetContains(myHashSet, 2); // return False, (already removed)
    return 0;
}
