/***************\
|	150130032	|
|	Baran Kaya	|
\***************/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstring>

#define black 0
#define red 1

using namespace std;

//---------------------------------------------------------TREE NODE---------------------------------------------------------


class  TreeNode{
private:
	string name;
	char gender;
	unsigned int age;
	unsigned int num_woman;
	unsigned int num_man;
	bool color; //1 bit color -> 0=Black, 1=Red
	TreeNode *left, *right, *parent;
public:
	TreeNode() {
		name = "\0";
		gender = '\0';
		age = 0;
		num_woman = num_man = 0;
		color = black;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	TreeNode(string newName, char newGender, unsigned int newAge) {
		name = newName;
		gender = newGender;
		age = newAge;
		num_woman = num_man = 0;
		color = black;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	unsigned int getAge() {
		return age;
	}
	string getName() {
		return name;
	}
	char getGender() {
		return gender;
	}
	void setColor(bool Color) {
		color = Color;
	}
	bool getColor() {
		return color;
	}
	void setLeft(TreeNode* newLeft) {
		left = newLeft;
	}
	TreeNode* getLeft() {
		return left;
	}
	void setRight(TreeNode* newRight) {
		right = newRight;
	}
	TreeNode* getRight() {
		return right;
	}
	void setParent(TreeNode* newParent) {
		parent = newParent;
	}
	TreeNode* getParent() {
		return parent;
	}
	void setNumWoman(unsigned int NW) {
		num_woman = NW;
	}
	unsigned int getNumWoman() {
		return num_woman;
	}
	void setNumMan(unsigned int NM) {
		num_man = NM;
	}
	unsigned int getNumMan() {
		return num_man;
	}
};


//---------------------------------------------------------RED BLACK TREE---------------------------------------------------------

class RedBlackTree {
	TreeNode *root, *NIL;
	void fixTheTree(TreeNode* lastNode);
	void leftRotation(TreeNode* lastNode);
	void rightRotation(TreeNode* lastNode);
	void printTree(TreeNode* traverse, unsigned int numOfTabs, char LorR);
	void updateGenderNumbers(TreeNode* traverse);
	TreeNode* findNthMan(TreeNode* traverse, int n);
	TreeNode* findNthWoman(TreeNode* traverse, int n);
public:
	RedBlackTree() {
		NIL = new TreeNode();	
		NIL->setLeft(NIL);
		NIL->setRight(NIL);
		NIL->setParent(NIL);
		root = NIL;
	}
	~RedBlackTree() {
		delete NIL;
	}
	void insert(TreeNode* newNode);
	void print() {
		printTree(root, 0, 'M');
	};
	void countGenders() {
		updateGenderNumbers(root);
	}
	string NthMan(int n);
	string NthWoman(int n);

};


//---------------------------------------------------------RED BLACK TREE FUNCTIONS---------------------------------------------------------


void RedBlackTree::insert(TreeNode* newNode) {

	TreeNode* traverse = root;
	TreeNode* traverseParent = NIL;

	//If tree is empty
	if (root == NIL) {
		root = newNode;
		newNode->setParent(NIL);
	}

	//If tree is not empty, first find the correct location
	else {
		//Locating the newNode's location
		while (traverse != NIL && traverse != NULL) {
			//Hold the traverse's previous location (parent)
			traverseParent = traverse;
			//Find left or right
			if (newNode->getName() < traverse->getName())
				traverse = traverse->getLeft();
			else
				traverse = traverse->getRight();
		}
		//Assign newNode's parent to the traverseParent
		newNode->setParent(traverseParent);

		//Assign traverseParent's left or right child to newNode
		if (newNode->getName() < traverseParent->getName())
			traverseParent->setLeft(newNode);
		else
			traverseParent->setRight(newNode);

	}

	//Set newNode's children and fix the tree violation
	newNode->setLeft(NIL);
	newNode->setRight(NIL);
	newNode->setColor(red);
	fixTheTree(newNode);
}


void RedBlackTree::printTree(TreeNode* traverse, unsigned int numOfTabs, char LorR) {

	numOfTabs++;

	//traverse come to leaves -> NIL
	if (traverse == NIL || traverse == NULL){
		return;

	printTree(traverse->getLeft(), numOfTabs, 'L');

	for (int i = 1; i < numOfTabs; i++)
		cout << "\t";

	if (LorR == 'R')
		cout << "^--";//Right child
	else if (LorR == 'L')
		cout << "v--";//Left child

	if (traverse->getColor() == 0)
		cout << "(B) ";
	else
		cout << "(R) ";
	cout << traverse->getName() << "-" << traverse->getAge() << "-" << traverse->getGender() << endl;

	printTree(traverse->getRight(), numOfTabs, 'R');
}


void RedBlackTree::fixTheTree(TreeNode* lastNode) {//rebalancing

	while (root != lastNode && lastNode->getParent()->getColor() == red) {
		//lastNode's parent is grand parent's left child
		if (lastNode->getParent() == lastNode->getParent()->getParent()->getLeft()) {
			
			TreeNode* rightChild = lastNode->getParent()->getParent()->getRight();

			//Case 1 -> Grand parent's right child is red -> Recolor
			if (rightChild != NIL && rightChild != NULL && rightChild->getColor() == red) {
				lastNode->getParent()->getParent()->setColor(red);
				lastNode->getParent()->setColor(black);
				rightChild->setColor(black);
				lastNode = lastNode->getParent()->getParent();
			}
			else {
				//Case 2 -> lastNode is the right child -> left rotation
				if (lastNode == lastNode->getParent()->getRight()) {
					lastNode = lastNode->getParent();
					leftRotation( lastNode );
				}
				//Case 3 -> lastNode is the left child -> right rotation
				lastNode->getParent()->getParent()->setColor(red);
				lastNode->getParent()->setColor(black);			
				rightRotation( lastNode->getParent()->getParent() );
			}
		}
		//lastNode's parent is grand parent's right child
		else {

			TreeNode* leftChild = lastNode->getParent()->getParent()->getLeft();

			//Case 1 -> Grand parent's left child is red -> Recolor
			if (leftChild != NIL && leftChild != NULL && leftChild->getColor() == red) {
				lastNode->getParent()->getParent()->setColor(red);
				lastNode->getParent()->setColor(black);
				leftChild->setColor(black);
				lastNode = lastNode->getParent()->getParent();
			}
			else {
				//Case 2 -> lastNode is the left child -> right rotation
				if (lastNode == lastNode->getParent()->getLeft()) {
					lastNode = lastNode->getParent();
					rightRotation( lastNode );
				}
				//Case 3 -> lastNode is the right child -> left rotation
				lastNode->getParent()->getParent()->setColor(red);
				lastNode->getParent()->setColor(black);
				leftRotation( lastNode->getParent()->getParent() );
			}
		}
	}
	root->setColor(black);
}


void RedBlackTree::leftRotation(TreeNode* lastNode) {

	TreeNode* rightNode = lastNode->getRight();
	lastNode->setRight(rightNode->getLeft());
	lastNode->getRight()->setParent(lastNode);//OR rightNode->getLeft()->setParent(lastNode);
	rightNode->setParent(lastNode->getParent());

	if (lastNode->getParent() == NIL || lastNode->getParent() == NULL) {
		root = rightNode;
	}
	else if (lastNode == lastNode->getParent()->getLeft()) {
		lastNode->getParent()->setLeft(rightNode);
	}
	else {
		lastNode->getParent()->setRight(rightNode);
	}

	rightNode->setLeft(lastNode);
	lastNode->setParent(rightNode);
}


void RedBlackTree::rightRotation(TreeNode* lastNode) {

	TreeNode* leftNode = lastNode->getLeft();
	lastNode->setLeft(leftNode->getRight());
	lastNode->getLeft()->setParent(lastNode);//OR leftNode->getRight()->setParent(lastNode);
	leftNode->setParent(lastNode->getParent());

	if (lastNode->getParent() == NIL || lastNode->getParent() == NULL) {
		root = leftNode;
	}
	else if (lastNode == lastNode->getParent()->getLeft()) {
		lastNode->getParent()->setLeft(leftNode);
	}
	else {
		lastNode->getParent()->setRight(leftNode);
	}

	leftNode->setRight(lastNode);
	lastNode->setParent(leftNode);
}


string RedBlackTree::NthMan(int n) {
	
	TreeNode* nthMan = findNthMan(root, n);
	if (nthMan == NIL)
		return "ERROR";
	else
		return nthMan->getName();
}


string RedBlackTree::NthWoman(int n) {

	TreeNode* nthWoman = findNthWoman(root, n);
	if (nthWoman == NIL)
		return "ERROR";
	else
		return nthWoman->getName();
}


TreeNode* RedBlackTree::findNthMan(TreeNode* traverse, int n) {//OS-SELECT(x,i)

	//r <- size[ left[x] ]+1
	int correctCount = traverse->getLeft()->getNumMan() + 1;//+1 is node's itself
	//if i=r -> return x
	if (correctCount == n && traverse->getGender() == 'M')
		return traverse;
	//else if i<r -> return OS-SELECT[ left[x],i ]
	else if (n < correctCount)
		findNthMan(traverse->getLeft(), n);
	//else -> return OS-SELECT[ right[x],i-r ]
	else if (n > correctCount)
		findNthMan(traverse->getRight(), n - correctCount);
	else
		return NIL;
}


TreeNode* RedBlackTree::findNthWoman(TreeNode* traverse, int n) {//OS-SELECT(x,i)

	//r <- size[ left[x] ]+1
	int correctCount = traverse->getLeft()->getNumWoman() + 1;//+1 is node's itself
	//if i=r -> return x
	if (correctCount == n && traverse->getGender() == 'F')
		return traverse;
	//else if i<r -> return OS-SELECT[ left[x],i ]
	else if (n < correctCount)
		findNthWoman(traverse->getLeft(), n);
	//else -> return OS-SELECT[ right[x],i-r ]
	else if (n > correctCount)
		findNthWoman(traverse->getRight(), n - correctCount);
	else
		return NIL;
}


void RedBlackTree::updateGenderNumbers(TreeNode* traverse) {//Function that updates the num_man and num_woman numbers with final state of the tree

	//Traverse in the tree
	if (traverse->getLeft() != NIL && traverse->getLeft() != NULL)
		updateGenderNumbers(traverse->getLeft());
	if (traverse->getRight() != NIL && traverse->getRight() != NULL)
		updateGenderNumbers(traverse->getRight());

	//Update nodes num_man or num_woman with node's gender
	if (traverse->getGender() == 'M')
		traverse->setNumMan(traverse->getNumMan() + 1);
	else if(traverse->getGender() == 'F')
		traverse->setNumWoman(traverse->getNumWoman() + 1);

	//Add parent node's children num_man and num_woman to parent node's gender numbers
	if (traverse->getLeft() != NIL && traverse->getLeft() != NULL) {
		traverse->setNumMan( traverse->getLeft()->getNumMan() + traverse->getNumMan() );
		traverse->setNumWoman( traverse->getLeft()->getNumWoman() + traverse->getNumWoman() );
	}
	if (traverse->getRight() != NIL && traverse->getRight() != NULL) {
		traverse->setNumMan( traverse->getRight()->getNumMan() + traverse->getNumMan() );
		traverse->setNumWoman( traverse->getRight()->getNumWoman() + traverse->getNumWoman() );
	}
}


