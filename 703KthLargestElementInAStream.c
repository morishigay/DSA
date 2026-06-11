//LEETCODE 703: KTH LARGEST ELEMENT IN A STREAM
#include <stdlib.h>

//heap data structure
typedef struct KthLargest{
    int k;
    int size;
    int* heap;
} KthLargest;

//utility function for swapping two integers, making it easier to maintain heap properties
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//min-heapify down for maintaining elements
void heapifyDown(int* heap, int size, int idx){
    //formulas for smallest, left, and right child indices
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && heap[left] < heap[smallest]){ //if the left child is smaller than the current smallest, update the smallest index to the left child
        smallest = left;
    }

    if (right < size && heap[right] < heap[smallest]){ //if the right child is smaller than the current smallest, update the smallest index to the right child
        smallest = right;
    }

    if (smallest != idx){ //if the smallest index is not the current index, swap the elements and continue heapifying down
        swap(&heap[idx], &heap[smallest]);
        heapifyDown(heap, size, smallest);
    }
}

//min-heapify up when adding elements
void heapifyUp(int* heap, int idx){
    while (idx > 0){ //while the current index is greater than 0 (not the root of the heap)
        int parent = (idx - 1) / 2; //formula for parent index
        if (heap[idx] < heap[parent]){ //if the current element is smaller than its parent
            swap(&heap[idx], &heap[parent]);
            idx = parent;
        } else{ //if the current element is not smaller than its parent, the heap property is satisfied
            break;
        }
    }
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* obj = (KthLargest*)malloc(sizeof(KthLargest));
    obj->k = k;
    obj->size = 0;
    obj->heap = (int*)malloc(k * sizeof(int));

    int initialElements = (numsSize < k) ? numsSize : k; //we need this so we don't go out of bounds
    for (int i = 0; i < initialElements; i++){ //add the first k elements to the heap
        obj->heap[i] = nums[i];
        obj->size++;
    }
    for (int i = (obj->size / 2) - 1; i >= 0; i--){ //build min-heap
        heapifyDown(obj->heap, obj->size, i);
    }

    for (int i = k; i < numsSize; i++){ //process remaining elements (if there are)
        if (nums[i] > obj->heap[0]){
            obj->heap[0] = nums[i];
            heapifyDown(obj->heap, obj->size, 0);
        }
    }
    return obj;
}

int kthLargestAdd(KthLargest* obj, int val) {
    if (obj->size < obj->k){ //if the heap is not full, add the new value and maintain the heap property
        obj->heap[obj->size] = val;
        obj->size++;
        heapifyUp(obj->heap, obj->size - 1);
    } else if (val > obj->heap[0]){ //if the new value is greater than the smallest element in the heap, replace the smallest element and maintain the heap property
        obj->heap[0] = val;
        heapifyDown(obj->heap, obj->size, 0);
    }
    return obj->heap[0]; //return the smallest element in the heap, which is the kth largest element in the stream
}

void kthLargestFree(KthLargest* obj) {
    free(obj->heap);
    free(obj);
}

int main(){
    return 0;
}
