#include <stdio.h>
#include <stdlib.h>

//BST node structure
typedef struct Node{
    int val; //KEY
    char type;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int val, char type){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->type = type;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int val, char type){
    Node* newNode = createNode(val, type);
    if (root == NULL){
        return newNode;
    }
    Node* curr = root;
    Node* parent = NULL;
    while (curr != NULL){
        parent = curr;
        if (val < curr->val){
            curr = curr->left;
        } else if (val > curr->right){
            curr = curr->right;
        } else{
            free(newNode);
            return root;
        }
    }
    if (val < parent->val){
        parent->left = newNode;
    } else{
        parent->right = newNode;
    }
    return root;
}

//display with DFS
int countMagicTri(Node* root){
    if (root == NULL) return;

    Node* stack[1000001];
    int top = -1, count = 0;
    stack[++top] = root;

    while (top >= 0){
        Node* curr = stack[top--];

        //check magic triangle conditions
        if (curr->type == 'V' && curr->left && curr->type == 'I' && curr->right && curr->type == 'R'){
            if (curr->val == curr->left->val * curr->right->val){ //V = I * R condition
                count++;
            }
        }
        //push children
        if (curr->right) stack[++top] = curr->right;
        if (curr->left) stack[++top] = curr->left;
    }
    return count;
}

void freeTri(Node* root){
    if (root != NULL){
        free(root->left);
        free(root->right);
        free(root);
    }
}

int main(){
    Node* root = NULL;
    int n, val;
    char letter;
    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        scanf("%d %c");
        insert(root, val, letter);
    }
    int count = countMagicTri(root);
    printf("%d\n", count);
    freeTri(root);
    return 0;
}