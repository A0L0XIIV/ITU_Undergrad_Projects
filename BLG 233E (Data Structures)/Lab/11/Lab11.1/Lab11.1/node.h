#include <iostream>
#include <ctime>
#include <fstream>
#include <stdlib.h>

#define NAME_LENGTH 30
#define PHONENUM_LENGTH 15

struct LList {
	char phonenum[PHONENUM_LENGTH];
	LList *next;
};

struct Phone_node {
	char name[NAME_LENGTH];
	char phonenum1[PHONENUM_LENGTH];
	LList *head;
	Phone_node *left;
	Phone_node *right;
};
