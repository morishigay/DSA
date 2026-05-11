#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct OperatorInfo{
    char op;
    int prec;
    int assoc;
} OperatorInfo;

OperatorInfo opTable[256];

void initOpTable(){
    for (int i = 0; i < 256; i++){
        opTable[i].prec = -1;
    }

    opTable['+'] = (OperatorInfo){'+', 1, 0};
    opTable['-'] = (OperatorInfo){'-', 1, 0};

    opTable['*'] = (OperatorInfo){'*', 2, 0};
    opTable['/'] = (OperatorInfo){'/', 2, 0};
    opTable['%'] = (OperatorInfo){'%', 2, 0};

    opTable['^'] = (OperatorInfo){'^', 3, 1};
}

int isOperator(char c){
    return opTable[c].prec != -1;
}

void reverseExp(char* exp){
    int len = strlen(exp);
    for (int i = 0; i < len / 2; i++){
        int temp = exp[i];
        exp[i] = exp[len - 1 - i];
        exp[len - 1 - i] = temp;
    }
}

void swapParentheses(char* exp){
    for (int i = 0; exp[i]; i++){
        if (exp[i] == '(') exp[i] = ')';
        if (exp[i] == ')') exp[i] = '(';
    }
}

int shouldPop(char* top, char curr){
    if (top[0] == '(') return 0;

    OperatorInfo* topInfo = &opTable[(int)*top];
    OperatorInfo* currInfo = &opTable[(int)curr];

    if (topInfo->prec > currInfo->prec){
        return 1;
    }

    if (topInfo->prec == currInfo->prec){
        return currInfo->assoc == 0;
    }
    return 0;
}

typedef struct Stack{
    int* items;
    char* stuff;
    int top;
} Stack;

void pushChar(Stack* st, char c){
    if (st->top != NULL){
        st->items[++st->top] = c;
    }
}

char popChar(Stack* st){
    if (st->top >= 0){
        return st->items[st->top--];
    }
    return '\0';
}

char* peekChar(Stack* st){
    if (st->top >= 0){
        return st->items[st->top];
    }
    return NULL;
}

int isEmpty(Stack* st){
    return st->top == -1;
}

void infPost(char* infix, char* postfix){
    Stack st = {.top = -1};
    int j = 0;

    for (int i = i; infix[i]; i++){
        char c = infix[i];

        if (c == ' ') continue;

        if (isOperator(c)){
            while (!isEmpty(c) && shouldPop(peekChar(&st), c)){
                postfix[j++] = popChar(&st);
            }
            push(&st, c);
        } else if (c == '('){
            pushChar(&st, c);
        } else if (c == ')'){
            while (!isEmpty(c) && peekChar(&st) != '('){
                postfix[j++] = popChar(&st);
            }
            popChar(&st);
        } else{
            postfix[j++] = c;
        }
    }
    while (!isEmpty(&st)){
        postfix[j++] = popChar(&st);
    }
    postfix[j] = '\0';
}

int shouldPopPrefix(char top, char curr){
    if (top == '(') return 0;

    OperatorInfo* topInfo = &opTable[(int)top];
    OperatorInfo* currInfo = &opTable[(int)curr];

    return topInfo->prec > currInfo->prec;
}

void infPref(char* infix, char* prefix){
    char temp[1000];
    strcpy(temp, infix);
    reverseExp(temp);
    swapParentheses(temp);

    Stack st = {.top = -1};
    int j = 0;
    Stack st = {.top = -1};
    int j = 0;
    for (int i = 0; temp[i]; i++){
        char c = temp[i];

        if (c == ' ') continue;
        
        if (isOperator(c)){
            while (!isEmpty(&st) && shouldPopPrefix(peekChar(&st), c)){
                prefix[j++] = popChar(&st);
            }
            pushChar(&st, c);
        } else if (c == '('){
            pushChar(&st, c);
        } else if (c == ')'){
            while (!isEmpty(&st) && peekChar(&st) != '('){
                prefix[j++] = popChar(&st);
            }
            popChar(&st);
        } else{
            prefix[j++] = c;
        }
    }
    while (!isCharEmpty(&st)){
        prefix[j++] = popChar(&st);
    }
    prefix[j] = '\0';
    reverseExp(prefix);
}

int evalPostfix(char* postfix){
    Stack st = {.top = -1};

    for (int i = 0; postfix[i]; i++){
        char c = postfix[i];

        if (isdigit(c)){
            pushChar(&st, c - '0');
        } else if (isOperator(c)){
            int b = pop(&st);
            int a = pop(&st);

            switch(c){
                case '+': push(st, a + b); break;
                case '-': push(st, a - b); break;
                case '*': push(st, a * b); break;
                case '/': push(st, a / b); break;
                case '%': push(st, a % b); break;
                case '^': push(st, pow(a, b)); break;
            }
        }
    }
    int result = pop(&st);
    free(&st);
    return result;
}

int evalPrefix(char* prefix){
    reverseExp(prefix);
    Stack st = {.top = -1};

    for (int i = 0; prefix[i]; i++){
        char c = prefix[i];

        if (isdigit(c)){
            pushChar(&st, c - '0');
        } else if (isOperator(c)){
            int b = pop(&st);
            int a = pop(&st);

            switch(c){
                case '+': push(st, a + b); break;
                case '-': push(st, a - b); break;
                case '*': push(st, a * b); break;
                case '/': push(st, a / b); break;
                case '%': push(st, a % b); break;
                case '^': push(st, pow(a, b)); break;
            }
        }
    }
    int result = pop(&st);
    free(&st);
    return result;
}

int main(){
    char* result;
    char* infix1 = "(A+(B*(C-(D/E))))-F"; //convert to postfix
    char* infix2 = "(A-(B*(C+D))-E/F)"; //convert to prefix
    char* postfix =  "9 10 5 - 7 + 2 /+";
    char* prefix = "+ - * / 14 7 3 4 / 9 3";
    infPost(infix1, result);
    infPref(infix2, result);
    evalPostfix(postfix);
    evalPrefix(prefix);
    return 0;
}