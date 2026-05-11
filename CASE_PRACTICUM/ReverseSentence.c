//ABOUT SLL (SINGLY LINKED LIST) AND STACKS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_SIZE 1000

typedef struct Node{
    char ch;
    struct Node* next;
} Node;

typedef struct Stack{
    Node* top;
} Stack;

Node* createNode(char ch){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode){
        exit(EXIT_FAILURE);
    }
    newNode->ch = ch;
    newNode->next = NULL;
    return newNode;
}

Stack* createStack(){
    Stack* st = (Stack*)malloc(sizeof(Stack));
    if (!st){
        exit(EXIT_FAILURE);
    }
    st->top = NULL;
    return st;
}

void push(Stack* st, char ch){
    Node* newNode = createNode(ch);
    newNode->next = st->top;
    st->top = newNode;
}

char pop(Stack* st){
    if (st->top == NULL){
        return '\0';
    }
    Node* temp = st->top;
    char ch = temp->ch; //pointer to the duplicated string
    st->top = temp->next;
    free(temp);
    return ch;
}

int isEmptyStack(Stack* st){
    return (st->top == NULL);
}

void freeStack(Stack* st){
    Node* curr = st->top;
    while (curr != NULL){
        Node* temp = curr;
        curr = curr->next;
        free(temp); //then free the node
    }
    free(st);
}

int main(){
    setlocale(LC_ALL, " ");
    Stack* st = createStack();
    char input[MAX_SIZE], choice[10];
    do{
        int wordCount = 0; //for checking if the inputted sentence is less than 5 words
            printf("Reverse Sentence\n");
            printf("================\n");
            do{
            printf("Input sentence[minimum 5 words]: ");
            if (!fgets(input, MAX_SIZE, stdin)) return 1;
            input[strcspn(input, "\n")] = '\0';  //remove trailing newline

            //count words and tokenize
            char temp[MAX_SIZE];
            strcpy(temp, input);
            char* token = strtok(temp, " ");
            while (token != NULL){
                wordCount++;
                token = strtok(NULL, " ");
            }

            //error handling (if input less than 5 words)
            if (wordCount < 5){
                continue;
            }
        } while (wordCount < 5); //repeat until valid input

        //process valid input
        //push each character of the string
        for (int i = 0; i < strlen(input); i++){
            push(st, input[i]);
        }

        //pop to build reversed string
        char reversed[MAX_SIZE];
        int i = 0;
        while (!isEmptyStack(st)){
            reversed[i++] = pop(st);
        }
        reversed[i] = '\0';

        //output result
        printf("The result is: %s\n", reversed);
        printf("Do you want to continue[yes|no] ? "); scanf("%s", choice); getchar();
        freeStack(st);
        st = createStack();
    } while (strcmp(choice, "yes") == 0);
    freeStack(st); //free remaining stack nodes
    return 0;
}