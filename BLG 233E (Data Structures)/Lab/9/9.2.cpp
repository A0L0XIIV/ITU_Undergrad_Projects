#include <ctime>
#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;

int N;

struct node {
	int number;
	node *left;
	node *right;
};
struct tree {
	node *root;
	void add(int);
	void createTree();
	int nodecount;
	int sum;
	void printPostorder(node*);
	void printPreorder(node*);
	void printInorder(node*);
	int findNumNode(node *);
	int findNumLeaf(node *);
	int findMax(node *);
	int findMin(node*);
	int calculateDepth(node*);
	float calculateAvarage();
	int calculateSum(node *);
	void remove(node *);
};

int main(){
	cout<<"n gir:"<<endl;
	cin>>N;
	
    tree tree;
    srand(time(NULL));
    
    tree.createTree();
    cout <<"Postorder:   ";
    tree.printPostorder(tree.root);
    cout << endl << "Inorder :    " ;
    tree.printInorder(tree.root); cout << endl;
    cout  <<"Preorder:    " ;
    tree.printPreorder(tree.root);
    cout << endl;
    cout << "Depth:  " <<  tree.calculateDepth(tree.root) << endl;
    cout << "Sum:   " << tree.calculateSum(tree.root) << endl;
    cout <<"Avarage:  " <<  tree.calculateAvarage() << endl;
    cout <<"Max:   " << tree.findMax(tree.root) << endl;
    cout << "Min   " << tree.findMin(tree.root) << endl;
    cout << "Number of Leaves:  " << tree.findNumLeaf(tree.root) << endl;
    cout << "Number of Nodes :  " << tree.findNumNode(tree.root) << endl;
    
    tree.remove(tree.root);
}


void tree::add(int toadd){
             node *traverse, *newnode;
             traverse = root;
             newnode = new node;
             newnode->number=toadd;
             newnode->left = NULL;
             newnode->right = NULL;
             if (root == NULL){
                root = newnode;
                return;
             }
             if(root->left==NULL){
				root->left=newnode;
				return;
             }
             if(root->right==NULL){
				root->right=newnode;
				return;
             }
             int l,r;
             while(findNumNode(traverse)>2){

				l=findNumNode(traverse->left);
				r=findNumNode(traverse->right);
				
				if (l < r) traverse = traverse->left;
				else if (l>r) traverse = traverse->right;
				else if (l==r) traverse = traverse->left;
             }
             if(traverse->left==NULL){
				traverse->left=newnode;
				return;
             }
             if(traverse->right==NULL){
				traverse->right=newnode;
				return;
             }


}

void tree::createTree(){
     root=NULL;
     nodecount=0;
     int array[N];
     for(int i=0; i<N; i++){
             array[i]=rand() % N+1;
             add(array[i]);
     }
    for(int i=0;i<N;i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

void tree::printPostorder(node *nptr) {
    if (nptr) {
        printPostorder(nptr->left);
        printPostorder(nptr->right);
        cout << nptr->number << " ";
    }
}
void tree::printInorder(node *nptr) {
    if (nptr) {
        printInorder(nptr->left);
        cout << nptr->number << " ";
        printInorder(nptr->right);

    }
}

void tree::printPreorder(node *nptr) {
    if (nptr) {
        cout << nptr->number << " ";
        printPreorder(nptr->left);
        printPreorder(nptr->right);

    }
}

int tree::findNumNode(node* ptr){
    if(ptr){
    	return 1+findNumNode(ptr->left)+findNumNode(ptr->right);
    }
    return 0;
}
int tree::findNumLeaf(node* ptr){
    if(ptr==NULL)
        return 0;
    if(ptr->left==NULL && ptr->right==NULL)
        return 1;
    return findNumLeaf(ptr->left)+findNumLeaf(ptr->right);
}

int tree::findMax(node* ptr){
    if(ptr==NULL)
        return -1;
    int left=findMax(ptr->left),
        right=findMax(ptr->right),
        m=0;
    if(m<ptr->number) m=ptr->number;
    if(m<left) m=left;
    if(m<right) m=right;
    return m;
}

int tree::findMin(node* ptr){
    if(ptr==NULL)
        return N+1;
    int left=findMin(ptr->left),
        right=findMin(ptr->right),
        m=N+1;
    if(m>ptr->number) m=ptr->number;
    if(m>left) m=left;
    if(m>right) m=right;
    return m;
}
int tree::calculateDepth(node *ptr){
    int depth = 0;
    while(1){
        if(ptr==NULL)
            break;
        depth++;
        ptr = ptr -> left;

    }
    return depth;
}
int tree::calculateSum(node *ptr){
    if(ptr==NULL)
        return -1;
    if (ptr->left==NULL && ptr->right == NULL)
        return ptr->number;
    return ptr->number+calculateSum(ptr->right)+calculateSum(ptr->left);
}
float tree::calculateAvarage(){
    return (float)calculateSum(root)/(float)N;
}
void tree::remove(node *p){

    if (p){
        if (p->left != NULL){
            remove(p->left);
            p->left = NULL;
    }
        if (p->right != NULL){
            remove(p->right);
            p->right = NULL;
    }
        delete p;
    }
}
