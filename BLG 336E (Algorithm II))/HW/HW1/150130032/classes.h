#pragma once
#include <iostream>

using namespace std;

class Node {
public:
	//Constructer
	Node() {
		Farmer = false;
		Carrots = false;
		Rabbit = false;
		Fox = false;
		canEat = false;
		edges[0] = edges[1] = edges[2] = edges[3] = edges[4] = -1;
		for (int i = 0; i < 20; i++) {
			BFSTree[i] = make_pair(nullptr, nullptr);
			DFSTree[i] = make_pair(nullptr, nullptr);
		}
	};
	Node(bool F, bool C, bool R, bool X, bool cE) {
		Farmer = F;
		Carrots = C;
		Rabbit = R;
		Fox = X;
		canEat = cE;
		edges[0] = edges[1] = edges[2] = edges[3] = edges[4] = -1;
		for (int i = 0; i < 20; i++) {
			BFSTree[i] = make_pair(nullptr, nullptr);
			DFSTree[i] = make_pair(nullptr, nullptr);
		}
	};

	//Edges
	Node* farmer = NULL;	//->Farmer crossing
	Node* carrots = NULL;	//->Farmer, Carrots crossing
	Node* rabbit = NULL;	//->Farmer, Rabbit crossing
	Node* fox = NULL;		//->Farmer, Fox crossing* /

	//Trees -> Stores 2 nodes that have edge between them
	pair <Node*, Node*> BFSTree[20];
	pair <Node*, Node*> DFSTree[20];

	//Functions
	void BFS();
	void DFS();
	//Return the side of the item
	char whichSide(bool Item) { 
		if (Item) return 'R'; else return 'L';
	}
	//If state can be occur. They cannot each other.
	bool stateOK() {
		return (!canEat);
	}
	//Add edge to the node
	void addEdge(int otherNode) {
		for (int i = 0; i < 5; i++) {
			if (edges[i] == -1) {
				edges[i] = otherNode;
				break;
			}
		}
	}
	//Get edges for calling node
	int getEdge(int index) {
		return edges[index];
	}

private:
	//False -> Left side, True -> Right side
	bool Farmer;
	bool Carrots;
	bool Rabbit;
	bool Fox;
	//Does state OK, can one eat the other?
	bool canEat;
	int edges[5];
};