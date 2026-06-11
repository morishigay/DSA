#include <stdio.h>
#include <string.h>

#define MAX_HEAP_SIZE 15
#define MAX_NAME_LEN 26

//struct to store machine details
typedef struct Machine{
    char name[MAX_NAME_LEN];
    int priority;
} Machine;

Machine heap[MAX_HEAP_SIZE];
int heapSize = 0;

//swap two machine structures
void swap(Machine *a, Machine *b){
    Machine temp = *a;
    *a = *b;
    *b = temp;
}

//maintain heap property upwards after insertion
void heapifyUp(int index){
    while (index > 0){
        int parent = (index - 1) / 2;
        if (heap[index].priority > heap[parent].priority){
            swap(&heap[index], &heap[parent]);
            index = parent;
        } else{
            break;
        }
    }
}

//maintain heap property downwards after extraction
void heapifyDown(int index){
    int maxIndex = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < heapSize && heap[leftChild].priority > heap[maxIndex].priority){
        maxIndex = leftChild;
    }
    if (rightChild < heapSize && heap[rightChild].priority > heap[maxIndex].priority){
        maxIndex = rightChild;
    }

    if (index != maxIndex){
        swap(&heap[index], &heap[maxIndex]);
        heapifyDown(maxIndex);
    }
}

//insert a new machine into the heap
void reportMachine(char name[], int priority){
    if (heapSize >= MAX_HEAP_SIZE){
        printf("MACHINE QUEUE FULL\n");
        return;
    }
    strcpy(heap[heapSize].name, name);
    heap[heapSize].priority = priority;
    heapifyUp(heapSize);
    heapSize++;
}

//repair the highest priority machine
void repairMachine(){
    if (heapSize == 0){
        printf("NO MACHINES\n");
        return;
    }
    //print the machine being repaired
    printf("REPAIRING %s %d\n", heap[0].name, heap[0].priority);

    //replace the root with the last element
    heap[0] = heap[heapSize - 1];
    heapSize--;

    //restore heap property
    if (heapSize > 0){
        heapifyDown(0);
    }
}

//display all machines currently stored in the heap array
void checkHeap(){
    for (int i = 0; i < heapSize; i++){
        printf("%s %d\n", heap[i].name, heap[i].priority);
    }
}

int main(){
    int q;
    if (scanf_s("%d", &q) != 1) return 0;

    char command[20];
    for (int i = 0; i < q; i++){
        scanf("%s", command);
        if (strcmp(command, "REPORT") == 0){
            char name[MAX_NAME_LEN];
            int priority;
            scanf_s("%s %d", name, &priority);
            reportMachine(name, priority);
        } else if (strcmp(command, "REPAIR") == 0){
            repairMachine();
        } else if (strcmp(command, "CHECK") == 0){
            checkHeap();
        }
    }
    return 0;
}
