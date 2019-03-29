/************\
|	Baran	 |
|	Kaya	 |
| 150130032	 |
\************/
#include <iostream>
#include <queue>
#include <stack>
#include <chrono>
#include <ctime>

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

Node* States[14];

void Node::BFS() {
	auto start = std::chrono::system_clock::now();
	int numOfVisitedNodes = 0;
	int maxNodesInMemory = 0;
	int numOfMoveSteps = 0;

	bool Discovered[14];
	for (int i = 0; i < 14; i++)
		Discovered[i] = false;
	
	queue<Node*> LayersQ;
	int nodeNum = -1;
	int treeIndex = 0;

	//Push the first element aka caller of the BFS function
	LayersQ.push(this);
	Discovered[0] = true;

	Node* currentNode;
	while (!LayersQ.empty()) {
		numOfVisitedNodes++;

		//Get first element and then pop it
		currentNode = LayersQ.front();
		LayersQ.pop();

		//Check every edge
		for (int i = 0; i < 5; i++) {
			//Get the node number that has edge to currentNode
			nodeNum = currentNode->getEdge(i);
			if (nodeNum == -1)
				break;
			
			//First check the state's status and then check if the node is discovered.
			//steteOK ->Does rabbit eat carrots etc.
			if (States[nodeNum]->stateOK() && Discovered[nodeNum] == false) {
				Discovered[nodeNum] = true;
				//Put those 2 nodes into the tree as a pair
				BFSTree[treeIndex++] = make_pair(currentNode, States[nodeNum]);
				LayersQ.push(States[nodeNum]);
				//Move count & Max nodes in the queue
				numOfMoveSteps++;
				numOfVisitedNodes++;
				if (maxNodesInMemory < LayersQ.size())
					maxNodesInMemory = LayersQ.size();
			}
		}
	}
	auto finish = std::chrono::system_clock::now();
	cout << "Algorithm: BFS" << endl;
	cout << "Number of the visited nodes: " << numOfVisitedNodes << endl;
	cout << "Maximum number of nodes kept in the memory: " << maxNodesInMemory << endl;
	cout << "Running time: " << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() << " nanoseconds" << endl;
	cout << "Solution move count: " << numOfMoveSteps << endl;
	cout << "Farmer, Carrots, Rabbit, Fox || Farmer, Carrots, Rabbit, Fox " << endl;
	cout << !States[0]->Farmer << "\t" << !States[0]->Carrots << "\t" << !States[0]->Rabbit << "\t" << !States[0]->Fox <<
		" || " << States[0]->Farmer << "\t" << States[0]->Carrots << "\t" << States[0]->Rabbit << "\t" << States[0]->Fox << endl;
	for (int i = 0; i < 20; i++) {
		if (BFSTree[i].first != nullptr)
			cout << !BFSTree[i].second->Farmer << "\t" << !BFSTree[i].second->Carrots << "\t" << !BFSTree[i].second->Rabbit << "\t" << !BFSTree[i].second->Fox <<
			" || " << BFSTree[i].second->Farmer << "\t" << BFSTree[i].second->Carrots << "\t" << BFSTree[i].second->Rabbit << "\t" << BFSTree[i].second->Fox << endl;
		else
			break;
	}
}

void Node::DFS() {
	auto start = std::chrono::system_clock::now();
	int numOfVisitedNodes = 0;
	int maxNodesInMemory = 0;
	int numOfMoveSteps = 0;

	bool Explored[14];
	for (int i = 0; i < 14; i++)
		Explored[i] = false;

	stack<Node*> DFStack;
	int nodeNum = -1;
	int treeIndex = 0;

	//First caller States[0]
	DFStack.push(this);
	Explored[0] = true;

	Node* currentNode;
	while (!DFStack.empty()) {
		numOfVisitedNodes++;

		//Get first element and then pop it
		currentNode = DFStack.top();
		DFStack.pop();

		//Check every edge
		for (int i = 0; i < 5; i++) {
			//Get the node number that has edge to currentNode
			nodeNum = currentNode->getEdge(i);
			if (nodeNum == -1)
				break;

			//First check the state's status and then check if the node is explored.
			//steteOK ->Does rabbit eat carrots etc.
			if (States[nodeNum]->stateOK() && Explored[nodeNum] == false) {
				Explored[nodeNum] = true;
				//Put those 2 nodes into the tree as a pair
				DFSTree[treeIndex++] = make_pair(currentNode, States[nodeNum]);
				DFStack.push(States[nodeNum]);
				//Move count & Max nodes in the stack
				numOfMoveSteps++;
				numOfVisitedNodes;
				if (maxNodesInMemory < DFStack.size())
					maxNodesInMemory = DFStack.size();
			}
		}
	}
	auto finish = std::chrono::system_clock::now();
	cout << "Algorithm: DFS" << endl;
	cout << "Number of the visited nodes: " << numOfVisitedNodes << endl;
	cout << "Maximum number of nodes kept in the memory: " << maxNodesInMemory << endl;
	cout << "Solution move count: " << numOfMoveSteps << endl;
	cout << "Running time: " << chrono::duration_cast<chrono::nanoseconds>(finish - start).count() << " nanoseconds" << endl;
	cout << "Farmer, Carrots, Rabbit, Fox || Farmer, Carrots, Rabbit, Fox " << endl;
	cout << !States[0]->Farmer << "\t" << !States[0]->Carrots << "\t" << !States[0]->Rabbit << "\t" << !States[0]->Fox <<
		" || " << States[0]->Farmer << "\t" << States[0]->Carrots << "\t" << States[0]->Rabbit << "\t" << States[0]->Fox << endl;
	for (int i = 0; i < 20; i++) {
		if (DFSTree[i].first != nullptr)
			cout << !DFSTree[i].second->Farmer << "\t" << !DFSTree[i].second->Carrots << "\t" << !DFSTree[i].second->Rabbit << "\t" << !DFSTree[i].second->Fox <<
			" || " << DFSTree[i].second->Farmer << "\t" << DFSTree[i].second->Carrots << "\t" << DFSTree[i].second->Rabbit << "\t" << DFSTree[i].second->Fox << endl;
		else
			break;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Error, incorrect number of arguments!" << endl;
		return 0;
	}

	//Nodes aka States
	States[0] = new Node(0, 0, 0, 0, 0);	//Farmer, Carrots, Rabbit, Fox	| -
	States[1] = new Node(1, 1, 0, 0, 1);	//Rabbit, Fox					| Farmer, Carrots
	States[2] = new Node(1, 0, 1, 0, 0);	//Carrots, Fox					| Farmer, Rabbit
	States[3] = new Node(1, 0, 0, 1, 1);	//Carrots, Rabbit				| Farmer, Fox
	States[4] = new Node(0, 1, 0, 0, 0);	//Farmer, Rabbit, Fox			| Carrots
	States[5] = new Node(0, 0, 1, 0, 0);	//Farmer, Carrots, Fox			| Rabbit
	States[6] = new Node(0, 0, 0, 1, 0);	//Farmer, Carrots, Rabbit		| Fox
	States[7] = new Node(1, 1, 1, 0, 0);	//Fox							| Farmer, Carrots, Rabbit
	States[8] = new Node(1, 1, 0, 1, 0);	//Rabbit						| Farmer, Carrots, Fox
	States[9] = new Node(1, 0, 1, 1, 0);	//Carrots						| Farmer, Rabbit, Fox
	States[10] = new Node(0, 1, 1, 0, 1);	//Farmer, Fox					| Carrots, Rabbit
	States[11] = new Node(0, 1, 0, 1, 0);	//Farmer, Rabbit				| Carrots, Fox
	States[12] = new Node(0, 0, 1, 1, 1);	//Farmer, Carrots				| Rabbit, Fox
	States[13] = new Node(1, 1, 1, 1, 0);	//-								| Farmer, Carrots, Rabbit, Fox
	

	//Forward edges
	States[0]->carrots = States[1];
	States[0]->rabbit = States[2];
	States[0]->fox = States[3];
	States[0]->addEdge(1);
	States[0]->addEdge(2);
	States[0]->addEdge(3);

	States[1]->farmer = States[4];
	States[2]->farmer = States[5];
	States[3]->farmer = States[6];
	States[1]->addEdge(4);
	States[2]->addEdge(5);
	States[3]->addEdge(6);

	States[4]->rabbit = States[7];
	States[4]->fox = States[8];
	States[4]->addEdge(7);
	States[4]->addEdge(8);

	States[5]->carrots = States[7];
	States[5]->fox = States[9];
	States[5]->addEdge(7);
	States[5]->addEdge(9);

	States[6]->carrots = States[8];
	States[6]->rabbit = States[9];
	States[6]->addEdge(8);
	States[6]->addEdge(9);

	States[7]->farmer = States[10];
	States[8]->farmer = States[11];
	States[9]->farmer = States[12];
	States[7]->addEdge(10);
	States[8]->addEdge(11);
	States[9]->addEdge(12);

	States[10]->fox = States[13];
	States[11]->rabbit = States[13];
	States[12]->carrots = States[13];
	States[10]->addEdge(13);
	States[11]->addEdge(13);
	States[12]->addEdge(13);

	//Backward edges
	States[1]->carrots = States[0];
	States[2]->rabbit = States[0];
	States[3]->fox = States[0];
	States[1]->addEdge(0);
	States[1]->addEdge(0);
	States[1]->addEdge(0);

	States[4]->farmer = States[1];
	States[5]->farmer = States[2];
	States[6]->farmer = States[3];
	States[4]->addEdge(1);
	States[5]->addEdge(2);
	States[6]->addEdge(3);

	States[7]->rabbit = States[4];
	States[8]->fox = States[4];
	States[7]->addEdge(4);
	States[8]->addEdge(4);

	States[7]->carrots = States[5];
	States[9]->fox = States[5];
	States[7]->addEdge(5);
	States[9]->addEdge(5);

	States[8]->carrots = States[6];
	States[9]->rabbit = States[6];
	States[8]->addEdge(6);
	States[9]->addEdge(6);

	States[10]->farmer = States[7];
	States[11]->farmer = States[8];
	States[12]->farmer = States[9];
	States[10]->addEdge(7);
	States[11]->addEdge(8);
	States[12]->addEdge(9);

	States[13]->fox = States[10];
	States[13]->rabbit = States[11];
	States[13]->carrots = States[12];
	States[13]->addEdge(10);
	States[13]->addEdge(11);
	States[13]->addEdge(12);
	
	string searchFunc = argv[1];
	if (searchFunc == "bfs" || searchFunc == "Bfs" || searchFunc == "BFS")
		States[0]->BFS();
	else if (searchFunc == "dfs" || searchFunc == "Dfs" || searchFunc == "DFS")
		States[0]->DFS();
	else
		cerr << "Wrong argument, try one of these (BFS, DFS)." << endl;

	//Clear memory
	//delete[] States;
    return 0;
}


