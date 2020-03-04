#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

void quicksort(int beginning, int end);
void printArray(float* array, int size);

struct location
{
	float x;
	float y;
};

float content[1000];

int main(int argc, char* argv[])
{
	FILE *ptr = fopen ( "array.txt" , "r" );
	double d = strtod( argv[1], NULL);
	float X = strtof ( argv[2], NULL);
	float Y = strtof ( argv[3], NULL);
	location *array = new location[(int)d];
	float *floatarray = new float[(int)d];
	unsigned int i = 0;
	char b,c;
	for ( i ; i < d ; i++ )
	{
		fscanf( ptr, "%f%c%f%c", &array[i].x, &b, &array[i].y, &c);
		floatarray[i] = sqrt( pow( X-array[i].x, 2 ) + pow( Y-array[i].y, 2 ) );
		content[i] = floatarray[i];
	}
	int n = 0;
	cout << "Enter the test number: ";
	cin >> n;
	quicksort(0, n);
	printArray(floatarray, n);
	delete [] array;
	delete [] floatarray;
	fclose(ptr);
}

void quicksort(int beginning, int end)
{
	if(beginning == end)return;
	float temp;
	unsigned int p, j, r;
	p = beginning;
	int i = p;
	r = beginning + rand() % (end - beginning + 1);
	temp = content[r];
	content[r] = content[end];
	content[end] = temp;
	r = end;
	for (j=p ; j < end ; j++ )
	{
		if ( content[j] <= content[r] )
		{
			temp = content[j];
			content[j] = content[i];
			content[i] = temp;
			i++;
		}
	}
	temp = content[r];
	content[r] = content[i];
	content[i] = temp;
	if(i > p)quicksort(p, i - 1);
	if(i+1 < r)quicksort(i+1, r);
}

void printArray(float* array, int size)
{
	for (unsigned int i = 0 ; i < size ; i++ )
	{
		printf("%f\n", array[i]);
	}
}

