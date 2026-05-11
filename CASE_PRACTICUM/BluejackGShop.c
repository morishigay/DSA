//ABOUT AVL TREE
#define _GNU_SOURCE //this is for strdup. you can also use #define _POSIX_C_SOURCE_200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TITLE 100000
#define MAX_GENRE 100

//PART 1: AVL TREE STRUCTURE AND NODE CREATION

typedef struct Node{
    char* title; //KEY
    char* genre;
    int stock;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

Node* createNode(Node* node, const char* title, const char* genre, int stock){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->title = strdup(title);
    newNode->genre = strdup(genre);
    newNode->stock = stock;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

//PART 2: VALIDATING INPUTS

//must be between 5 and 25 char, unique (for utility)
bool isUnique(Node* root, const char* title){
    if (!root) return true;
    if (strcmp(root->title, title) == 0) return false;
    return isUnique(root->left, title) && isUnique(root->right, title);
}

bool validTitle(Node* root, const char* title){
    int len = strlen(title);
    if (len < 5 || len > 25){
        return false;
    }
    return isUnique(root, title);
}

void getTitle(Node* root, char* title){
    do{
        printf("Input game title[5-25][unique]: ");
        if (fgets(title, MAX_TITLE, stdin) == NULL) return;
        title[strcspn(title, "\n")] = '\0';
    } while (!validTitle(root, title));
}

//must be Action, RPG, Adventure, Card Game (for utility)
bool validGenre(const char* genre){
    if (strcmp(genre, "Action") != 0 && strcmp(genre, "RPG") != 0 && strcmp(genre, "Adventure") != 0 && strcmp(genre, "Card Game") != 0){
        return false;
    }
    return true;
}

void getGenre(char* genre){
    do{
        printf("Input game genre[]: ");
        if (fgets(genre, MAX_GENRE, stdin) == NULL) return;
        genre[strcspn(genre, "\n")] = '\0';
    } while (!validGenre(genre));
}

//must be greater or equal than 1 (for utility)
bool validStock(int stock){
    if (stock < 1){
        return false;
    }
    return true;
}

void getStock(int* stock){
    char input[20];
    do{
        printf("Input stock[>= 1]: ");
        if (fgets(input, 20, stdin) == 0) return;
        input[strcspn(input, "\n")] = '\n';
        *stock = atoi(input);
    } while(!validStock(stock));
}

//PART 3: AVL TREE MECHANICS FOR INSERTION, DELETION AND TRAVERSAL/PRINTING

/* In C, max and min are not built-in functions. We'll have to implement it from scratch but it's pretty easy rlly.
int max(int a, int b){
    return (a > b) ? a : b;
}

int min(int a, int b){
    return (a < b) ? a : b;
}*/

//utility to get height
int getHeight(Node* root){
    if (root == NULL) return 0;
    return root->height;
}

//utility for checking balance of a node
int getBalance(Node* root){
    if (root == NULL) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

//utility for right rotation in y subtree
Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* t2 = x->right;

    //perform rotation
    x->right = y;
    y->left = t2; 

    //update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

//utility for left rotation in x subtree
Node* leftRotate(Node* x){
    Node* y = x->right;
    Node* t2 = y->left;

    //perform rotation
    y->left = x;
    x->right = t2;

    //update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

//insert a node in an AVL tree
Node* insert(Node* root, char* title){
    //basic BST insertion
    int res = strcmp(title, root->title);
    if (res < 0){
        root = insert(root->left, title);
    } else if (res > 0){
        root = insert(root->right, title);
    } else{
        return root;
    }

    //update height
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    //check if the following node is balanced
    int balance = getBalance(root);

    //if not, there will be 4 cases
    //1. LL case
    if (balance > 1 && res < 0){
        return rightRotate(root);
    }

    //2. RR case
    if (balance < -1 && res > 0){
        return leftRotate(root);
    }
    //3. LR case
    if (balance < 1 && res < 0){
        root->left = leftRotate(root);
        return rightRotate(root);
    }

    //4. RL case
    if (balance > -1 && res > 0){
        root->right = rightRotate(root);
        return leftRotate(root);
    }
    return root;
}

//search a node
Node* search(Node* root, char* title){
    if (root == NULL) return NULL;
    int res = strcmp(root->title, title);
    if (res == 0){
        return root;
    } else if (res < 0){
        return search(root->left, title);
    }
    return search(root->right, title);
}

//delete a node in an AVL tree
Node* remove(Node* root, char* title){
    //basic BST deletion
    if (root == NULL){
        return root;
    }

    int res = strcmp(root->title, title);
    if (res < 0){
        root->left = remove(root->left, title);
    } else if (res > 0){
        root->right = remove(root->right, title);
    } else{
        if (!root->left || !root->right){
            Node* temp = root->left ? root->left : root->right;
            if (!temp){
                temp = root;
                root = NULL;
            } else{
                *temp = *root;
                free(temp);
            }
        } else{
            Node* temp = min(root->right);
            strncpy(temp->title, root->title, sizeof(temp->title) - 1);
            root->right = remove(root->left, temp->title);
        }
    }

    //update height
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    //check if the following node is balanced
    int balance = getBalance(root);

    //if not, there will be 4 cases
    //1. LL case
    if (balance > 1 && res < 0){
        return rightRotate(root);
    }

    //2. RR case
    if (balance < -1 && res > 0){
        return leftRotate(root);
    }
    //3. LR case
    if (balance < 1 && res < 0){
        root->left = leftRotate(root);
        return rightRotate(root);
    }

    //4. RL case
    if (balance > -1 && res > 0){
        root->right = rightRotate(root);
        return leftRotate(root);
    }
    return root;
}

//print all games (in-order)
void viewAllGames(Node* root){
    if (root == NULL){
        printf("Warehouse is empty !\n");
        printf("Press Enter to continue ...\n"); getchar();
    } else{
        printf("---------------------------------------------------------\n");
        printf("Game Title               | Game Genre      | Game Stock |\n");
        viewAllGames(root->left);
        printf("| %-15s | %-6s | %-4d |\n");
        viewAllGames(root->right);
        printf("---------------------------------------------------------\n");
    }
}

//delete a game
Node* remove(Node* root, char* title){
    
}

//freeeeeeeeee
void freeGames(Node* root){
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

//PART 4: MENU FOR ALL FUNCTIONS IMPLEMENTED ABOVE

void menu(){
    Node* root = NULL;
    char* title, *genre;
    int choice, stock;
    do{
        printf("Bluejack GShop\n");
        printf("==============\n");
        printf("1. Insert Game\n");
        printf("2. View Game\n");
        printf("3. Update Stock\n");
        printf("4. Exit\n");
        printf(">> "); scanf("%d", &choice);

        switch(choice){
            case 1:{ //INSERT GAME
                getTitle(root, title);
                getGenre(genre);
                getStock(stock);
                root = insert(root, title);
                printf("Insert success\n");
            }
            break;
            case 2: //VIEW GAME
                viewAllGames(root);
                break;
            case 3:{ //UPDATE STOCK
                getTitle(root, title);
                Node* searched = search(root, title);
                if (searched == NULL){ //IF DOES NOT EXIST
                    printf("Data not found !\n");
                    printf("Press Enter to continue ..."); getchar();
                } else{ //IF EXISTS
                    char cmd[20];
                    printf("Input update type[add|remove|case insensitive]: "); scanf("%s", cmd);
                    if (strcmp(cmd, "add") == 0){ //IF ADD
                        getStock(stock);
                    } else if (strcmp(cmd, "remove") == 0){ //IF REMOVE
                        int removed;
                        printf("Input stock to remove[1-50]: "); scanf("%d", &removed);
                        if (removed < 1 || removed > 50){
                            return 1;
                        }
                        removed -= root->stock;
                        printf("Data updated successfully");
                    } else{ //NEITHER OF THE COMMANDS/INCORRECT COMMANDS
                        printf("What in the hell you doing bra\n");
                    }
                }
            }
            break;
            case 4: //EXIT
                break;
            default: //ERROR MESSAGE
                printf("Son\n");
                break;
        }
    } while (choice != 5);
    freeGames(root);
}

int main(){
    menu();
    return 0;
}