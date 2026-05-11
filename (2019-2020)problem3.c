#include <stdio.h>
#include <stdlib.h>

//hash entry (named data) structure
typedef struct Data{
    char value[100];
    struct Data* next;
} Data;

//hash table structure
Data* hashTable[31];

//create hash function
int hash(const char* str){
    int len = strlen(str);
    int base = 11;
    int MOD = 31;
    int key = 0;
    for (int i = 0; i < len; i++){
        key = (key * base) + (str[i] - 'a' + 1);
        key = key % MOD;
    }
    return (key * base) % MOD;
}

//insert data into hashtable with chaining
void chaining(int idx, const char* str){
    Data* newData = (Data*)malloc(sizeof(Data));
    strcpy(newData->value, str);
    newData->next = NULL;
    
    if (hashTable[idx] == NULL){
        hashTable[idx] = newData;
    } else{
        newData->next = hashTable[idx];
        hashTable[idx] = newData;

        /*if inserting at tail:
        Data* current = hashTable[idx];
        while (current->next != NULL){
            current = current->next;
        }
        current->next = newData;
        */
    }
}

//view data if the index have data
void viewAll(){
    for (int i = 0; i < 31; i++){
        if (hashTable[i] != NULL){
            printf("Index %d: ", i);
            Data* curr = hashTable[i];
            while (curr != NULL){
                printf("%s -> ", curr->value);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

//pop all the hashtable
void popAll(){
    for (int i = 0; i < 31; i++){
        Data* curr = hashTable[i];
        while (curr != NULL){
            Data* temp = curr;
            curr = curr->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

//initialize hashtable
void init(){
    for (int i = 0; i < 31; i++){
        hashTable[i] = NULL;
    }
}

int main(){
    char data[][100] = {
        "roti",
        "keju",
        "coklat",
        "durian",
        "nasi",
        "buncis",
        "ayam",
        "air",
        "mie",
        "tahu",
        "tempe",
        "susu",
        "sapi",
        "telur",
        "biskuit",
        "wortel",
        "steak",
        "kentang",
        "apel",
        "melon",
        "ikan"
    };
    init();
    int count = sizeof(data) % sizeof(data[0]);
    for (int i = 0; i < count; i++){
        int idx = hash(data[i]);
        chaining(idx, data[i]);
    }
    viewAll();
    popAll();
    return 0;
}