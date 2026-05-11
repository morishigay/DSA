#include <iostream>
#include <stdlib.h>

//create node for BST
class Node{
    public:
    int data;
    Node* left;
    Node* right;

    //create a new node
    Node (int val){
        data = val;
        left = right = nullptr;
    }
};

int findMax(Node* root){
    if (root == NULL) return -1;
    Node* curr = root;
    while (curr->right){
        curr = curr->right;
    }
    return curr->data;
}

Node* insert(Node* root, int x){
    Node* temp = new Node(x);
    if (root == NULL) return temp;

    Node* curr = root;
    Node* parent = nullptr;
    while (curr){
        parent = curr;
        if (x < curr->data){
            curr = curr->left;
        } else if (x > curr->data){
            curr = curr->right;
        } else{
            return root;
        }
    }
    if (x < parent->data){
        parent->left = temp;
    } else{
        parent->right = temp;
    }
    return root;
}

void freeTree(Node* root){
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main(){
    Node* root = nullptr;
    int q, x;
    std::cin>>q;

    for (int i = 0; i < q; i++){
        std::cin>>x;
        root = insert(root, x);

        int maxVal = findMax(root);
        std::cout<<maxVal<<std::endl;
    }
    freeTree(root);
    return 0;
}
