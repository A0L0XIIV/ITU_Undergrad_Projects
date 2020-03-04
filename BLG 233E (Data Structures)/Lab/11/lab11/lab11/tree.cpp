#include "tree.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>

//using namespace std;

void Tree::create(){
	root = NULL;// create empty tree
	nodecount = 0;// initialize nodecount to 0
	read_fromfile();
}

void Tree::read_fromfile() {
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
}


void Tree::close() {
	write_tofile();
	emptytree(root);
}


void Tree::write_tofile() {
	if (!(phonebook = fopen(filename, "w+"))) {
		cerr << "Could not open file" << endl;
		return;
	}
	write_inorder(root);
	fclose(phonebook);
}


void Tree::write_inorder(Phone_node *p) {
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
}


void Tree::write_preorder(Phone_node *p) {
	struct File_Record {
		char name[NAME_LENGTH];
		char phonenum[PHONENUM_LENGTH];
	};
	File_Record record;
	if (p) {
		strcpy(record.name, p->name);
		strcpy(record.phonenum, p->phonenum);
		fwrite(&record, sizeof(File_Record), 1, phonebook);
		write_preorder(p->left);
		write_preorder(p->right);
	}
}


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
				cout << traverse->name << " " << traverse->phonenum << endl;
				countfound++;
			}
		}
	}
	return countfound;
}

void Tree::traverse_inorder(Phone_node *p) {
	if (p) {
		traverse_inorder(p->left);
		cout << p->name << " " << p->phonenum << endl;
		traverse_inorder(p->right);
	}
}


void Tree::add(Phone_node *toadd) {
	Phone_node *traverse, *newnode;
	traverse = root;
	int comparison;
	bool added = false;
	newnode = new Phone_node;
	strcpy(newnode->name, toadd->name);
	strcpy(newnode->phonenum, toadd->phonenum);
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
		else
			cout << "Data cannot repeat.\n";
	}
	if (added)nodecount++;
}


void Tree::remove(char *remove_name) {
	Phone_node *traverse, *parent;
	traverse = root;
	bool found = false;
	char direction = ‘k’;
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
		else(direction == ‘r')
			remove(&parent->right);
	else remove(&root);
	}
	else
		cout << “Could not find”
			<< “ record to remove.\n";
}
