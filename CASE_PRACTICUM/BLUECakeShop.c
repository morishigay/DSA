//ABOUT ARRAYS, POINTERS, STRUCTS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cake{
    const char* code;
    const char* name;
    int stock;
    float price;
} Cake;

Cake* initCakeTable(int* count){
    Cake initData[] = {
        {"CK001", "Blueberry Cake", 13, 25000},
        {"CK009", "Chocochip Cake", 5, 20000},
        {"CK017", "Mayonaise Cake", 24, 30000},
        {"CK023", "Strawberry Shortcake", 7, 17500}
    };
    *count = sizeof(initData) / sizeof(initData[0]);
    Cake* table = (Cake*)malloc(sizeof(Cake) * (*count));
    memcpy(table, initData, sizeof(Cake) * (*count));
    printf("BLUE CAKE SHOP CASHIER\n");
    printf("======================\n");
    printf("No. | Cake Code | Cake Name           | Available | Price         \n");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < *count; i++){
        printf("%02d. | %-9s | %-21s | %-10d | Rp. %d,-\n", i + 1, table[i].code, table[i].name, table[i].stock, table[i].price);
    }
    return table;
}

Cake* findCakeByCode(Cake cakes[], int count, char* code){
    for (int i = 0; i < count; i++){
        if (strcasecmp(cakes[i].code, code) == 0){
            return &cakes[i];
        }
    }
    return NULL;
}

void menu(){
    int choice, stock, cakeCount;
    char code[10];
    Cake* cakes = initCakeTable(&cakeCount);
    do{
        printf("Menu :\n");
        printf("1. Sell\n");
        printf("2. Add Stock\n");
        printf("3. Exit\n");
        printf("Input choice: "); scanf("%d", &choice);

        switch(choice){
            case 1:{ //sell
                printf("Input Cake Code [5 chars]: "); scanf("%s", code);
                Cake* selectedCake = findCakeByCode(cakes, cakeCount, code);
                if (selectedCake == NULL){
                    printf("---The Cake Code doesn't exist ---\n");
                    break;
                }
                printf("Input Quantity [0..13]: "); scanf("%d", &stock);
                if (stock <= 0 || stock > 13){
                    printf("...The quantity of cake is not enough...\n");
                    break;
                }
                int total = selectedCake->price * stock;
                printf("Total Price is: Rp. %d,- x %d = Rp. %d,-\n", selectedCake->price, stock, total);
                printf("--- Thank You ---\n");
                selectedCake->stock -= stock; //update stock
                break;
            }
            case 2:{ //add stock
                printf("Input Cake Code [5 chars]: "); scanf("%s", code);
                Cake* selectedCake = findCakeByCode(cakes, cakeCount, code);
                if (selectedCake == NULL){
                    printf("---The Cake Code doesn't exist ---\n");
                    break;
                }
                printf("Input Quantity [0..13]: "); scanf("%d", &stock);
                if (stock <= 0 || stock > 13){
                    printf("...The quantity of cake is not enough...\n");
                    break;
                }
                selectedCake->stock += stock; //update stock
                printf("--- Adding Stock Success ---");
                break;
            }
            case 3: //exit
                break;
            default:
                printf("Invalid input\n");
                break;
        }
    } while (choice != 3);
    free(cakes);
}

int main(){
    menu();
    return 0;
}