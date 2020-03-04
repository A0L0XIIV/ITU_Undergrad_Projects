#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
 
using namespace std;
 
struct node{
    int number,sum,numOfNodes;
    struct node *left,*right;
}*root;
 
int N;
int *ar;
 
 
void add( node *root , int k ){
     
     node* newNode, *traverse, *parent;
     newNode = new node;
     newNode->left = NULL;
	 newNode->right = NULL;
     newNode->number = k;
     traverse = new node;
     parent = new node;
     traverse = root;
     parent = root;
     
     if(root == NULL)						//Aðaç boþsa
     	root->number = k;
							
	while(traverse){ 						//Yeni gelecek sayýnýn konulacaðý yeri bulur ve onun bir üstünü parent yapar, böylece yeni node parent'ýn altýna gelir
		parent = traverse;
		if(k < traverse->number)
			traverse = traverse->left;
		else
			traverse = traverse->right;
	}
	if(k > parent->number) 					//Yeni sayý parent sayýsýndan büyükse saða, küçükse sola konur
		parent->right = newNode;
	else
		parent->left = newNode;
     
}
 
 
void createTree(){
     
    cout << "Enter N: ";
    cin >> N;
     
    root=new node;
    ar=new int[N];
    int rndm;
    bool rndmOk;
     
    for( int i=0 ; i<N ; i++ ){
        rndm=rand()%(3*N);
        rndmOk = true;
        for(int j=0;j<i;j++){
        	if(ar[j] == ar[i])
        		rndmOk = false;
		}
		if(rndmOk == true)
			ar[i] = rndm;
		else{									//Ayný ise tekrar dön
			i--;
			break;
		}
    }
     
    for( int i=0 ; i<N ; i++ ){
    	add(root,ar[i]);
    }
     
    for( int i=0 ; i<N ; i++ )
        cout << ar[i] << ' ';
     
    cout << endl;
    delete(ar);
}
 
 
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
    node* traverse;
    traverse = t;
    int max = traverse->number;
    if(traverse->left != NULL){
		int max1 = findMax(traverse->left);
		if(max < max1)
			max = max1;
	}
    else if(traverse->right != NULL){
		int max2 = findMax(traverse->right);
		if(max < max2)
			max = max2;
	}
    return max;
}
 
 
int findMin(){
    return root->minValue;
}
 
 
int findNumNode(){
    return root->numOfNodes;
}
 
 
int findNumLeaf( node *t ){
     
    if( t->left && t->right )
        return findNumLeaf(t->left)+findNumLeaf(t->right);
    if( t->left && !t->right )
        return findNumLeaf(t->left);
     
    return 1;
}
 
 
int calculateDepth( node *t , int dep ){
     
    if( t->left && t->right )
        return max(calculateDepth(t->left,dep+1),calculateDepth(t->right,dep+1));
    if( t->left && !t->right )
        return calculateDepth(t->left,dep+1);
     
    return dep;
}
 
 
int calculateSum(){
    return root->sum;
}
 
double calculateAverage(){
    return (double)root->sum/(double)N;
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
				numNode = findNumNode();
				cout << "Number of the nodes = " << numNode << endl;
				break;
			case 7:
				int numLeaf;
				numLeaf = findNumLeaf(root);
				cout << "Number of the leaves = " << numLeaf << endl;
				break;
			case 8:
				int depth;
				depth = calculateDepth(root, 1);
				cout << "Depth = " << depth << endl;
				break;
			case 9:
				int sum;
				sum = calculateSum();
				cout << "Sum = " << sum << endl;
				break;
			case 10:
				int average;
				average = calculateAverage();
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
