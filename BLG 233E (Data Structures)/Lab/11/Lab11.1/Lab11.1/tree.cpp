#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>
#include <string>
#include <string.h>

using namespace std;

void Tree::create() {
	root = NULL;// create empty tree
	nodecount = 0;// initialize nodecount to 0
	//read_fromfile();
}


/*void Tree::read_fromfile() {
	struct File_Record {
		char name[NAME_LENGTH];
		char phonenum[PHONENUM_LENGTH];
	};
	File_Record record;
	Phone_node *newnode;
	filename = "phonebook.txt";
	if (!(phonebook = fopen(filename, "r+")))
		if (!(phonebook = fopen(filename, "w+"))) {
			cerr << "Could not open file." << endl;
			cerr << "Will work in" << " memory only." << endl;
			return;
		}
	fseek(phonebook, 0, SEEK_SET);
	while (!feof(phonebook)) {
		newnode = new Phone_node;
		fread(&record, sizeof(File_Record), 1, phonebook);
		if (feof(phonebook))
			break;
		strcpy(newnode->name, record.name);
		strcpy(newnode->phonenum, record.phonenum);
		newnode->left = newnode->right = NULL;
		add(newnode);
		delete newnode;
	}
	fclose(phonebook);
}*/


void Tree::close() {
	//write_tofile();
	emptytree(root);
}


/*void Tree::write_tofile() {
	if (!(phonebook = fopen(filename, "w+"))) {
		cerr << "Could not open file" << endl;
		return;
	}
	write_inorder(root);
	fclose(phonebook);
}*/


/*void Tree::write_inorder(Phone_node *p) {
	struct File_Record {
		char name[NAME_LENGTH];
		char phonenum[PHONENUM_LENGTH];
	};
	File_Record record;
	if (p) {
		write_inorder(p->left);
		strcpy(record.name, p->name);
		strcpy(record.phonenum, p->phonenum);
		fwrite(&record, sizeof(File_Record), 1, phonebook);
		write_inorder(p->right);
	}
}*/


void Tree::emptytree(Phone_node *p) {
	if (p) {
		if (p->left != NULL) {
			emptytree(p->left);
			p->left = NULL;
		}
		if (p->right != NULL) {
			emptytree(p->right);
			p->right = NULL;
		}
		delete p;
	}
}


int Tree::search(char*search_name) {
	Phone_node *traverse;
	LList *Ltraverse;
	traverse = root;
	int countfound = 0;
	bool all = false;
	if (search_name[0] == '*')
		all = true;
	if (all) {
		traverse_inorder(root);
		countfound++;
	}
	else { // singlerecord search
		while (traverse && !countfound) {
			int comparison = strcmp(search_name, traverse->name);
			if (comparison < 0)
				traverse = traverse->left;
			else if (comparison > 0)
				traverse = traverse->right;
			else {//ifnames are equal, record found
				cout << traverse->name << " "; // << traverse->phonenum << endl;
				Ltraverse = traverse->head;
				while (Ltraverse->next) {
					cout << Ltraverse->phonenum << " ";
					Ltraverse = Ltraverse->next;
				}
				cout << endl;
				countfound++;
			}
		}
	}
	return countfound;
}

void Tree::traverse_inorder(Phone_node *p) {
	if (p) {
		LList *Ltraverse;
		Ltraverse = p->head;
		traverse_inorder(p->left);
		cout << p->name << " "; // << p->phonenum << endl;

		while (Ltraverse) {
			cout << Ltraverse->phonenum << " ";
			Ltraverse = Ltraverse->next;
		}
		cout << endl;
		traverse_inorder(p->right);
	}
}


void Tree::add(Phone_node *toadd) {
	Phone_node *traverse, *newnode;
	LList *Ltraverse, *newList;

	traverse = root;
	int comparison;
	bool added = false;
	newnode = new Phone_node;
	newList = new LList;
	//newList = NULL;
	newnode->head = NULL;
	newnode->head = newList;
	newList->next = NULL;
	//newList = newnode->head;
	strcpy(newnode->name, toadd->name);
	//strcpy(newnode->phonenum, toadd->phonenum);
	//strcpy(newnode->head->phonenum, toadd->phonenum1);
	strcpy(newList->phonenum, toadd->phonenum1);
	//newList = newnode->head;
	newnode->left = NULL;
	newnode->right = NULL;
	if (root == NULL) {
		//first node being added
		root = newnode;
		nodecount++;
		return;
	}
	while ((traverse != NULL) && (!added)) {
		comparison = strcmp(newnode->name, traverse->name);
		if (comparison < 0) {
			if (traverse->left != NULL)
				traverse = traverse->left;
			else {
				traverse->left = newnode;
				added = true;
			}
		}
		else if (comparison > 0) {
			if (traverse->right != NULL)
				traverse = traverse->right;
			else {
				traverse->right = newnode;
				added = true;
			}
		}
		else {
			Ltraverse = traverse->head;
			//cout << "Data cannot repeat.\n";
			while (Ltraverse) {
				Ltraverse = Ltraverse->next;
			}
			strcpy(Ltraverse->phonenum, newList->phonenum);
			//Ltraverse->next = newList;
			added = true;
		}
	}
	if (added)nodecount++;
}


void Tree::remove(char *remove_name) {
	Phone_node *traverse, *parent;
	traverse = root;
	parent = NULL;
	bool found = false;
	char direction = 'k';
	while (traverse && !found) {
		int comparison = strcmp(remove_name, traverse->name);
		if (comparison < 0) {
			parent = traverse;
			direction = 'l';
			traverse = traverse->left;
		}
		else if (comparison > 0) {
			parent = traverse;
			direction = 'r';
			traverse = traverse->right;
		}
		else // found record to remove
			found = true;
	}
	if (found) {
		if (direction == 'l')
			remove(&parent->left);
		else if(direction == 'r')
			remove(&parent->right);
		else remove(&root);
	}
	else
		cout << "Could not find" << " record to remove.\n";
}


void Tree::remove(Phone_node **p) {
	Phone_node *r, *q;//used to find place for left subtree
	r = *p;
	if (r == NULL)// attempt to delete nonexistent node
		return;
	else if (r->right == NULL) {
		*p = r->left;//reattach left subtree
		delete r;
	}
	else if (r->left == NULL) {
		*p = r->right;//reattach right subtree
		delete r;
	}
	else {//neither subtree is empty
		for (q = r->right; q->left; q = q->left); //inorder successor
		q->left = r->left;//reattach left subtree
		*p = r->right;//reattach right subtree
		delete r;
	}
}

