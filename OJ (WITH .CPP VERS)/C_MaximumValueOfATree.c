#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//node structure of BST
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

//create a new node for BST
struct Node* createNode(int x){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = x;
    newNode->left = newNode->right= NULL;
    return newNode;
}

//find max of a node
int findMax(struct Node* root){
    if (root == NULL) return -1; //should not happen

    struct Node* curr = root;
    while (curr->right != NULL){
        curr = curr->right;
    }
    return curr->data;
}

//insertion of a new node
struct Node* insert(struct Node* root, int x){
    //if tree is empty, create new root
    if (root == NULL){
        return createNode(x);
    }
    
    struct Node* curr = root;
    struct Node* parent = NULL;
    
    //finding insertion point
    while (curr != NULL){
        parent = curr; //update parent

        if (x < curr->data){
            curr = curr->left;
        } else if (x > curr->data){
            curr = curr->right;
        } else{
            return root; //for handling duplicates
        }
    }

    struct Node* newNode = createNode(x);
    
    //if x is smaller, make it left child. if not, make it right child
    if (x < parent->data){
        parent->left = newNode;
    } else{
        parent->right = newNode;
    }
    return root;
}

//to prevent memory leak
void freeTree(struct Node* root){
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(){
    struct Node* root = NULL;
    int q, x;
    scanf("%d", &q);

    for (int i = 0; i < q; i++){
        scanf("%d", &x);
        root = insert(root, x);

        int maxVal = findMax(root);
        printf("%d\n", maxVal);
    }

    //clean-up
    freeTree(root);
    return 0;
}