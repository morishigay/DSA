#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ASCII_SIZE 256  // Support all ASCII characters

// Structure for heap node
typedef struct{
    char ch;
    int freq;
} HeapNode;

// Structure for max heap
typedef struct{
    HeapNode *arr;
    int size;
    int capacity;
} MaxHeap;

//count frequency of each character
void countFrequency(const char *str, int freq[]){
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        freq[c]++;
    }
}

//create a max heap
MaxHeap* createHeap(int capacity){
    MaxHeap *heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->arr = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

//insert into heap
void insertHeap(MaxHeap *heap, char ch, int freq){
    if (heap->size == heap->capacity){
        printf("Heap overflow.\n");
        return;
    }
    heap->arr[heap->size].ch = ch;
    heap->arr[heap->size].freq = freq;
    heapifyUp(heap, heap->size);
    heap->size++;
}

//extract max (highest frequency)
HeapNode extractMax(MaxHeap *heap){
    if (heap->size <= 0){
        HeapNode empty = {'\0', 0};
        return empty;
    }
    HeapNode root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return root;
}

//heapify up (for insert)
void heapifyUp(MaxHeap *heap, int idx){
    while (idx > 0){
        int parent = (idx - 1) / 2;
        if (heap->arr[idx].freq > heap->arr[parent].freq){
            HeapNode temp = heap->arr[idx];
            heap->arr[idx] = heap->arr[parent];
            heap->arr[parent] = temp;
            idx = parent;
        } else {
            break;
        }
    }
}

//heapify down (for extract)
void heapifyDown(MaxHeap *heap, int idx){
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left].freq > heap->arr[largest].freq)
        largest = left;
    if (right < heap->size && heap->arr[right].freq > heap->arr[largest].freq)
        largest = right;

    if (largest != idx){
        HeapNode temp = heap->arr[idx];
        heap->arr[idx] = heap->arr[largest];
        heap->arr[largest] = temp;
        heapifyDown(heap, largest);
    }
}

int main(){
    char str[1024];
    int freq[ASCII_SIZE] = {0};

    printf("Enter a string: ");
    if (!fgets(str, sizeof(str), stdin)){
        printf("Error reading input.\n");
        return 1;
    }

    //remove newline if present
    str[strcspn(str, "\n")] = '\0';

    //count frequency of each character
    countFrequency(str, freq);

    //create heap and insert characters with non-zero frequency
    MaxHeap *heap = createHeap(ASCII_SIZE);
    for (int i = 0; i < ASCII_SIZE; i++){
        if (freq[i] > 0) {
            insertHeap(heap, (char)i, freq[i]);
        }
    }

    //extract from heap and display in descending frequency
    printf("\nCharacter frequencies (highest first):\n");
    while (heap->size > 0){
        HeapNode node = extractMax(heap);
        if (node.ch == ' ')
            printf("' ' (space) : %d\n", node.freq);
        else if (node.ch == '\t')
            printf("'\\t' (tab)  : %d\n", node.freq);
        else
            printf("'%c' : %d\n", node.ch, node.freq);
    }
    free(heap->arr);
    free(heap);
    return 0;
}
