#include <iostream>
#include <ctime>
#include <fstream>
#include "tree.h"
#define N 10
using namespace std;

void BSF(node *root){
     Queue Q;
     Q.create();
     Q.enqueue(root);
     node* u;
     while(!Q.isempty()){
           u=Q.dequeue();            
           if(u->left) Q.enqueue(u->left);
           if(u->right) Q.enqueue(u->right);
           cout << u->number << " ";
     }
}

void DSF(node *root){
     Stack S;
     S.create();
     S.push(root);
     node* u;
     while (!S.isempty()){
           u=S.pop();
           if(u->right) S.push(u->right);
           if(u->left) S.push(u->left);
           cout << u->number << " ";
     }
}

void Stack::create(){
     head=NULL;
}

void Stack::close(){
	node *p;
	while (head){
		p = head;
		head = head->next;
		//delete [] p->data;
		delete p;
	}
}

void Stack::push(node *newdata){
	node *newnode = new node;
	newnode = newdata;
	newnode->number = newdata->number;
	newnode->next = head;
	head = newnode;
}

node *Stack::pop(){
	if (isempty())
		return NULL;
	node *topnode = head;
	head = head->next;
	//delete topnode;
	return topnode;
}
bool Stack::isempty(){
	return (head == NULL);
}

void Queue::enqueue(node* newdata){
	node *newnode = new node;
	newnode = newdata;
	newnode->left=newdata->left;
	newnode->right=newdata->right;
	newnode->number=newdata->number;
	newnode->next = NULL;
	if ( isempty() ) { // first element?
		back = newnode;
		front = back;
	}
	else {
		back->next = newnode;
		back = newnode;
	}
}

node *Queue::dequeue() {
	node *topnode;
	topnode = front;
	front = front->next;
	//delete topnode;
	return topnode;
}

bool Queue::isempty() {
	return front == NULL;
}

void Queue::create(){
	front = NULL; back = NULL;
}
void Queue::close(){
	node *p;
	while (front) {
		p = front;
		front = front->next;
		//delete [] p->data;
		delete p;
	}
}
srand(time(NULL));
void tree::add(int toadd){
             node *traverse, *newnode;
             traverse = root;
             int comparison;
             bool added = false;
             newnode = new node;
             newnode->number=toadd;
             newnode->left = NULL;
             newnode->right = NULL;
             if (root == NULL){//first node being added
                root = newnode;
                return;
             }
             while ((traverse != NULL) && (!added)){
                if(toadd < traverse->number) {
                   if (traverse->left != NULL)
                      traverse = traverse->left;
                   else {
                        traverse->left = newnode;
                        added = true;
                   }
                }
                else if(toadd > traverse->number) {
                     if (traverse->right != NULL)
                        traverse = traverse->right;
                     else {
                          traverse->right = newnode;
                          added = true;
                     }
                }
                else{
                     added=true;
                    cout << "Data cannot repeat.\n";
                }
             }

}
     
void tree::createTree(){
     root=NULL;
     nodecount=0;
     int array[N];
     for(int i=0; i<N; i++){
             x:
             array[i]=rand() % 20+1;
             for(int j=i-1; j>=0; j--){
                     if(array[j]==array[i]) goto x;}
             add(array[i]);
     }
}

int main(){
    tree tree;
    srand(time(0));
    tree.createTree();
    cout << endl<<"inorder:   ";
    tree.printInorder(tree.root, 14);
    cout << endl;
    cout << tree.nodecount-1 << endl;
    cout << "BSF: ";
    BSF(tree.root);
    cout << endl;
    cout << "DSF: ";
    DSF(tree.root);     
    system("pause");
}
bool a=false;
void tree::printInorder(node *nptr, int num) {
    if (nptr) {
        printInorder(nptr->left, num);
        if(a) return;
        cout << nptr->number << " ";
        nodecount++;
                        if(num==nptr->number){
                              cout << "bulundu";
                              a=true;
                              return;
                              }
        printInorder(nptr->right, num);
    }
}

