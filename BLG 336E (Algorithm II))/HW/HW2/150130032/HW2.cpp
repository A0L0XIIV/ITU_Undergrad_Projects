/************\
* 150130032  *
* Baran Kaya *
\************/

//#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <algorithm> 
#include <vector>
#include <math.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <climits>
#include <ctime>
//#include <chrono>

using namespace std;

//Global number of calculations
unsigned int numOfCal = 0;

//--------------------------Point class--------------------------

class Point {
public:
	//Constructers
	Point() {
		x = y = z = 0;
	}
	Point(int X, int Y, int Z) {
		x = X;
		y = Y;
		z = Z;
	}
	//Get functions
	int getX() { return x; }
	int getY() { return y; }
	int getZ() { return z; }
private:
	int x;
	int y;
	int z;
};

//--------------------------Euclidian distance function--------------------------

float euclidianDis(vector<Point> ArrayOfPairs) {
	int p1 = pow(ArrayOfPairs[0].getX() - ArrayOfPairs[1].getX(), 2);
	int p2 = pow(ArrayOfPairs[0].getY() - ArrayOfPairs[1].getY(), 2);
	int p3 = pow(ArrayOfPairs[0].getZ() - ArrayOfPairs[1].getZ(), 2);
	
	numOfCal++;//Incerease it

	return sqrt(p1 + p2 + p3);
}
/*
float euclidianDis(Point A, Point B) {
	int p1 = pow(A.getX() - B.getX(), 2);
	int p2 = pow(A.getY() - B.getY(), 2);
	int p3 = pow(A.getZ() - B.getZ(), 2);

	numOfCal++;//Incerease it

	return sqrt(p1 + p2 + p3);
}
*/
//--------------------------Sort compare functions--------------------------

bool compareX(Point a, Point b) {
	return (a.getX() < b.getX());
}
bool compareY(Point a, Point b) {
	return (a.getY() < b.getY());
}
bool compareZ(Point a, Point b) {
	return (a.getZ() < b.getZ());
}

//--------------------------Recursive closest pair function--------------------------

vector<Point> closestPairRec(vector<Point> Px, vector<Point> Py) {

	unsigned int Psize = Px.size();
	int mid = Psize / 2;
	Point midPoint = Px[mid];//x* in slides

	//|P| <= 3 -> Brute force
	if (Px.size() <= 3) {
		switch (Px.size()) {
			case 2: {
				vector<Point> pair;
				pair.push_back(Px[0]);
				pair.push_back(Px[1]);
				return pair;
				break; 
			}
			case 3: {
				vector<Point> pairOfBruteForce1;
				pairOfBruteForce1.push_back(Px[0]);
				pairOfBruteForce1.push_back(Px[1]);
				float dist0_1 = euclidianDis(pairOfBruteForce1);
				vector<Point> pairOfBruteForce2;
				pairOfBruteForce2.push_back(Px[0]);
				pairOfBruteForce2.push_back(Px[2]);
				float dist0_2 = euclidianDis(pairOfBruteForce2);
				vector<Point> pairOfBruteForce3;
				pairOfBruteForce3.push_back(Px[1]);
				pairOfBruteForce3.push_back(Px[2]);
				float dist1_2 = euclidianDis(pairOfBruteForce3);
				if (dist0_1 < dist0_2 && dist0_1 < dist1_2)
					return pairOfBruteForce1;
				else if (dist0_2 < dist0_1 && dist0_2 < dist1_2)
					return pairOfBruteForce2;
				else
					return pairOfBruteForce3;
				break; 
			}
			default: {
				//vector<Point> empty;
				//return empty;
				cerr << "Error: Returned vector size is 1 or 0" << endl;
				exit;
				break; 
			}
		}
		
		/*
		unsigned int N = Px.size();
		float min = 9999.99;
		float dist;
		Point* pairOfBruteForce;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				pairOfBruteForce[0] = Px[i];
				pairOfBruteForce[1] = Px[j];
				dist = euclidianDis(pairOfBruteForce);
				if (dist < min)
					min = dist;
			}
		}
		*/
	}

	//Construct Q and R vectors for x,y and z
	vector<Point>::const_iterator leftFirst = Px.begin();
	vector<Point>::const_iterator leftLast = Px.begin() + mid;
	vector<Point>::const_iterator rightFirst = Px.begin() + mid;
	vector<Point>::const_iterator rightLast = Px.end();
	vector<Point> Qx(leftFirst, leftLast);
	vector<Point> Rx(rightFirst, rightLast);

	/*
	leftFirst = Py.begin();
	leftLast = Py.begin() + (mid - 1);
	rightFirst = Py.begin() + mid;
	rightLast = Py.end();
	vector<Point> Qy(leftFirst, leftLast);
	vector<Point> Ry(rightFirst, rightLast);

	leftFirst = Pz.begin();
	leftLast = Pz.begin() + (mid - 1);
	rightFirst = Pz.begin() + mid;
	rightLast = Pz.end();
	vector<Point> Qz(leftFirst, leftLast);
	vector<Point> Rz(rightFirst, rightLast);
	*/

	vector<Point> ResultOfQ, ResultOfR;
	ResultOfQ = closestPairRec(Qx, Py);
	ResultOfR = closestPairRec(Rx, Py);

	//Find delta -> min distance inside Q and R
	float delta = min(euclidianDis(ResultOfQ), euclidianDis(ResultOfR));

	//Construct S vector (between mid-delta and min+delta)
	vector<Point> S;
	int L = midPoint.getX();

	for (int i = 0; i < Psize; i++) {
		if (abs(Px[i].getX() - L) < delta) {
			S.push_back(Px[i]);
		}
	}

	//Sort L vector by y coor. -> PY KULLANARAK SIRALAMA YAPILACAK!!!!!!!!!!!
	sort(S.begin(), S.end(), compareY);

	//Find the min distance in L (Comparing only next 15 points)
	unsigned int Ssize = S.size();
	vector<Point> minOfS;

	for (int i = 0; i < Ssize; i++) {
		for (int j = 1; j < Ssize && j <= 15; j++) {
			//Check if i+j is inside the S vector
			if (i + j < Ssize) {
				vector<Point> pointPair;
				pointPair.push_back(S[i]);
				pointPair.push_back(S[i + j]);
				float distOfPoints = euclidianDis(pointPair);
				if (distOfPoints < delta)
					minOfS = pointPair;
			}
		}
	}

	if (!minOfS.empty() && euclidianDis(minOfS) < delta)
		return minOfS;
	else if (euclidianDis(ResultOfQ) < euclidianDis(ResultOfR))
		return ResultOfQ;
	else
		return ResultOfR;
}

//--------------------------Closest pair function--------------------------

vector<Point> closestPair(vector<Point> pointVector) {
	//Sorting point array by x,y and z
	vector<Point> Px = pointVector;
	vector<Point> Py = pointVector;
	//vector<Point> Pz = pointVector;

	sort(Px.begin(), Px.end(), compareX);
	sort(Py.begin(), Py.end(), compareY);
	//sort(Pz.begin(), Pz.end(), compareZ);

	return closestPairRec(Px, Py);
}

//---------------------------------------MAIN---------------------------------------

int main(int argc, char *argv[])
{
	//File operations
	if (argc != 2) {
		cerr << "Error, incorrect number of arguments!" << endl;
		return 0;
	}

	char* filename;
	filename = argv[1];
	ifstream filePtr;
	filePtr.open(filename);

	string line, x_coor, y_coor, z_coor;
	vector<Point> pointVector;
	int sizeOfData = 0;

	//Reading the file
	if (!filePtr.is_open()) {
		cerr << "File could not be opened." << endl;
		exit(1);
	}
	else {
		//Get size of the data
		getline(filePtr, line);
		cout << line << endl;
		sizeOfData = stoi(line);

		//Read lines
		//while (!filePtr.eof()) {
		for (int i = 0; i < sizeOfData; i++) {

			getline(filePtr, line);
			//cout << "line: " << line << endl;
			//Seperating the line
			istringstream lin;
			lin.str(line);
			getline(lin, x_coor, ' ');
			getline(lin, y_coor, ' ');
			lin >> z_coor;
			//cout << i << " - " << x_coor << " - " << y_coor << " - " << z_coor << endl;
			pointVector.push_back(Point(stoi(x_coor), stoi(y_coor), stoi(z_coor)));
		}
	}

	
	//I tried to use chrono but ssh does not compile it with chrono so i decided to use basic time() function	
	//auto start = chrono::high_resolution_clock::now();	
	double start = time(NULL);

	//Çift nokta dönecek
	vector<Point> minDistPoints = closestPair(pointVector);

	//auto finish1 = chrono::high_resolution_clock::now();
	//std::cout << "Time elapsed: " << chrono::duration_cast<chrono::nanoseconds>(finish1 - start).count() << " nanoseconds." << endl;
	double finish = time(NULL);
	double timeEl = finish - start;
	std::cout << "Time elapsed: " << timeEl << endl;
	std::cout << "The distance: " << euclidianDis(minDistPoints) << endl;
	std::cout << "Number of total distance calculations: " << numOfCal << endl;

	filePtr.close();
    return 0;
}


