/* FOR TESTING:
    - Insert cave 52, gold production 10
    - Insert cave 31, gold production 15
    - Insert cave 27, gold production 25
    - Insert cave 40, gold production 11
    - Insert cave 79, gold production 89
    - Insert cave 65, gold production 4
    - Insert cave 82, gold production 2
    - Insert cave 94, gold production 51
    - Insert cave 40, gold production 13
*/
#include <stdio.h>
#include <stdlib.h>

//BST node structure
typedef struct Node{
    int caveIndex;
    int goldProd;
    struct Node* left;
    struct Node* right;
} Node;

//create new BST node
Node* createNode(int caveIndex, int goldProd){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->caveIndex = caveIndex;
    newNode->goldProd = goldProd;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//validate cave index
void getCaveIndex(int* caveIndex){
    do{
        printf("Input cave index [1-999]: ");
        scanf("%d", caveIndex);
    } while (*caveIndex < 1 || *caveIndex > 999);
}

//validate gold production
void getGoldProd(int* goldProd){
    do{
        printf("Input gold production [1-100]: ");
        scanf("%d", goldProd);
    } while (*goldProd < 1 || *goldProd > 100);
}

//insert new cave (cave index as the key, gold prod as the value being stored)
Node* insert(Node* root, int caveIndex, int goldProd){
    Node* newNode = createNode(caveIndex, goldProd);
    if (root == NULL){
        return newNode;
    }

    Node* curr = root;
    Node* parent = NULL;
    while (curr != NULL){
        parent = curr;
        if (caveIndex < curr->caveIndex){
            curr = curr->left;
            if (curr == NULL){ //found empty spot
                parent->left = newNode;
                return root;
            }
        } else if (caveIndex > curr->caveIndex){
            curr = curr->right;
            if (curr == NULL){ //found empty spot
                parent->right = newNode;
                return root;
            }
        } else{
            //duplicate handling
            curr->goldProd += goldProd;
            free(newNode);
            printf("Cave index already exists.\n");
            printf("New total gold production for Cave %d is %d", caveIndex, curr->goldProd);
            return root;
        }
    }
    return root;
}

//display all caves (inorder traversal)
void displayAll(Node* root, int currDepth){
    if (root == NULL){
        printf("Cave data is empty, nothing to display.\n");
        printf("Press any key to continue..."); getchar();
    } else{
        displayAll(root->left, currDepth + 1);
        printf(">> Cave %d (depth %d\t), total gold production: %d\n", root->caveIndex, currDepth, root->goldProd);
        displayAll(root->right, currDepth + 1);
        printf("Press any key to continue..."); getchar();
    }
}

//utility function for finding max depth
int findMaxDepth(Node* root, int currDepth){
    if (root == NULL) return 0;
    int leftDepth = findMaxDepth(root->left, currDepth + 1);
    int rightDepth = findMaxDepth(root->right, currDepth + 1);
    return (leftDepth > rightDepth) ? leftDepth : rightDepth;
}

//utility function for counting levels of a bst
void countLevels(Node* root, int currDepth, int levelSums[], int maxDepth){
    if (root == NULL) return 0;
    levelSums[currDepth] += root->goldProd; //add current cave's gold to its depth level
    countLevels(root->left, currDepth + 1, levelSums, maxDepth);
    countLevels(root->right, currDepth + 1, levelSums, maxDepth);
}

//display mining report
void displayMiningReport(Node* root){
    if (root == NULL){
        printf("Cave data is empty, nothing to report.\n");
        printf("Press any key to continue..."); getchar();
    } else{
        //find maximum first
        int maxDepth = findMaxDepth(root, 1);

        //then initialize result dynamically
        int* result = (int*)calloc(maxDepth + 1, sizeof(int));

        //count gold production
        countLevels(root, 1, result, maxDepth);

        //display the result from highest to lowest cave
        for (int i = maxDepth; i >= 1; i--){
            printf(">> Total gold production for depth %d is %d\n", i, result[i]);
        }
        printf("Press any key to continue..."); getchar();
    }
}

//free tree
void freeTree(Node* root){
    if (root != NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void menu(){
    Node* root = NULL;
    int choice, caveIndex, goldProd;
    do{
        printf("Hov Mining Simulator\n");
        printf("====================\n");
        printf("[1.] Insert Mining Data\n");
        printf("[2.] Display All Cave Data\n");
        printf("[3.] Display Mining Reports\n");
        printf("[4.] Exit\n");
    
        switch (choice){
            case 1:
                getCaveIndex(&caveIndex);
                getGoldProd(&goldProd);
                insert(root, &caveIndex, &goldProd);
                break;
            case 2:
                displayAll(root, 1); //start at depth 1 for root
                break;
            case 3:
                displayMiningReport(root);
                break;
            case 4:
                freeTree(root);
                printf("All data has been removed from memory.\n");
                printf("Thank you for playing, see you again...\n");
                break;
            default:
                printf("Invalid input\n");
                break;
        }
    } while (choice != 4);
}

int main(){
    menu();
    return 0;
}