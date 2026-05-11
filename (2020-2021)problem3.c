#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node* left;
	struct Node* right;
} Node;

Node* createNode(int x){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = x;
	newNode->left = newNode->right = NULL;
	return newNode;
}

Node* search(Node* root, int x){
	Node* curr = root;

	while (curr != NULL && curr->data != x){
		if (x < curr->data){
			return curr->left;
		} else{
			return curr->right;
		}
	}
	return curr;
}

Node* insert(Node* root, int x){
	if (root == NULL){
		return createNode(x);
	}

	Node* curr = root;
	Node* parent = NULL;
	
	while (curr != NULL){
		parent = curr; //upd parent as curr

		if (x < curr->data){
			curr = curr->left;
		} else if (x > curr->data){
			curr = curr->right;
		} else{
			return root;
		}
	}

	Node* newNode = createNode(x);
	if (x < parent->data){
		parent->left = newNode;
	} else{
		parent->right = newNode;
	}
	return root;
}

void inorder(Node* root){
	if (root != NULL){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void preorder(Node* root){
	if (root != NULL){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(Node* root){
	if (root != NULL){
		postorder(root->left);
		postorder(root->right);
		printf("%d", root->data);
	}
}

Node* remove(Node* root, int x){
	if (root == NULL){
		return root;
	}

	if (root->data > x){
		root->left = remove(root->left, x);
	} else if (root->data < x){
		root->right = remove(root->right, x);
	} else{
		if (root->left == NULL && root->right == NULL){
			free(root);
			return;
		} else if (root->left != NULL && root->right != NULL){
			Node* temp;
		} else{
			Node* temp = root->left;
		}
	}
	return root;
}

int minVal(Node* root){
	if (root == NULL){
		return -1;
	}

	Node* curr = root;
	while (curr->left != NULL){
		curr = curr->left;
	}
	return curr->data;
}

int maxVal(Node* root){
	if (root == NULL){
		return -1;
	}

	Node* curr = root;
	while (curr->right != NULL){
		curr = curr->right;
	}
	return curr->data;
}

int countNodes(Node* root){
	if (root == NULL){
		return -1;
	}
	return 1 + countNodes(root->left) + countNodes(root->right);
}

int height(Node* root, int h){
	if (root == NULL){
		return h - 1;
	}
	int leftHeight = height(root->left, h + 1);
	int rightHeight = height(root->right, h + 1);
	return (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int main(){
	return 0;
}