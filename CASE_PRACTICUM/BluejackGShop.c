//ABOUT AVL TREE
#define _POSIX_C_SOURCE 200809L //for strdup, or you can use #define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 100000
#define MAX_GENRE 100

//AVL tree node
typedef struct Node{
    char* title; //KEY
    char* genre;
    int stock;

    //what an AVL tree must have idk what to call them
    struct Node* left;
    struct Node* right;
    int height;
} Node;

//create AVL tree node
Node* createNode(char* title, char* genre, int stock){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->title = strdup(title);
    newNode->genre = strdup(genre);
    newNode->stock = 0;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

//must be between 5 and 25, unique
bool isUnique(Node* root, const char* title){
    if (root == NULL) return true;
    if (strcmp(root->title, title) == 0) return false;
    return isUnique(root->left, title) && isUnique(root->right, title);
}

bool validName(Node* root, const char* title){
    int len = strlen(title);
    if (len < 5 || len > 25){
        return false;
    }
    return isUnique(root, title);
}

void getGameName(Node* root, char* title){
    do{
        printf("Input game title[5-25][unique]: ");
        if (fgets(title, MAX_NAME, stdin) == NULL) return;
        title[strcspn(title, "\n")] = '\0';
    } while (!validName(root, title));
}

//must be the following: Action, RPG, Adventure, Card Game
bool validGenre(const char* genre){
    if (strcmp(genre, "Action") != 0 && strcmp(genre, "RPG") != 0 && strcmp(genre, "Adventure") != 0 && strcmp(genre, "Card Game") != 0){
        return false;
    }
    return true;
}

void getGameGenre(char* genre){
    do{
        printf("Input game genre[Action|RPG|Adventure|Card Game]: ");
        if (fgets(genre, MAX_GENRE, stdin) == NULL) return;
        genre[strcspn(genre, "\n")] = '\0';
    } while (!validGenre(genre));
}

//must be greater or equal than 1
bool validStock(int stock){
    if (stock < 1){
        return false;
    }
    return true;
}

void getGameStock(int* stock){
    char input[20];
    do{
        printf("Input game stock[>= 1]: ");
        if (fgets(input, 20, stdin) == NULL) return 0;
        input[strcspn(input, "\n")] = '\0';
        *stock = atoi(input);
    } while (!validStock(*stock));
}

//AVL tree mechanics for insertion
int getHeight(Node* root){
    if (root == NULL) return 0;
    return root->height;
}

int getMax(int a, int b){
    return (a > b) ? a : b;
}

Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* t2 = x->right;

    //perform rotation
    x->right = y;
    y->left = t2;

    //update heights
    y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x){
    Node* y = x->right;
    Node* t2 = y->left;

    //perform rotation
    y->left = x;
    x->right = t2;

    //update heights
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

int getBalance(Node* root){
    if (root == NULL) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

//insert a game (THE TITLE IS THE KEY)
Node* insert(Node* root, char* title, char* genre, int stock){
    //usual BST insertion
    if (root == NULL){
        return createNode(title, genre, stock);
    }
    int res = strcmp(root->title, title);
    if (res > 0){
        root->left = insert(root->left, title, genre, stock);
    } else if (res < 0){
        root->right = insert(root->right, title, genre, stock);
    } else{
        return root;
    }

    //update height
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    //call getBalance to check if the node became unbalanced
    int balance = getBalance(root);

    //if unbalanced, there are 4 cases
    //1. LL case
    if (balance > 1 && strcmp(title, root->left->title) < 0){
        return rightRotate(root);
    }

    //2. RR case
    if (balance < -1 && strcmp(title, root->right->title) > 0){
        return leftRotate(root);
    }

    //3. LR case
    if (balance > 1 && strcmp(title, root->left->title) > 0){
        root->left = leftRotate(root);
        return rightRotate(root);
    }
    
    //4. RL case
    if (balance < -1 && strcmp(title, root->right->title) < 0){
        root->right = rightRotate(root);
        return leftRotate(root);
    }
    return root;
}

//search a game (TITLE IS THE KEY)
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

Node* getMin(Node* root){
    if (root->left != NULL){
        return getMin(root->left);
    }
    return root;
}

//delete a game
Node* removeGame(Node* root, char* title){
    //usual BST deletion
    if (root == NULL) return root;
    int res = strcmp(root->title, title);
    if (res > 0){
        root = removeGame(root->left, title);
    } else if (res < 0){
        root = removeGame(root->right, title);
    } else{
        if (root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        } else if (root->left != NULL && root->right != NULL){
            Node* temp = getMin(root->right);
            free(root->title);
            free(root->genre);
            free(temp);
            root->title = strdup(temp->title);
            root->genre = strdup(temp->genre);
            root->stock = temp->stock;
            root->right = remove(root->right, temp->title);
        } else{
            Node* temp = (root->left != NULL) ? root->left : root->right;
            free(root->title);
            free(root->genre);
            free(root);
            return temp;
        }
    }

    //update height
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    //call getBalance to check if the node became unbalanced
    int balance = getBalance(root);

    //if unbalanced, there are 4 cases
    //1. LL case
    if (balance > 1 && strcmp(title, root->left->title) < 0){
        return rightRotate(root);
    }

    //2. RR case
    if (balance < -1 && strcmp(title, root->right->title) > 0){
        return leftRotate(root);
    }

    //3. LR case
    if (balance > 1 && strcmp(title, root->left->title) > 0){
        root->left = leftRotate(root);
        return rightRotate(root);
    }
    
    //4. RL case
    if (balance < -1 && strcmp(title, root->right->title) < 0){
        root->right = rightRotate(root);
        return leftRotate(root);
    }
    return root;
}

//view all games in inorder method
void viewGames(Node* root){
    if (root == NULL){
        printf("Warehouse is empty !\n");
        printf("Press Enter to continue...\n"); getchar();
    } else{
        printf("----------------------------------------------------------------\n");
        printf("| Game Title                  | Game Genre      | Game Stock   |\n");
        printf("----------------------------------------------------------------\n");
        viewGames(root->left);
        printf("|%-25s | %-15s | %10d |\n");
        viewGames(root->right);
        printf("----------------------------------------------------------------\n");
    }
}

//free all games
void freeGames(Node* root){
    if (root == NULL) return;
    freeGames(root->left);
    freeGames(root->right);
    free(root);
}

void menu(){
    Node* root = NULL;
    int choice, stock;
    char title[MAX_NAME];
    char genre[MAX_GENRE];
    do{
        printf("Bluejack GShop\n");
        printf("==============\n");
        printf("1. Insert Game\n");
        printf("2. View Game\n");
        printf("3. Update Stock\n");
        printf("4. Exit\n");
        scanf("%d", &choice);

        switch (choice){
        case 1:{ //insert game
            getGameName(root, title);
            getGameGenre(genre);
            getGameStock(stock);
            root = insert(root, title, genre, stock);
            printf("Insert success !\n");
        }
        break;
        case 2: //view game
            viewGames(root);
            break;
        case 3:{ //update stock
            getGameName(root, title);
            Node* searched = search(root, title);
            if (searched == NULL){ //if does not exist
                printf("Data not found !\n");
                printf("Press Enter to continue ...\n"); getchar();
            } else{ //if exists
                char cmd[20];
                int qty;
                printf("Input update type[add|remove|case-insensitive]: "); scanf("%s", cmd);
                if (strcmp(cmd, "add") == 0 || strcmp(cmd, "Add") == 0){ //add
                    printf("Input stock to add[1-50]: "); scanf("%d", &qty);
                    searched->stock += qty;
                    printf("Data updated successfully !\n");
                } else if (strcmp(cmd, "remove") == 0 || strcmp(cmd, "Remove") == 0){ //remove
                    printf("Input stock to remove[1-50]: "); scanf("%d", &qty);
                    if (qty > searched->stock){
                        printf("Insufficient stock! Current stock: %d\n", searched->stock);
                    } else if (qty < searched->stock){
                        searched->stock -= qty;
                        printf("Data updated successfully\n");
                    } else{
                        root = removeGame(root, title);
                        printf("Data updated sucessfully\n");
                        printf("%s is removed from the warehouse !\n", searched->title);
                    }
                } else{ //incorrect cmd
                    printf("bradar what is this\n");
                }
            }
        }
        break;
        case 4: //exit
            break;
        default: //error message
            printf("Try again\n");
            break;
        }
    } while (choice != 4);
    freeGames(root);
}

int main(){
    menu();
    return 0;
}