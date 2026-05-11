#include <stdio.h>
#include <stdlib.h>

//reverse array from start to end with pointers
void reverse(int* start, int* end){
    end--; //point to last element
    while (start < end){
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void rotateRight(int *arr, int n, int k){
    if (k == 0 || k == n) return;
    k %= n;

    //reverse entire array
    reverse(arr, arr + n);

    //reverse first k elements
    reverse(arr, arr + k);

    //reverse the rest
    reverse(arr + k, arr + n);
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);

    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        scanf("%d", arr + i);
    }

    rotateRight(arr, n, k);
    for (int i = 0; i < n; i++){
        printf("%d ", *(arr + i));
    }
    free(arr);
    return 0;
}