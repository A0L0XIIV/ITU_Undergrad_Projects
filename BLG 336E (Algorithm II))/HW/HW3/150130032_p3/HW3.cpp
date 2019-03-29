/************\
* 150130032  *
* Baran Kaya *
\************/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <utility>	//std::pair
#include <random>	//Karger algo
#include <time.h>	//random

using namespace std;

//Road class -> Start point, End point
class Road {
public:
	Road() { Start = -1; End = -1; }
	Road(int S, int E) { Start = S; End = E; }
	int Start;
	int End;
	Road reverseRoad() { return Road(End, Start); }
	void setRoadEnd(int newEndPoint) { End = newEndPoint; }
	bool sameRoad(Road other) { return (this->Start == other.Start && this->End == other.End); }
	bool reverseRoad(Road other) { return (this->Start == other.End && this->End == other.Start); }
};

//Shop class -> Shop ID, road vector for edges
class Shop {
	int shopId;
	vector<Road> roads;
public:
	Shop() { shopId = 0; }
	Shop(int ID, Road Roads) {
		shopId = ID;
		roads.push_back(Roads);
	}
	int getId() { return shopId; }
	vector<Road> getRoads() { return roads; }
	void addRoad(Road R) { roads.push_back(R); }
};

//Min Cut algorithm -> Karger algorithm and mergeNodes functions' prototypes
void mergeNodes(vector<Shop>& Shops, vector<Road>& Roads, int index);
int kargerMinCut(vector<Shop> Shops, vector<Road> Roads);


int main(int argc, char *argv[])
{
	//Random initialize
	srand(time(NULL));

	//File operations
	if (argc != 2) {
		cerr << "Error, incorrect number of arguments!" << endl;
		return 0;
	}

	char* filename;
	filename = argv[1];
	ifstream filePtr;
	filePtr.open(filename);

	string line, leftPart, rightPart;
	vector<pair<int,int>> edgeVector;

	//Reading the file
	if (!filePtr.is_open()) {
		cerr << "File could not be opened." << endl;
		exit(1);
	}
	else {
		//Get numberOfShops and numberOfRoads from first line
		getline(filePtr, line);

		//Read other lines
		while (!filePtr.eof()) {

			getline(filePtr, line);
			//cout << "line: " << line << endl;
			//Seperating the line
			istringstream lin;
			lin.str(line);
			getline(lin, leftPart, ' ');
			lin >> rightPart;
			//cout << i << " - " << leftPart << " - " << rightPart << endl;
			pair<int, int>edge(stoi(leftPart), stoi(rightPart));
			edgeVector.push_back(edge);
		}
	}

	//Create shops and roads objects
	vector<Shop> ShopsVec;
	vector<Road> RoadsVec;

	bool FoundLeft = false;
	bool FoundRight = false;

	//Traverse inside the vector that holds edges (shop pairs)
	for (int i = 0; i < edgeVector.size(); i++) {
		FoundLeft = false;
		FoundRight = false;
		//Check if the left one or the right one is already in the ShopsVec
		for (int j = 0; j < ShopsVec.size(); j++) {
			if (ShopsVec[j].getId() == edgeVector[i].first)
				FoundLeft = true;
			else if (ShopsVec[j].getId() == edgeVector[i].second)
				FoundRight = true;
		}

		//Create road with shop pair
		Road r(edgeVector[i].first, edgeVector[i].second);
		RoadsVec.push_back(r);

		//Not found the left shop id in the ShopsVec -> Add it to the vector
		if (!FoundLeft) 
			ShopsVec.push_back( Shop(edgeVector[i].first, r) );
		//If shop is already created then just add (connect) new road to it
		else {
			for (int j = 0; j < ShopsVec.size(); j++) {
				if (ShopsVec[j].getId() == edgeVector[i].first) {
					ShopsVec[j].addRoad(r);
					break;
				}
			}
		}
		//Same as above -> for right shop id
		if (!FoundRight) 
			ShopsVec.push_back( Shop(edgeVector[i].second, r.reverseRoad() ) );
		else {
			for (int k = 0; k < ShopsVec.size(); k++) {
				if (ShopsVec[k].getId() == edgeVector[i].second) {
					ShopsVec[k].addRoad( r.reverseRoad() );
					break;
				}
			}
		}	
	}

	//Apply algorithm for min cut (Karger)
	cout << "Min number: " << kargerMinCut(ShopsVec, RoadsVec) << endl;

    return 0;
}

//Merging two nodes (Call vectors by reference)
void mergeNodes(vector<Shop>& Shops, vector<Road>& Roads, int index) {

	int firstShopId = Roads[index].Start;
	int secondShopId = Roads[index].End;
	int firstShopPlace;
	int secondShopPlace;

	//Delete selected (index) road (edge) from road vector
	Roads.erase(Roads.begin() + index);

	//Find the place of first and second shops in the shops vector by their id
	for (firstShopPlace = 0; firstShopPlace < Shops.size(); firstShopPlace++) {
		if (Shops[firstShopPlace].getId() == firstShopId) 
			break;
	}
	for (secondShopPlace = 0; secondShopPlace < Shops.size(); secondShopPlace++) {
		if (Shops[secondShopPlace].getId() == secondShopId)
			break;
	}

	//Adjunsting shopVec
	//Handle roads that have connected to the firstShop (deleted one)
	//Change shops edges that were connected to the first shop -> replace firstShop with secondShop
	vector<Road> firstShopRodes = Shops[firstShopPlace].getRoads(); //Get edges of deleted shop
	vector<Road> changeShopRoad; //Will use for shops that have road to firstShop
	for (int i = 0; i < firstShopRodes.size(); i++) {
		//Find shops in shopsVec that are connected to the firstShop
		for (int j = 0; j < Shops.size(); j++) {
			if (Shops[j].getId() == firstShopRodes[i].End) {//Check firstShop's roadVec's second column to find them
				changeShopRoad = Shops[j].getRoads();
				//Find found shop's road to firstShop in its roadVec and change them to the secondShop
				for (int k = 0; k < changeShopRoad.size(); k++)
					if (changeShopRoad[k].End == firstShopId) {//Check found shops roadVec's second column for firstShop (There can only be one road to firstShop)
						changeShopRoad[k].setRoadEnd(secondShopId);
						break;
					}
				break;
			}
		}
	}

	//Adjusting RoadsVec
	//Change firstShops in road vector to secondShop
	for (int i = 0; i < Roads.size(); i++) {
		if (Roads[i].Start == firstShopId) //Roads -> start point is firstShop
			Roads[i].Start = secondShopId;
		else if(Roads[i].End == firstShopId) //Roads -> end point is firstShop
			Roads[i].End = secondShopId;
	}

	//Delete loop roads
	for (int i = 0; i < Roads.size(); i++) {
		if (Roads[i].Start == Roads[i].End)
			Roads.erase(Roads.begin() + i);
	}

	//Delete firstShop from the shop vector
	Shops.erase(Shops.begin() + firstShopPlace);
}

int kargerMinCut(vector<Shop> Shops, vector<Road> Roads) {

	vector<Shop> graph = Shops;
	vector<Road> edges = Roads;

	unsigned int numOfNodes = graph.size();
	unsigned int numOfEdges = edges.size();

	//Until there are only two shops (nodes), merge randomly selected two shops
	while (numOfNodes > 2)
	{
		// Pick a random road from roadVec
		numOfEdges = edges.size(); //Refresh with every loop
		int randomIndex = rand() % numOfEdges;
		Road randomEdge = edges[randomIndex];

		// Merge selected road's two shops and handle with other connected roads to these two shops
		numOfNodes--;
		numOfEdges--;
		mergeNodes(graph, edges, randomIndex);
		
	}

	// Return the number of roads between the last 2 shops -> min cut
	return numOfEdges;
}

