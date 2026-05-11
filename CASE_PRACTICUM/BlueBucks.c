//ABOUT BST (BINARY SEARCH TREE)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_SIZE 1000
#define NAME_SIZE 26
#define EMAIL_SIZE 21
#define PHONE_NUM_SIZE 14

typedef struct Node{
    char name[NAME_SIZE];
    char email[EMAIL_SIZE];
    char phoneNum[PHONE_NUM_SIZE]; //KEY FOR EVERYTHING
    int points;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(const char* name, const char* email, const char* phoneNum, int points){
    Node* newNode = (Node*)malloc(sizeof(Node));
    strncpy(name, newNode->name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0';
    strncpy(email, newNode->email, sizeof(newNode->email) - 1);
    newNode->email[sizeof(newNode->email) - 1] = '\0';
    strncpy(phoneNum, newNode->phoneNum, sizeof(newNode->phoneNum) - 1);
    newNode->phoneNum[sizeof(newNode->phoneNum) - 1] = '\0'; 
    newNode->points = points;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//validate functions

bool isValidPhoneNum(const char* phoneNum){
    size_t len = strlen(phoneNum);
    if (len < 10 || len > 13){
        return false;
    }

    for (int i = 0; i < len; i++){
        if (!isdigit(phoneNum[i])) return false;
    }
    return true;
}

bool isValidName(const char* name){
    size_t len = strlen(name);
    if (len < 5 || len > 25){
        return false;
    }
    if (strncmp(name, "Mr.", 3) == 0){
        if (len == 3){
            return false;
        }
        return true;
    } else if (strncmp(name, "Mrs.", 4) == 0){
        if (len == 4){
            return false;
        }
        return true;
    } else{
        return false;
    }
    return true;
}

bool isValidEmail(const char* email){
    size_t len = strlen(email);
    int atCount;
    if (len < 10 || len > 20){
        return false;
    }
    for (int i = 0; i < len; i++){
        char ch = email[i];
        if (ch == '@'){
            atCount++;
        }
        if (!isalnum(ch) || ch =='@'){
            return false;
        }
    }
    if (strncmp(email, ".com", 4) == 0){
        if (len == 4){
            return false;
        }
        return true;
    } else if (strncmp(email, ".co.id", 6) == 0){
        if (len == 6){
            return false;
        }
        return true;
    } else{
        return false;
    }
    return true;
}

bool isValidDrink(const char* drink){
    if (strcmp(drink, "Cafe Latte") != 0 || strcmp(drink, "Caramel Macchiato") != 0 || strcmp(drink, "Cappuccino") != 0 || strcmp(drink, "Cafe Mocha") != 0){
        return false;
    }
    return true;
}

bool isValidDrinkQuantity(int quantity){
    if (quantity < 1){
        return false;
    }
    return true;
}

//input functions

void getCustomerPhoneNum(char* phoneNum){
    do{
        printf("Input phone number[10-13][numeric]: ");
        if (fgets(phoneNum, PHONE_NUM_SIZE, stdin) == 0) continue;
        phoneNum[strcspn(phoneNum, "\n")] = '\0';
    } while (!isValidPhoneNum(phoneNum));
}

void getCustomerName(char* name){
    do{
        printf("Input name[5-25][Mr. |Mrs. ]: ");
        if (fgets(name, NAME_SIZE, stdin) == 0) continue;
        name[strcspn(name, "\n")] = '\0';
    } while (!isValidName(name));
}

void getCustomerEmail(char* email){
    do{
        printf("Input email[10-20][email format]: ");
        if (fgets(email, EMAIL_SIZE, stdin) == 0) continue;
        email[strcspn(email, "\n")] = '\0';
    } while (!isValidEmail(email));
}

void getCustomerDrink(char* drink){
    do{
        printf("Input drink[Cafe Latte|Caramel Macchiato|Cappuccino|Cafe Mocha]: ");
    } while (!isValidDrink(drink));
}

void getCustomerQuantity(int* quantity){
    char input[20];
    do{
        printf("Input drink quantity[>= 1]: ");
        if (fgets(input, 20, stdin) == 0) continue;
        input[strcspn(input, "\n")] = '\0';
        *quantity = atoi(input);
    } while (!isValidDrinkQuantity(*quantity));
}

//BST operations

Node* searchCustomer(Node* root, char* phoneNum){
    Node* curr = root;
    while (curr != NULL){
        int res = strcmp(phoneNum, curr->phoneNum);
        if (res == 0){
            return curr;
        } else if (res < 0){
            curr = curr->left;
        } else{
            curr = curr->right;
        }
    }
    return NULL;
}

Node* insertCustomer(Node* root, const char* name, const char* email, const char* phoneNum, int points){
    Node* temp = createNode(name, email, phoneNum, points);
    if (root == NULL){
        return temp;
    }
    Node* curr = root;
    Node* parent = NULL;
    int res = strcmp(phoneNum, curr->phoneNum);
    while (curr != NULL){
        parent = curr;
        if (res < 0){
            curr = curr->left;
        } else if (res >= 0){
            curr = curr->right;
        } else{
            free(temp); //duplicate found
            return root;
        }
    }

    //link new node to the parent
    if (res < 0){
        parent->left = temp;
    } else{
        parent->right = temp;
    }
    return root;
}

void orderSummary(Node* root, const char* drink, int quantity){
    printf("Order summary:\n");
    for (int i = 0; i < MAX_SIZE; i++){
        printf("%-12s %dx", drink, quantity);
    }
}

void viewAllCustomer(Node* root){
    if (root == NULL){
        printf("There is no data !\n");
        printf("Press Enter to continue...\n"); getchar();
        return;
    } else{
        printf("---------------------------------------------------------------------------\n");
        printf("| Name                         | Phone Number  | Email           | Points |\n");
        printf("---------------------------------------------------------------------------\n");
        viewAllCustomer(root->left);
        printf("%-10s | %-5s | %-6s | %2d |\n", root->name, root->phoneNum, root->email, root->points);
        viewAllCustomer(root->right);
        printf("---------------------------------------------------------------------------\n");
    }
}

Node* getSucc(Node* root){ //utility for deletion
    Node* curr = root;
    while (curr && curr->left != NULL){
    	curr = curr->left;
	}
	return curr;
}

Node* removeCustomer(Node* root, char* phoneNum){
    if (root == NULL){
    	return NULL;
	}
	int res = strcmp(phoneNum, root->phoneNum);
	if (res < 0){
		root = removeCustomer(root->left, root->phoneNum);
	} else if (res > 0){
		root = removeCustomer(root->right, root->phoneNum);
	} else{
		if (root->left == NULL){
			Node* temp = root->right;
			free(root);
			return temp;
		}
		
		if (root->right == NULL){
			Node* temp = root->left;
			free(root);
			return temp;
		}
		
		Node* succ = getSucc(root->right);
		strncpy(succ->phoneNum, root->phoneNum, sizeof(succ->phoneNum) - 1);
		root->right = removeCustomer(root->right, succ->phoneNum);
	}
	return root;
}

void freeTree(Node* root){
    if (root != NULL){
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void menu(){
    Node* root = NULL;
    int choice, quantity;
    char phoneNum[PHONE_NUM_SIZE], name[NAME_SIZE], email[EMAIL_SIZE], drink[MAX_SIZE];
    do{
        printf("BlueBucks\n");
        printf("=========\n");
        printf("1. Process Order\n");
        printf("2. View All Customer\n");
        printf("3. Remove Customer\n");
        printf("4. Exit");
        printf(">> "); scanf("%d", &choice);

        switch (choice){
        case 1:{ //process order
            getCustomerPhoneNum(phoneNum);
            Node* searched = searchCustomer(root, phoneNum);
            if (searched != NULL){ //if registered user
                char choice;
                printf("Do you want to use your points[You have %d points][y|n]: "); scanf("%c", &choice);
            } else{ //if non-registered user
                getCustomerName(name);
                getCustomerEmail(email);
                printf("Insert success !\n");
            }
            break;
        }
        case 2: //view all customer
            viewAllCustomer(root);
            break;
        case 3:{ //remove customer
            getCustomerPhoneNum(phoneNum);
            Node* searched = searchCustomer(root, phoneNum);
            if (searched != NULL){ //if found
                removeCustomer(root, phoneNum);
                printf("Delete success !\n");
                printf("Press Enter to continue ...\n"); getchar();
            } else{
                printf("Data invalid !\n");
                printf("Press Enter to continue ...\n"); getchar();
            }
            break;
        }
        case 4: //exit
            break;
        default:
            printf("bradar invalid input\n");
            break;
        }
    } while (choice != 4);
    freeTree(root);
}

int main(){
    menu();
    return 0;
}
