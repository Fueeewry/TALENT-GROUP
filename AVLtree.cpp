#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node{
	int num;
	Node *left,*right;
	int height, bf;
}Node;

Node *createNode(int num){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->num = num;
	newNode->height = 1;
	newNode->bf = 0;
	newNode->left = newNode->right = NULL;
	
	return newNode;
}

int maxHeight(int a,int b){
	return (a>b)?a:b;
}

int getHeight(Node *root){
	if(root == NULL)return 0;
	else return root->height;
}

int computeHeight(Node *node){
	return maxHeight(getHeight(node->left), getHeight(node->right)) + 1;
}

Node *updateNode(Node *node){
	node->height = computeHeight(node);
	node->bf = getHeight(node->left) - getHeight(node->right);
}

Node *leftRotate(Node *root){
	Node *pivot = root->right;
	Node *temp = root->left;
	
	pivot->left = root;
	pivot->right = temp;
	
	root = updateNode(root);
	pivot = updateNode(pivot);
	
	return pivot;
}

Node *rightRotate(Node *root){
	Node *pivot = root->left;
	Node *temp = root->right;
	
	pivot->right = root;
	pivot->left = temp;
	
	root = updateNode(root);
	pivot = updateNode(pivot);
	
	return pivot;
	
}
Node *rotation(Node *root){
	if(root->bf < -1 && root->right->bf < 0){
		return leftRotate(root);
	}else if(root->bf<-1 &&root->right->bf > 0){
		root->right = leftRotate(root);
		return leftRotate(root);
	}else if(root->bf > 1 && root->left->bf > 0){
		return rightRotate(root);
	}else if(root->bf>1 && root->left->bf <0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
}

Node *insert(Node *root,int num){
	if(root==NULL){
		return createNode(num);
	}else if(num < root->num){
		root->right = insert(root->left,num);
	}else if(num > root->num){
		root->left = insert(root->right,num);
	}
	
	root = updateNode(root);
	
	return rotation(root);
}

void inOrder(Node *root){
	if(root ==NULL) return;
	inOrder(root->left);
	printf("%d\n",root->num);
	inOrder(root->right);
}

Node* searchNode(Node* root,int value){
	
	if(root==NULL){
		return root;
	}
	
	if(root->num == value){
		return root;
	}else if(value<root->num){
		return searchNode(root->left,value);
	}else if(value>root->num){
		return searchNode(root->right,value);
	}
}

Node* minValueNode(Node* node){
	Node* cur = node;
	while(cur->left!=NULL){
		cur = cur->left;
	}
	return cur;
}
Node* deleteNode(Node* root, int value){
	if(root==NULL){
		return root;
	}
	if(value<root->num){
		root->left = deleteNode(root->left,value);
	}else if(value>root->num){
		root->right = deleteNode(root->right,value);
	}else{
		if(root->left ==NULL||root->right ==NULL){
			Node* temp = root->left ==NULL? root->right : root->left;
			
			if(temp ==NULL){
				temp = root;
				root = NULL;
			}else{
				*root = *temp;
			}
			
			free(temp);
		}else{
			Node* temp = minValueNode(root->right);
			root->num = temp->num;
			root->right = deleteNode(root->right, temp->num);
		}
		
		if(root==NULL){
			return root;
		}
	}
}

void deleteAll(Node* root){
	if(root==NULL)return;
	
	deleteAll(root->left);
	deleteAll(root->right);
	free(root);
}

Node *updateNode(Node *root, int oldValue, int newValue){
	Node* temp = searchNode(root, oldValue);
	if(temp!=NULL){
		root=deleteNode(root,oldValue);
		root=deleteNode(root,newValue);
	}
	//node->height = computeHeight(node);
	//node->bf = getHeight(node->left) - getHeight(node->right);
	return root;
}

int main(){
	
	Node *root = NULL;
	root = insert(root,4);
	root = insert(root,5);
	//root = insert(root,6);
	inOrder(root);
	
	
	return 0;
}
