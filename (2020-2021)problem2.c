#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11
#define TABLE_SIZE2 1000

typedef struct HashEntry{
    int key;
    int value;
    int occupied;
} HashEntry;

HashEntry* hashTable[TABLE_SIZE] = {0};
HashEntry* hashTable2[TABLE_SIZE2] = {0};

int lenNumber(int num){
    int l = 0;
    while (num > 0){
        num /= 10;
        l++;
    }
    return l;
}

unsigned int hashDivision(int key){
    return key % TABLE_SIZE;
}

unsigned int hashFolding(int key){
    int sum = 0;
    while (key > 0){
        sum += key % 10;
        key /= 10;
    }
    return sum % TABLE_SIZE2;
}

void insert(HashEntry table[], int key, int value){
    unsigned int hash = hashDivision(key);

}

void insert2(){

}

void freeTable(HashEntry table[]){
    for(int i = 0; i < TABLE_SIZE; i++){
        table[i].key = 0;
        table[i].value = 0;
        table[i].occupied = 0;
    }
}

void freeTable2(){
    
}

int main(){
    //51, 22, 33, 45, 81, 60, 63, 69, 60, 55, 21
    //1921678, 777281, 1892, 1921, 21017
    return 0;
}