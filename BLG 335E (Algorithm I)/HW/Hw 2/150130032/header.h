/***************\
|	150130032	|
|	Baran Kaya	|
\***************/

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class residence{
    friend class AllResidences2010;
private:
    int population;
    int min_age;
    int max_age;
    string gender;
    int zipcode;
    string geo_id;    
public:  
    residence();
    void set_population(int p){
         population = p;
    }
    int get_population(){
        return population;
    }
    void set_min_age(int min){
         min_age = min;
    }
    int get_min_age(){
        return min_age;    
    }
    void set_max_age(int max){
         max_age = max;
    }
    int get_max_age(){
        return max_age;    
    }
    void set_gender(string g){
         gender = g;
    }
    string get_gender(){
           return gender;       
    }
    void set_zipcode(int z){
         zipcode = z;
    }
    int get_zipcode(){
        return zipcode;    
    }
    void set_geo_id(string geo){
         geo_id = geo;
    }
    string get_geo_id(){
           return geo_id;       
    }
};

class AllResidences2010{
    vector<residence> residenceVec;
public:
    AllResidences2010();
    void push(residence R);
    //void Quicksort(vector<residence> &A, int p, int r);
    //int Partition(vector<residence> &A, int p, int r);
	void Quicksort(int p, int r);
	int Partition(int p, int r);
    vector<residence> getResidenceVec() {
		return residenceVec;
	}
};
