#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, q;
    scanf("%d %d", &n, &q);

    //dynamically allocate array
    int* arr = (int*)malloc(sizeof(int));
    if (arr == NULL) return 1;

    //read initial array
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    //process q operations
    for (int j = 0; j < q; j++){
        char op; //ts for operations
        scanf(" %c", &op); //space before %c to skip whitespace

        if (op == 'U'){
            int i, x;
            scanf("%d %d", &i, &x);
            arr[i - 1] = x; //convert to 0-based index
        } else if (op == 'S'){
            int l, r;
            scanf("%d %d", &l, &r);
            long long sum = 0;
            for (int idx = l - 1; idx < r; idx++){
                sum += arr[idx];
            }
            printf("%lld\n", sum);
        }
    }
    free(arr);
    return 0;
}