#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//m = table size
int m = 23;

struct tnode{
    char value[10];
    int step;
} *ND[25];

int hashing(char value[10]){
    int key = 0;
    for (int i = 0; value[i] != '\0'; i++){
        key += value[i];
    }
    return key % m;
}

struct tnode* newData(char value[10]){
    struct tnode* newNode = (struct tnode*)malloc(sizeof(struct tnode));
    strcpy(newNode->value, value);
    newNode->step = 0;
    return newNode;
}

void insert(char value[10]){
    struct tnode* data = newData(value);
    int key = hashing(value);
    int index = key;
    int i = 0;

    while (ND[index] != NULL){ //linear probing: look for the next available (NULL) slot
        index = (key + i) % m; //move to next index cirucularly

        if (i == m){ //if we have checked all the slots and returned to the start
            printf("TABLE IS FULL!!!\n");
            free(data); //clean up memory if insert fails
            return;
        }
    }
    //insert data and record the number of steps taken (collisions)
    data->step = i;
    ND[index] = data;
}

void view(){
    for (int i = 0; i < m; i++){
        if (ND[i]){
            printf("[%d]\t%s (%d steps(s))\n", i, ND[i]->value, ND[i]->step + 1);
        } else{
            printf("[%d]\tNULL\n", i);
        }
    }
}

int main(){
    //initialize
    for(int i = 0; i < m; i++){
        ND[i] = NULL;
    }
    insert("AAAAA");
    insert("BBBBB");
    insert("CCCCC");
    insert("AAABB");
    insert("BABAA");
    insert("BAABA");
    insert("BBAAA");
    insert("ABBAA");
    view();
    return 0;
}