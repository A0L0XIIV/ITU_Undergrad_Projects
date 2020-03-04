#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

struct node {
	int number;
	node *left;
	node *right;
};
struct tree {
	node *root;
	void create();
	void createTree();
	void removeTree(node* t);
	void printPreorder(node* t);
	void printInorder(node* t);
	void printPostorder(node* t);
	int findMax(node* t);
	int findMin(node* t);
	int findNumNode(node* t);
	int findNumLeaf(node* t);
	int calculateDepth(node* t);
	int calculateSum(node* t);
	int calculateAverage(node* t);
};

using namespace std;

tree BST;
//srand(time(NULL));

int main(){
	
	srand(time(NULL));
	
	BST.create();
	BST.createTree();
	
	cout << "Binary search tree porgram" << endl;
	cout << "0. Exit" << endl;
	cout << "1. Print Preorder" << endl;
	cout << "2. Print Inorder" << endl;
	cout << "3. Print Postorder" << endl;
	cout << "4. Find Max" << endl;
	cout << "5. Find Min" << endl;
	cout << "6. Find Number of the Nodes" << endl;
	cout << "7. Find Number of the Leafs" << endl;
	cout << "8. Calculate Depth" << endl;
	cout << "9. Calculate Sum" << endl;
	cout << "10. Calculate Average" << endl;
	
	int choose = 0;
	bool condition = true;
	while(condition){
		cout << "Enter:";
		cin >> choose;
		switch( choose ){
			case 0:
				condition = false;
				break;
			case 1:
				BST.printPreorder(BST.root);
				break;
			case 2:
				BST.printInorder(BST.root);
				break;
			case 3:
				BST.printPostorder(BST.root);
				break;
			/*case 4:
				int max;
				max = BST.findMax(BST.root);
				cout << "Max = " << max << endl;
				break;
			case 5:
				int min;
				min = BST.findMin(BST.root);
				cout << "Min = " << min << endl;
				break;
			case 6:
				int numNode;
				numNode = BST.findNumNode(BST.root);
				cout << "Number of the nodes = " << numNode << endl;
				break;
			case 7:
				int numLeaf;
				numLeaf = BST.findNumLeaf(BST.root);
				cout << "Number of the leaves = " << numLeaf << endl;
				break;
			case 8:
				int depth;
				depth = BST.calculateDepth(BST.root);
				cout << "Depth = " << depth << endl;
				break;
			case 9:
				int sum;
				sum = BST.calculateSum(BST.root);
				cout << "Sum = " << sum << endl;
				break;
			case 10:
				int average;
				average = BST.calculateAverage(BST.root);
				cout << "Average = " << average << endl;
				break;*/
			default:
				cout << "Error invalid number!" << endl;
				break;
		}
	}	
	
	BST.removeTree(BST.root);
	exit(1);
	
}


void tree::create(){
	BST.root = NULL;
}

	
void tree::createTree(){
	
	srand(time(NULL));
	node* root;
	root = new node;
	root->left = NULL;
	root->right = NULL;
	root = BST.root;
	
	int N = 50 + rand()%50;
	int size = 5 + rand()%5;
	int array[size];
	int number = 1 + rand()%10;
	
	for(int i=0; i<size; i++){
		array[i] = number;
		if(number < N)
			number += 1 + rand()%10;
		else
			number += (N - number) % (rand()%5);
	}
	
	//node* t = new node;
	node* parent;
	node* traverse;
	traverse = root;
	
	for(int j=0; j<size; j++){
		node* t = new node;
		t->left = NULL;
		t->right = NULL;
		t->number = array[j];
		
		if(BST.root == NULL) 						//Aðaç boþsa yeni sayý root olur
			root = t;
		else{
			while(traverse){ 						//Yeni gelecek sayýnýn konulacaðý yeri bulur ve onun bir üstünü parent yapar, böylece yeni node parent'ýn altýna gelir
				parent = traverse;
				if(t->number < traverse->number)
					traverse = traverse->left;
				else
					traverse = traverse->right;
			}
			if(t->number > parent->number) 			//Yeni sayý parent sayýsýndan büyükse saða, küçükse sola konur
				parent->right = t;
			else
				parent->left = t;
		}
	}		
}
	
void tree::removeTree(node* t){
	
	/*if(root == NULL)
		cout << "This BST is already empty" << endl;
		return;
	else{
		
	}*/
	
	if (t) {
		if (t->left != NULL){
			removeTree(t->left);
			t->left = NULL;
		}
		if (t->right != NULL){
			removeTree(t->right);
			t->right = NULL;
		}
		delete t;
	}
	
}


void tree::printPreorder(node* t){
	
	if (t) {
		cout << t->number << endl;
		BST.printPreorder(t->left);
		BST.printPreorder(t->right);
	}
	
}

void tree::printInorder(node* t){
	
	if (t) {
		BST.printInorder(t->left);
		cout << t->number << endl;
		BST.printInorder(t->right);
	}
	
}


void tree::printPostorder(node* t){
	
	if (t) {
		BST.printPostorder(t->left);
		BST.printPostorder(t->right);
		cout << t->number << endl;
	}
	
}


int tree::findNumNode(node* t){
	
}


int tree::findNumLeaf(node* t){
	
}


int tree::calculateDepth(node* t){
	
}


int tree::calculateSum(node* t){
	
}


int tree::calculateAverage(node* t){
	
}
























