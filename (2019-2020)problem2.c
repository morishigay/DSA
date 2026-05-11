#include <stdio.h>
#include <stdlib.h>

//wagonTrain class
typedef struct wagonTrain{
    char cargoType;
    int cargoID;
    struct wagonTrain* next;
} wagonTrain;

//create and insert new wagonTrain
wagonTrain* pushCargo(wagonTrain* WT, char cargoType, int cargoID){
    wagonTrain* newCargo = (wagonTrain*)malloc(sizeof(wagonTrain));
    newCargo->cargoType = cargoType;
    newCargo->cargoID = cargoID;
    newCargo->next = NULL;

    if (WT == NULL){
        WT = newCargo;
    } else{
        wagonTrain* curr = WT;
        while (curr->next != NULL) curr = curr->next;
        curr->next = newCargo;
    }
    return WT;
}

//display a wagon train
void printWagonTrain(wagonTrain* WT){
    wagonTrain* curr = WT;
    while (curr != NULL){
        if (curr == WT){
            printf("%c%d", curr->cargoType, curr->cargoID);
        } else if (curr->next == NULL){
            printf(" :: %c%d\n", curr->cargoType, curr->cargoID);
        } else{
            printf(" :: %c%d\n", curr->cargoType, curr->cargoID);
            curr = curr->next;
        }
    }
}

//display ALL wagon train
void printAllTrainSet(wagonTrain* polarExpress, wagonTrain* bachmannPenn, wagonTrain* santaFe, wagonTrain* hogwartsExpress){
    printf("LIST OF TRAIN SET\n");
    printf("=================\n");

    printf("%-17s %s", "Polar Express", "= ");
    printWagonTrain(polarExpress);

    printf("%-17s %s", "Bachmann Penn", "= ");
    printWagonTrain(bachmannPenn);

    printf("%-17s %s", "Santa Fe", "= ");
    printWagonTrain(santaFe);

    printf("%-17s %s", "Hogwarts Express", "= ");
    printWagonTrain(hogwartsExpress);
}

//detect a train with identical connected series
int checkWagonTrainCargo(wagonTrain* A, wagonTrain* B){
    if (A == NULL && B == NULL){
        return 1;
    }
    while (A != NULL && B != NULL){
        if (A->cargoID != B->cargoID || A->cargoType != B->cargoType){
            return 0;
        }
        A = A->next;
        B = B->next;
    }
    return (A == NULL && B == NULL);
}

int main(){
    int i = 0, j = 0;
    char cargoType[3] = {'A', 'B', 'C'};
    int cargoIDType[10] = {12, 23, 35, 47, 56, 66, 78, 84, 92};

    //TRAIN SET 1 - Polar Express
    wagonTrain* polarExpress = NULL;
    for (i = 0; i < 9; i++){
        polarExpress = pushCargo(polarExpress, cargoType[i % 3], cargoIDType[i]);
    }

    //TRAIN SET 2 - Bachmann Penn
    wagonTrain* bachmannPenn = NULL;
    for (i = 0; i < 9; i += 2){
        bachmannPenn = pushCargo(bachmannPenn, cargoType[i % 3], cargoIDType[i]);
    }
    for (j = 1; j < 9; j += 2){
        bachmannPenn = pushCargo(bachmannPenn, cargoType[j % 3], cargoIDType[j]);
    }

    //TRAIN SET 3 - Santa Fe
    wagonTrain* santaFe = NULL;
    for (i = 8; i >= 0; i--){
        santaFe = pushCargo(santaFe, cargoType[i % 3], cargoIDType[i]);
    }

    //TRAIN SET 4 - Hogwarts Express
    wagonTrain* hogwartsExpress = NULL;
    hogwartsExpress = pushCargo(hogwartsExpress, 'A', 12);
    hogwartsExpress = pushCargo(hogwartsExpress, 'B', 23);
    hogwartsExpress = pushCargo(hogwartsExpress, 'C', 35);
    hogwartsExpress = pushCargo(hogwartsExpress, cargoType[i % 3], cargoIDType[i]);

    //display all train sets
    printAllTrainSet(polarExpress, bachmannPenn, santaFe, hogwartsExpress);

    //polar express and bachmann penn
    printf("%d\n", checkWagonTrainCargo(polarExpress, bachmannPenn));

    //santa fe and hogwarts express
    printf("%d\n", checkWagonTrainCargo(santaFe, hogwartsExpress));

    //hogwarts express and polar express
    printf("%d\n", checkWagonTrainCargo(hogwartsExpress, polarExpress));
    getchar();
    return 0;
}