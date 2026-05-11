//LEETCODE #20: VALID PARENTHESES
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack{
    char items[1001];
    int top;    
} Stack;

void push(Stack* st, char c){
    if (st->top < 10000){
        st->items[++st->top] = c;
    }
}

char peek(Stack* st){
    return st->items[st->top];
}

char pop(Stack* st){
    return st->items[st->top--];
}

bool isEmpty(Stack* st){
    return st->top == -1;
}

bool isValid(char* s){
    Stack st = {.top = -1};
    int i = 0; //for count

    while (s[i] != '\0'){
        char curr = s[i];
        if (curr == '(' || curr == '[' || curr == '{'){
            push(&st, curr);
        } else if (curr == ')' || curr == ']' || curr == '}'){
            if (isEmpty(&st)){
                return false;
            }
            char topChar = peek(&st);
            if ((curr == ')' && topChar != '(') || (curr == ']' && topChar != '[') || (curr == '}' && topChar != '{')){
                return false;
            }
            pop(&st);
        }
        i++;
    }
    return isEmpty(&st); //all brackets are matched
}

int main(){
    return 0;
}