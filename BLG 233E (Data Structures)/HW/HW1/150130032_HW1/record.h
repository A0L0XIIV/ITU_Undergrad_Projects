/* @Author
* Student Name: Baran Kaya
* Student ID : 150130032
* Date: 17.10.2015
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct patient_record {

char name[40];
char doctorName[40]; 
char diagnosis[40];
int patientNumber; 
int polyclinicNumber;
char branchName[20];

int recordNumber;

void print_records();
void searchByName(char *);
void searchByNumber(int);
void insert_record();
void remove_record();
void list();

};