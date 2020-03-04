#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

float content[1000];

int main(){
	
	int n = 0, m = 0;
	cout << "Number of elements: ";
	cin >> n;
	
	string line;
	ifstream myfile ("array.txt");
	if (myfile.is_open()){
		while ( getline (myfile,line) && m++ < n){
			cout << line << '\n';
			for(int i=0; i < getsize(line); i++){
				line[i] 
			}
    	}
    myfile.close();
	}

	else cout << "Unable to open file"; 
	
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
