#include <iostream>
#include <ctime>
#include <fstream>
#include <stdlib.h>

#define NAME_LENGTH 30
#define PHONENUM_LENGTH 15


struct Phone_node {
	char name[NAME_LENGTH];
	char phonenum[PHONENUM_LENGTH];
	Phone_node *left;
	Phone_node *right;
};