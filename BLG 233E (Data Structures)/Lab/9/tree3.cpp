#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
 
using namespace std;
 
struct node{
    int number;
    struct node *left,*right;
}*root;
 
int N;
int *ar;
 
 
void printPreorder( node *t ){
     
    if (t) {
		cout << t->number << " ";
		printPreorder(t->left);
		printPreorder(t->right);
	}
}
 
 
void printInorder( node *t ){
     
    if (t) {
		printInorder(t->left);
		cout << t->number << " ";
		printInorder(t->right);
	}
}
 
 
void printPostorder( node *t ){
     
     if (t) {
		printPostorder(t->left);
		printPostorder(t->right);
		cout << t->number << " ";
	}
}
 
 
void removeTree( node *t ){
     
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
 
 
int findMax( node *t ){
    /*node* traverse;
    traverse = t;
    int maxValue = traverse->number;
    if(traverse->left != NULL){
		int max1 = findMax(traverse->left);
		if(maxValue < max1)
			maxValue = max1;
	}
    else if(traverse->right != NULL){
		int max2 = findMax(traverse->right);
		if(maxValue < max2)
			maxValue = max2;
	}
    return maxValue;*/
    int maxValue = t->number;
    if(t->left != NULL){
		int max1 = findMax(t->left);
		if(maxValue < max1)
			maxValue = max1;
	}
    else if(t->right != NULL){
		int max2 = findMax(t->right);
		if(maxValue < max2)
			maxValue = max2;
	}
    return maxValue;
}
 
 
int findMin( node *t ){
    /*node* traverse;
    traverse = t;
    int minValue = traverse->number;
    if(traverse->left != NULL){
		int min1 = findMin(traverse->left);
		if(minValue > min1)
			minValue = min1;
	}
    else if(traverse->right != NULL){
		int min2 = findMin(traverse->right);
		if(minValue > min2)
			minValue = min2;
	}
    return minValue;*/
    int minValue = t->number;
    if(t->left != NULL){
		int min1 = findMin(t->left);
		if(minValue > min1)
			minValue = min1;
	}
    else if(t->right != NULL){
		int min2 = findMin(t->right);
		if(minValue > min2)
			minValue = min2;
	}
    return minValue;
}
 
 
int findNumNode( node *t ){
    /*node* traverse;
    traverse = t;
    int counter = 1;
    if(traverse->left != NULL){
		counter += findNumNode(traverse->left);
	}
    else if(traverse->right != NULL){
    	counter += findNumNode(traverse->right);
	}
    return counter;*/
    if(t){
		return 1 + findNumNode(t->left) + findNumNode(t->right);
    }
    return 0;
}
 
 
int findNumLeaf( node *t ){
    node* traverse;
    traverse = t;
    int counter = 1;
    if(traverse->left != NULL){
		if(traverse->left == NULL && traverse->right == NULL)
			counter += findNumLeaf(traverse->left);

	}
    else if(traverse->right != NULL){
		if(traverse->left == NULL && traverse->right == NULL)
			counter += findNumLeaf(traverse->right);
	}
    return counter;
}
 
 
int calculateDepth( node *t ){
    /*node* traverse;
    traverse = t;
    int counter = 1;
    if(traverse->left != NULL){
    	traverse = traverse->left;
		counter++;
	}
    return counter;*/
    int counter = 1;
    if(t->left != NULL){
    	t = t->left;
		counter++;
	}
    return counter;
}
 
 
int calculateSum( node *t ){
    node* traverse;
    traverse = t;
    int sum = 0;
    if(traverse->left != NULL){
		int min1 = calculateSum(traverse->left);
		sum += traverse->number;
	}
    else if(traverse->right != NULL){
		int min2 = calculateSum(traverse->right);
		sum += traverse->number;
	}
    return sum;
}
 
double calculateAverage( node *t ){
	int sum = calculateSum(root);
	int numOfNodes = findNumNode(root);
	double average;
	average = sum / numOfNodes;
	return average;
}


void add(int k){//( node *t , int k ){
     
    /*if( !t->left ){
         
        t->left = new node;
        t->left->number = k; 
        t->left->left=NULL;
        t->left->right=NULL;
    }
    else if( !t->right ){
         
        t->right = new node;
        t->right->number = k;
        t->right->left=NULL;
        t->right->right=NULL;
    }
    
    int numOfLeft, numOfRight;
    
	while( findNumNode(t) > 2 ){
	
		numOfLeft = findNumNode(t->left);	
		numOfRight = findNumNode(t->right);
		
		if ( numOfLeft < numOfRight )
			t = t->left;
		else if ( numOfLeft > numOfRight )
			t = t->right;
		else if ( numOfLeft == numOfRight )
			t = t->left;
	}
	if(t->left == NULL){
		t->left = new node;
		t->left->number = k;
		t->left->left = NULL;
		t->left->right = NULL;
		return;
	}
	if(t->right == NULL){
		t->right = new node;
		t->right->number = k;
		t->right->left = NULL;
		t->right->right = NULL;
		return;
	}*/
	node *nodeAdd, *traverse;
	traverse = root;
	nodeAdd = new node;
	nodeAdd->number = k;
	nodeAdd->left = nodeAdd->right = NULL;
	
	if(root == NULL){
		root = nodeAdd;
		return;
	}
	
	if( !root->left ){
        root->left = nodeAdd;
        return;
    }
    else if( !root->right ){
        root->right = nodeAdd;
        return;
    }
    
    int numOfLeft, numOfRight;
    
	while( findNumNode(traverse) > 2 ){
	
		numOfLeft = findNumNode(traverse->left);	
		numOfRight = findNumNode(traverse->right);
		
		if ( numOfLeft < numOfRight )
			traverse = traverse->left;
		else if ( numOfLeft > numOfRight )
			traverse = traverse->right;
		else if ( numOfLeft == numOfRight )
			traverse = traverse->left;
	}
	if(traverse->left == NULL){
		traverse->left = nodeAdd;
		return;
	}
	if(traverse->right == NULL){
		traverse->right = nodeAdd;
		return;
	}
}
 
 
void createTree(){
     
    cout << "Enter N: ";
    cin >> N;
     
    //root=new node;
    root = NULL;
    ar=new int[N];
     
    for( int i=0 ; i<N ; i++ )
        ar[i]=rand()%N;
     
    //root->number=ar[0];
     
    for( int i=0 ; i<N ; i++ )
    	add(ar[i]);
        //add(root,ar[i]);
     
    for( int i=0 ; i<N ; i++ )
        cout << ar[i] << ' ';
     
    cout << endl;
    delete(ar);
}
 
 
int main(){
     
    srand(time(NULL));
     
    createTree();
     
    cout << "Binary search tree program" << endl;
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
				printPreorder(root);
				cout << endl;
				break;
			case 2:
				printInorder(root);
				cout << endl;
				break;
			case 3:
				printPostorder(root);
				cout << endl;
				break;
			case 4:
				int max;
				max = findMax(root);
				cout << "Max = " << max << endl;
				break;
			case 5:
				int min;
				min = findMin(root);
				cout << "Min = " << min << endl;
				break;
			case 6:
				int numNode;
				numNode = findNumNode(root);
				cout << "Number of the nodes = " << numNode << endl;
				break;
			case 7:
				int numLeaf;
				numLeaf = findNumLeaf(root);
				cout << "Number of the leaves = " << numLeaf << endl;
				break;
			case 8:
				int depth;
				depth = calculateDepth(root);
				cout << "Depth = " << depth << endl;
				break;
			case 9:
				int sum;
				sum = calculateSum(root);
				cout << "Sum = " << sum << endl;
				break;
			case 10:
				double average;
				average = calculateAverage(root);
				cout << "Average = " << average << endl;
				break;
			default:
				cout << "Error invalid number!" << endl;
				break;
		}
	}	
     
    if( root )
        removeTree(root);
    return 0;
}
