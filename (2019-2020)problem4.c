#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//patient data
struct data{
    int date;
    int month;
    int year;
    char name[100];
    struct data* prev;
    struct data *next;
} *head=NULL, *tail=NULL, *temp=NULL;

//get patient date
long getDateNumber(int date, int month, int year){
    return (long)(year * 1000) + (month * 100) + date;
}

//get patient month (name and number)
int getMonthNumber(char* month){
    if(!strcmp(month, "january"))return 1;
    if(!strcmp(month, "february"))return 2;
    if(!strcmp(month, "march"))return 3;
    if(!strcmp(month, "april"))return 4;
    if(!strcmp(month, "may"))return 5;
    if(!strcmp(month, "june"))return 6;
    if(!strcmp(month, "july"))return 7;
    if(!strcmp(month, "august"))return 8;
    if(!strcmp(month, "september"))return 9;
    if(!strcmp(month, "october"))return 10;
    if(!strcmp(month, "november"))return 11;
    if(!strcmp(month, "december"))return 12;
}

char* getMonthName(int month){
    switch (month){
        case 1: return "january";
        case 2: return "february";
        case 3: return "march";
        case 4: return "april";
        case 5: return "may";
        case 6: return "june";
        case 7: return "july";
        case 8: return "august";
        case 9: return "september";
        case 10: return "october";
        case 11: return "november";
        case 12: return "december";
    }
}

//create new patient data
struct data* createNode(int date, int month, int year, char* name){
    struct data* newNode = (struct data*)malloc(sizeof(struct data));
    newNode->date = date;
    newNode->month = month;
    newNode->year = year;
    strcpy(newNode->name, name);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

//add patient data based on priority (OLDER PPL ARE PRIORITIZED)
void priorityPush(int date, int month, int year, char* name){
    struct data* newNode = createNode(date, month, year, name);
    if (newNode == NULL) return;

    //if empty
    if (head == NULL){
        head = tail = newNode;
        return;
    }

    //if newnode is older than current head
    if (year < head->year || (year == head->year && month < head->month) || (year == head->year && month == head->month && date < head->date)){  //insertion at head
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    } else{ //insertion at tail
        struct data* curr = head;
        while (curr->next != NULL && (curr->next->year < year || curr->next->year == year && curr->next->month < month) || (curr->next->year == year && curr->next->month == month && curr->next->date <= date)){ //traverse to find the correct insertion point
            curr = curr->next;
        }

        //insert after curr
        newNode->next = curr->next;
        newNode->prev = curr;
        
        if (curr->next != NULL){
            curr->next->prev = newNode;
        } else{
            tail = newNode; //update tail if insertion is at the end
        }
        curr = curr->next;
    }
}

//remove patient data from the front
void popHead(){
    if (head == NULL) return;
    struct data* temp = head;
    head = head->next;
    free(temp);
}

//remove ALL patient data
void popAll(){
    while(head){
        popHead();
    }
}

int main(){
    int totalPatients, totalCure;
    scanf("%d %d", &totalPatients, &totalCure); getchar();
    for(int i = 0; i < totalPatients; i++){
        addData();
    }

    for(int i = 0; i < totalCure; i++){
        popHead(); 
    }
    
    if (totalPatients < totalCure || totalPatients == totalCure){
        printf("All patients get the cure, %d cure left\n", totalCure - totalPatients);
    } else if (totalPatients > totalCure){
        printf("Need %d more cure\n", totalPatients - totalCure);
    }
    printAll();
    popAll();
    return 0;
}