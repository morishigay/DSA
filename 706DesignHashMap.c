//LEETCODE 706: DESIGN HASHMAP
#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 1000

typedef struct Node{
    int key;
    int value;
    struct Node* next; //for chaining
} Node;

typedef struct MyHashMap{
    Node* bucket[HASH_SIZE];
} MyHashMap;

Node* createNode(int key, int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

MyHashMap* myHashMapCreate() {
    MyHashMap* hashMap = (MyHashMap*)malloc(sizeof(MyHashMap));
    if (!hashMap){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < HASH_SIZE; i++){
        hashMap->bucket[i] = NULL;
    }
    return hashMap;
}

static int hashFunction(int key){
    return key % HASH_SIZE;
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
    int idx = hashFunction(key);
    Node* curr = obj->bucket[idx];

    //update if key exists
    while (curr){
        if (curr->key == key){
            curr->value = value;
            return;
        }
        curr = curr->next;
    }
    Node* newNode = createNode(key, value);
    newNode->next = obj->bucket[idx];
    obj->bucket[idx] = newNode;
}

int myHashMapGet(MyHashMap* obj, int key) {
    int idx = hashFunction(key);
    Node* curr = obj->bucket[idx];
    while (curr){
        if (curr->key == key){
            return curr->value;
        }
        curr = curr->next;
    }
    return -1; //not found
}

void myHashMapRemove(MyHashMap* obj, int key) {
    int idx = hashFunction(key);
    Node* curr = obj->bucket[idx];
    Node* prev = NULL;
    while (curr){
        if (curr->key == key){
            if (prev){
            prev->next = curr->next;
            } else{
                obj->bucket[idx] = curr->next;
            }
            free(curr);
            return; //sucessfully removed
        }
        //move to the next node if key doesn't match
        prev = curr;
        curr = curr->next;
    }
}

void myHashMapFree(MyHashMap* obj) {
    for (int i = 0; i < HASH_SIZE; i++){
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
    MyHashMap* myHashMap = myHashMapCreate();
    myHashMapPut(myHashMap, 1, 1); // The map is now [[1,1]]
    myHashMapPut(myHashMap, 2, 2); // The map is now [[1,1], [2,2]]
    myHashMapGet(myHashMap, 1);    // return 1, The map is now [[1,1], [2,2]]
    myHashMapGet(myHashMap, 3);    // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
    myHashMapPut(myHashMap, 2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existing value)
    myHashMapGet(myHashMap, 2);    // return 1, The map is now [[1,1], [2,1]]
    myHashMapRemove(myHashMap, 2); // remove the mapping for 2, The map is now [[1,1]]
    myHashMapGet(myHashMap, 2);    // return -1 (i.e., not found), The map is now [[1,1]]
    return 0;
}
