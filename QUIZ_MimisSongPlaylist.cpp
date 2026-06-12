#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_TITLE_LEN 25

typedef struct Data{
    char name[MAX_TITLE_LEN];
    int priority;
} Data;

Data heap[MAX_SIZE];
int size = 0;

void swap(Data* a, Data* b){
    Data temp = *a;
    *a = *b;
    *b = temp;
}

//for MAX heap (higher priority = higher value)
void upHeapMax(int idx){
    while (idx > 0){
        int parent = (idx - 1) / 2;
        if (heap[idx].priority > heap[parent].priority){
            swap(&heap[idx], &heap[parent]);
            idx = parent;  //move up to parent
        } else {
            break;
        }
    }
}

void downHeapMax(int idx){
    while (1){
        int maxIdx = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heap[left].priority > heap[maxIdx].priority){
            maxIdx = left;
        }

        if (right < size && heap[right].priority > heap[maxIdx].priority){
            maxIdx = right;
        }

        if (maxIdx != idx){
            swap(&heap[idx], &heap[maxIdx]);
            idx = maxIdx;  //continue down the heap
        } else{
            break;
        }
    }
}

//for MIN heap (lower priority = higher value)
void upHeapMin(int idx){
    while (idx > 0){
        int parent = (idx - 1) / 2;
        if (heap[idx].priority < heap[parent].priority){
            swap(&heap[idx], &heap[parent]);
            idx = parent;  //move up to parent
        } else{
            break;
        }
    }
}

void downHeapMin(int idx){
    while (1){
        int minIdx = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heap[left].priority < heap[minIdx].priority){
            minIdx = left;
        }

        if (right < size && heap[right].priority < heap[minIdx].priority){
            minIdx = right;
        }

        if (minIdx != idx){
            swap(&heap[idx], &heap[minIdx]);
            idx = minIdx;  //continue down the heap
        } else{
            break;
        }
    }
}

//insert for ascending order (MIN heap)
void ascendingInsert(char name[], int prio){
    if (size >= MAX_SIZE){
        printf("Heap is full!\n");
        return;
    }
    strcpy(heap[size].name, name);
    heap[size].priority = prio;
    upHeapMin(size);
    size++;
}

//remove root for ascending order (MIN heap)
void ascendingRemove(){
    if (size == 0){
        return;
    }
    heap[0] = heap[size - 1];
    size--;
    if (size > 0){
        downHeapMin(0);
    }
}

void ascendingDisplay(){
    if (size == 0){
        printf("No songs in playlist\n");
        return;
    }

    //create a temporary copy to display without destroying heap
    Data tempHeap[MAX_SIZE];
    int tempSize = size;
    memcpy(tempHeap, heap, sizeof(Data) * size);

    //extract and display in order
    for (int i = 0; i < tempSize; i++){
        printf("%d\t\t%s\n", tempHeap[i].priority, tempHeap[i].name);
    }
}

//insert for descending order (MAX heap)
void descendingInsert(char name[], int prio){
    if (size >= MAX_SIZE){
        printf("Heap is full!\n");
        return;
    }
    strcpy(heap[size].name, name);
    heap[size].priority = prio;
    upHeapMax(size);
    size++;
}

void descendingRemove(){
    if (size == 0){
        return;
    }
    heap[0] = heap[size - 1];
    size--;
    if (size > 0){
        downHeapMax(0);
    }
}

void descendingDisplay(){
    if (size == 0){
        printf("No songs in playlist\n");
        return;
    }

    //create a temporary copy to display without destroying heap
    Data tempHeap[MAX_SIZE];
    int tempSize = size;
    memcpy(tempHeap, heap, sizeof(Data) * size);

    //extract and display in order
    for (int i = 0; i < tempSize; i++){
        printf("%d\t\t%s\n", tempHeap[i].priority, tempHeap[i].name);
    }
}

int main(){
    int n, prio;
    char name[MAX_TITLE_LEN];
    char order[20];

    scanf_s("%s", order);
    scanf_s("%d", &n); getchar();

    //insert all songs first
    printf("Enter songs (priority name):\n");
    for (int i = 0; i < n; i++){
        scanf_s("%d", &prio); getchar();
        fgets(name, MAX_TITLE_LEN, stdin);
        name[strcspn(name, "\n")] = 0;

        if (strcmp(order, "ascending") == 0){
            ascendingInsert(name, prio);
        } else if (strcmp(order, "descending") == 0){
            descendingInsert(name, prio);
        }
    }

    //display the results
    if (strcmp(order, "ascending") == 0){
        ascendingDisplay();
    } else if (strcmp(order, "descending") == 0){
        descendingDisplay();
    }
    return 0;
}
