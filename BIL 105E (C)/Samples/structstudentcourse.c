#include <stdio.h>

//definition of variables for storing student and courses
struct student{
	char name[20];
	int enrol_year;
	float grade1;
	float grade2;
	struct student *sonraki;
};
struct course{
	char course_name[10];
	float avg_grade;
	struct student *ilk;
};

//function that returns the list of student with greater total grade than average 
void greater(struct course a){
	do{
		if((a.ilk->grade1)/3+2.(a.ilk->grade2)/3 > a.grade);
			printf("%s", a.ilk->list);
		a.ilk=a.ilk->sonraki;
	}while(a.ilk->sonraki!=NULL);
}
