//#ifndef TREE_H
//#define TREE_H
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include "node.h"


struct Tree {
	Phone_node *root;
	int nodecount;
	char *filename;
	FILE *phonebook;
	void create();
	void close();
	void emptytree(Phone_node *);
	void add(Phone_node *);
	void remove(char *);
	void remove(Phone_node **);
	void traverse_inorder(Phone_node *);
	int search(char *);
	void update(int recordnum);
	void read_fromfile();
	void write_inorder(Phone_node *);
	void write_tofile();
};

//#endif