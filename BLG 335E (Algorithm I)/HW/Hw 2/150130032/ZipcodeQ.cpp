/***************\
|	150130032	|
|	Baran Kaya	|
\***************/

//#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"

//#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include "header.h"
//#include <chrono>
#include <ctime>

using namespace std;

int N;

//------------------------------------------------CONSTRUECTERS------------------------------------------------

residence::residence() {
	population = 0;
	min_age = 0;
	max_age = 0;
	gender = " ";
	zipcode = 0;
	geo_id = " ";
}

AllResidences2010::AllResidences2010() {

}

//------------------------------------------------FUNCTIONS------------------------------------------------

/*
void AllResidences2010::Quicksort(vector<residence> &A, int p, int r) {
	if (p<r) {
		int q = Partition(A, p, r);
		Quicksort(A, p, q - 1);
		Quicksort(A, q + 1, r);
	}
}

int AllResidences2010::Partition(vector<residence> &A, int p, int r) {

	residence pivot = A[r];
	residence temp;
	int i = p - 1;

	for (int j = p; j < r - 1; j++) {
		//First checking population and if populations are the same then check geo_id. 
		//If geo_id's are the same their zipcodes are the same too, soo it will not sort them.
		if (A[j].get_population() < pivot.get_population() || (A[j].get_population() == pivot.get_population() && A[j].get_geo_id() <= pivot.get_geo_id())) {
			i++;
			//Exchange
			temp = A[j];
			A[j] = A[i];
			A[i] = temp;
		}
	}

	//Exchange
	temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;
	return i + 1;
}
*/

void AllResidences2010::Quicksort(int p, int r) {
	
	if (p<r) {
		int q = Partition(p, r);
		Quicksort(p, q - 1);
		Quicksort(q + 1, r);
	}
}

int AllResidences2010::Partition(int p, int r) {
	residence temp;
	/*
	//For calculating the worst case of quicksort -> it finds the population=1 residence and make it pivot
	for (int k = 0; k < N; k++) {
		if (residenceVec[k].get_population() == 1) {
			temp = residenceVec[k];
			residenceVec[k] = residenceVec[r];
			residenceVec[r] = temp;
		}
	}
	*/
	residence pivot = residenceVec[r];
	
	int i = p - 1;

	for (int j = p; j <= r - 1; j++) {
		//First checking population and if populations are the same then check geo_id. 
		//If geo_id's are the same their zipcodes are the same too, soo it will not sort them.
		if (residenceVec[j].get_population() < pivot.get_population() || (residenceVec[j].get_population() == pivot.get_population() && residenceVec[j].get_geo_id() <= pivot.get_geo_id())) {
			i++;
			//Exchange
			temp = residenceVec[j];
			residenceVec[j] = residenceVec[i];
			residenceVec[i] = temp;
		}
	}

	//Exchange
	temp = residenceVec[i + 1];
	residenceVec[i + 1] = residenceVec[r];
	residenceVec[r] = temp;
	return i + 1;
}

void AllResidences2010::push(residence R) {
	residenceVec.push_back(R);
}

//------------------------------------------------MAIN------------------------------------------------

int main(int argc, char *argv[])
{
	N = stoi(argv[1]);

	//File operations
	ifstream rfptr;
	rfptr.open("population_by_zip_2010.csv");
	ofstream wfptr;
	wfptr.open("out.csv");

	//AllResidences2010 object
	AllResidences2010* AR;
	AR = new AllResidences2010;
	residence R;
	string population, min_age, max_age, gender, zipcode, geo_id;
	string total;
	int count = N;

	std::cout << "Reading file..." << endl;

	//Reading the file
	if (!rfptr.is_open()) {
		cerr << "File could not be opened." << endl;
		exit(1);
	}
	else {
		//First line -> unnecessary
		getline(rfptr, total);
		while (!rfptr.eof() && count > 0) {
			count--;
			getline(rfptr, total);
			//cout << "total: " << total << endl;
			//Seperating the line
			istringstream lin;
			lin.str(total);
			getline(lin, population, ',');
			getline(lin, min_age, ',');
			getline(lin, max_age, ',');
			getline(lin, gender, ',');
			getline(lin, zipcode, ',');
			lin >> geo_id;
			//cout << population << " - " << min_age << " - " << max_age << " - " << gender << " - " << zipcode << " - " << geo_id << endl;
			R.set_population(stoi(population));
			//Cheking NULL for converting to int
			if(!min_age.empty())
				R.set_min_age(stoi(min_age));
			else
				R.set_min_age(0);
			//Cheking NULL for converting to int
			if(!max_age.empty())
				R.set_max_age(stoi(max_age));
			else
				R.set_max_age(0);
			R.set_gender(gender);
			R.set_zipcode(stoi(zipcode));
			R.set_geo_id(geo_id);
			AR->push(R);
		}
	}

	//Calling the quicksort
	cout << "Sorting..." << endl;
	//First i tried to call quicksort with vector but then i changed it.
	//AR->Quicksort(AR->getResidenceVec(), 0, N-1/*AR->getResidenceVec().size -1*/);	

	//I tried to use chrono but ssh does not compile it with chrono so i decided to use basic time() function	
	//auto start = chrono::high_resolution_clock::now();

	double start = time(NULL);

	AR->Quicksort(0, N - 1);

	double finish = time(NULL);
	double timeEl = finish - start;
	std::cout << "Time elapsed: " << timeEl << endl;

	//auto finish1 = chrono::high_resolution_clock::now();
	//std::cout << "Time elapsed: " << chrono::duration_cast<chrono::nanoseconds>(finish1 - start).count() << " nanoseconds." << endl;

	//Writing to file
	cout << "Writing to file..." << endl;
	residence yaz;
	for (int i = 0; i < N; i++) {
		yaz = AR->getResidenceVec()[i];
		wfptr << yaz.get_population() << "," << yaz.get_min_age() << "," << yaz.get_max_age() << "," << yaz.get_gender() << "," << yaz.get_zipcode() << "," << yaz.get_geo_id() << "," << endl;
	}

	//Closing file and deleting dynamic object
	delete AR;
	rfptr.close();
	wfptr.close();

	return 0;
}
