#include <stdio.h>
#include <stdlib.h>

//node structure for AVL tree
typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    int height; //height of the node
    int size;
} Node;

//function to create a node for the AVL tree
Node* createNode(int x){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; //new node is initially added at leaf
    return newNode;
}

//utility function to get height of the tree
int height(Node* root){
    if (root == NULL) return 0;
    return root->height;
}

//another utility function to get maximum of two integers
int maximum(int a, int b){
    return (a > b) ? a : b;
}

//function to right rotate subtree rooted with y
Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;

    //perform rotation
    x->right = y;
    y->left = T2;

    //update height
    y->height = maximum(height(y->left), height(y->right)) + 1;
    x->height = maximum(height(x->left), height(x->right)) + 1;

    //return new root
    return x;
}

//function to left rotate subtree rooted with x
Node* leftRotate(Node* x){
    Node* y = x->left;
    Node* T2 = y->right;

    //perform rotation
    y->right = x;
    x->left = T2;

    //update height
    x->height = maximum(height(x->left), height(x->right)) + 1;
    y->height = maximum(height(y->left), height(y->right)) + 1;

    //return new root
    return y;
}

//function to get the balance factor of a node
int getBalance(Node* node){
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

//function to insert a key into the AVL tree
Node* insert(Node* root, int key){
    if (root == NULL) return createNode(key);

    if (key < root->data){
        root->left = insert(root->left, key);
    } else if (key > root->data){
        root->right = insert(root->right, key);
    } else{
        return root; //handles duplicates
    }

    //update height of current node
    root->height = maximum(height(root->left), height(root->right)) + 1;

    //get the balance factor to check whether the node is not balanced
    int balance = getBalance(root);

    //left-left case
    if (balance > 1 && key < root->left->data){
        return rightRotate(root);
    }

    //right-right case
    if (balance < -1 && key > root->right->data){
        return leftRotate(root);
    }

    //left-right case
    if (balance > 1 && key > root->left->data){
        root->left = leftRotate(root);
        return rightRotate(root);
    }

    //right-left case
    if (balance < -1 && key < root->right->data){
        root->right = rightRotate(root);
        return leftRotate(root);
    }

    //return unchanged root
    return root;
}

//function to find the node with minimum value
Node* minValue(Node* root){
    Node* curr = root;
    while (curr->left != NULL){
        curr = curr->left;
    }
    return curr;
}

//function to delete a key from the AVL tree
Node* remove(Node* root, int key){
    if (root == NULL) return root;

    //basic BST deletion
    if (key < root->data){
        root->left = remove(root->left, key);
    } else if (key > root->data){
        root->right = remove(root->right, key);
    } else{
        //node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)){
            Node* temp = root->left ? root->left : root->right;

            //no child case
            if (temp == NULL){
                temp = root;
                return root;
            } else{   //one child case
                *root = *temp; //copy the contents of the non-empty child
                free(temp);
            }
        } else{
            //node with two children
            Node* temp = minValue(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
        //if the tree had only one node
        if (root == NULL) return root;

        //update height of the node
        root->height = maximum(height(root->left), height(root->right)) + 1;

        //get balance factor to check if the node is not balanced
        int balance = getBalance(root);

        //left-left case
        if (balance > 1 && getBalance(root->left) >= 0){
            return rightRotate(root);
        }

        //right-right case
        if (balance < -1 && getBalance(root->right) <= 0){
            return leftRotate(root);
        }

        //left-right case
        if (balance > 1 && getBalance(root->left) < 0){
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        //right-left case
        if (balance < -1 && getBalance(root->right) > 0){
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

//function to find the kth
int kthSmallest(Node* root, int k){
    if (root == NULL) return -1;
    int leftSize = (root->left != NULL) ? root->left->size : 0;
    if (k == leftSize + 1){
        return root->data;
    } else if (k <= leftSize){
        return kthSmallest(root->left, k);
    } else{
        return kthSmallest(root->right, k - leftSize - 1);
    }
}

//function to free memory of the AVL tree
void freeAVLTree(Node* root){
    if (root != NULL){
        freeAVLTree(root->left);
        freeAVLTree(root->right);
        free(root);
    }
}

int main(){
    Node* root = NULL;
    int n, q, k;
    scanf("%d %d %d", &n, &q, &k);

    for (int i = 0; i < n; i++){
        int val;
        scanf("%d", &val);
        root = insert(root, val);
    }

    for (int j = 0; j < q; j++){
        int val;
        scanf("%d", &val);
        root = remove(root, val);
    }
    printf("%d\n", kthSmallest(root, k));
    freeAVLTree(root);
    return 0;
}