//ABOUT DLL (DOUBLY LINKED LIST) AND QUEUES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

//structure for DLL node
typedef struct Node{
    char name[26];
    char description[MAX];
    char code[7];
    int age;
    int priority;
    struct Node* prev;
    struct Node* next;
} Node;

//structure for priority queue
typedef struct PriorityQueue{
    Node* head;
} PriorityQueue;

//initialize new node and new priority queue
Node* createNode(){
    Node* newNode = (Node*)malloc(sizeof(Node)); //or Node* newNode = (Node*)calloc(1, sizeof(Node));
    newNode->name[0] = '\0';
    newNode->age = 0;
    newNode->description[0] = '\0';
    newNode->code[0] = '\0';
    newNode->priority = 0;
    newNode->prev = newNode->next = NULL;
    return newNode;
    /* to make things quick:
    if (newNode != NULL){
        memset(newNode, 0, sizeof(Node));
    }
    newNode->prev = newNode->next = NULL;
    return newNode;*/
}

void initQueue(PriorityQueue* pq){
    pq->head = NULL;
}

//validate user input function(s)
//get patient name
void getPatientName(char* name){
    int valid = 0;
    do{
        printf("Input patient name[4-25]: ");
        if (fgets(name, 26, stdin) == NULL){
            printf("Error reading input\n");
            continue;
        }

        //remove trailing newline
        name[strcspn(name, "\n")] = '\0';

        //check if input was truncated
        if (strchr(name, '\n') == NULL && strlen(name) == sizeof(name) - 1){
            printf("Error reading input\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        int len = strlen(name);
        if (len >= 4 && len <= 25){
            valid = 1;
        } else{
            printf("Invalid input\n");
        }
    } while (!valid);
}

//get patient age
void getPatientAge(int* age){
    int valid = 0;
    do{
        printf("Input patient age[>= 0]: ");
        scanf("%d", &age);

        if (*age > 0){
            valid = 1;
        } else{
            printf("Home say young\n");
        }
    } while (!valid);
}

//get patient description
void getPatientDesc(char* desc){
    int valid = 0;
    do{
        printf("Input description[>= 6 characters]: ");
        //safe input with fgets instead of scanf
        if (fgets(desc, MAX, stdin) == NULL){
            printf("Error reading input\n");
            continue;
        }

        //remove trailing newline
        desc[strcspn(desc, "\n")] = '\0';

        //check if input was truncated
        if (strchr(desc, '\n') == NULL && strlen(desc) == sizeof(desc) - 1){
            printf("Error reading input\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        //count words in description (handle multiple spaces)
        int wordCount = 0;
        char temp[1000];
        strcpy(temp, desc);

        char* token = strtok(temp, " ");
        while (token != NULL){
            if (strlen(token) > 0){ //skip empty tokens
                wordCount++;
            }
            token = strtok(NULL, " ");
        }

        if (wordCount < 6){
            printf("Too short\n");
        } else{
            valid = 1;
        }
    } while (!valid);
}

//get patient code
void getPatientCode(char* code){
    int valid = 0;
    do{
        printf("Input code[Red|Yellow|Green]: ");
        if (fgets(code, 7, stdin) == NULL){
            printf("Invalid input\n");
            continue;
        }

        code[strcspn(code, "\n")] = '\0';

        if (strcmp(code, "Red") == 0 || strcmp(code, "Yellow") == 0 || strcmp(code, "Green") == 0){
            valid = 1;
        } else{
            printf("That's not a valid code.\n");
        }
    } while (!valid);
}

//priority queue operations
void enqueue(PriorityQueue* pq, Node* newNode){
    if (pq->head == NULL || newNode->priority > pq->head->priority){
        //insert at beginning
        newNode->next = pq->head;
        if (pq->head != NULL){
            pq->head->prev = newNode;
        }
        pq->head = newNode;
    } else{
        //find correct position based on priority
        Node* curr = pq->head;
        while (curr->next != NULL && curr->next->priority >= newNode->priority){
            curr = curr->next;
        }
        //insert after curr
        newNode->next = curr->next;
        newNode->prev = curr;
        if (curr->next != NULL){
            curr->next->prev = newNode;
        }
        curr->next = newNode;
    }
}

void view(PriorityQueue* pq){
    if (pq == NULL || pq->head == NULL){
        printf("There is no queue yet !\n");
        printf("Press Enter to continue ...\n"); getchar();
        return;
    }
    Node* temp = pq->head;
    int counter = 1; //for the No column
    printf("Patient List: ");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|No   | Name                          | Age       | Description                                                             | Code       |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
    while (temp != NULL){
        printf("|%-3d | %-30s | %-9d | %-68s | %-10s |\n", counter++, temp->name, temp->age, temp->description, temp->code);
        temp = temp->next;
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Press Enter to continue ...\n"); getchar(); //wait for Enter key
}

Node* peek(PriorityQueue* pq){
    return pq->head;
}

int isEmpty(PriorityQueue* pq){
    return pq->head == -1;
}

Node* dequeue(PriorityQueue* pq){
    if (pq->head == NULL){
        return NULL;
    }
    Node* temp = pq->head;
    pq->head = pq->head->next;
    if (pq->head != NULL){
        pq->head->prev = NULL;
    }
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void freeQueue(PriorityQueue* pq){
    Node* curr = pq->head;
    while (curr != NULL){
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }
    pq->head = NULL;
}

void menu(){
    Node* newNode = createNode();
    PriorityQueue pq;
    initQueue(&pq);
    int choice, age;
    char name[MAX], desc[MAX], code[MAX];
    do{
        printf("Bluejack Hospital\n");
        printf("===================\n");
        printf("1. Insert\n");
        printf("2. View\n");
        printf("3. Next Queue\n");
        printf("4. Exit\n");
        printf(">> "); scanf("%d", &choice);
        while (getchar() != '\n');

        switch(choice){
        case 1: //insert
            getPatientName(newNode->name);
            getPatientAge(&newNode->age);
            getPatientDesc(newNode->description);
            getPatientCode(newNode->code);
            if (strcmp(newNode->code, "Red") == 0){
                newNode->priority = 1;
            } else if (strcmp(newNode->code, "Yellow") == 0){
                newNode->priority = 2;
            } else{
                newNode->priority = 3;
            }
            enqueue(&pq, newNode);
            printf("Insert success !\n");
            break;
        case 2: //view
            view(&pq);
            break;
        case 3: //next queue
            if (isEmpty(&pq)){
                printf("There is no queue yet !\n");
                printf("Press Enter to continue ...\n"); getchar();
            } else{
                Node* removedPatient = dequeue(&pq);
                printf("The next patient is:\n");
                printf("Name: %s\n", removedPatient->name);
                printf("Age: %d\n", removedPatient->age);
                printf("Description: %s\n", removedPatient->description);
                printf("Code: %s\n", removedPatient->code);
                printf("Press Enter to continue ...\n"); getchar();
                free(removedPatient);
            }
            break;
        case 4:
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    } while (choice != 4);
    freeQueue(&pq);
}

int main(){
    menu();
    return 0;
}