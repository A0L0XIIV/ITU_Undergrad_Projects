//Baran Kaya - 150130032
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

//----------------------------------------------NODE CLASS-----------------------------------------------

class Node {
	friend class AdderRemover;
	friend class ARTraverser;
	int number;
public:
	Node(int i);
	Node *next;
	Node *previous;
};

//----------------------------------------------ADDER REMOVER CLASS-----------------------------------------------

class AdderRemover {
	friend class ARTraverser;
protected:
	Node* head;
	Node* tail;
	char* name;
	int nodeCount;
	ARTraverser* traverser;
public:
	//AdderRemover();
	virtual void add(int num)=0;
	virtual void remove()=0;
	void removeAll();
	void display() const;
	void setTraverser();
	void traverse() const;
	virtual ~AdderRemover();
};

//----------------------------------------------DERIVED ADDER REMOVER CLASSES-----------------------------------------------

class FAFR :public AdderRemover {
public:
	FAFR() { FAFR::name = "FAFR"; head = tail = NULL; };
	void add(int num);
	void remove();
	~FAFR();
};

class FALR :public AdderRemover {
public:
	FALR() { FALR::name = "FALR"; head = tail = NULL; };
	void add(int num);
	void remove();
	~FALR();
};

class LAFR :public AdderRemover {
public:
	LAFR() { LAFR::name = "LAFR"; head = tail = NULL; };
	void add(int num);
	void remove();
	~LAFR();
};

class LALR :public AdderRemover {
public:
	LALR() { LALR::name = "LALR"; head = tail = NULL; };
	void add(int num);
	void remove();
	~LALR();
};

//----------------------------------------------ARTRAVERSER CLASS-----------------------------------------------

class ARTraverser {
	friend class AdderRemover;
protected:
	Node* current;
public:
	//ARTraverser();
	bool hasNode();			//Why it should be virtual i do not understand. Because both derived class uses current pointer to check if list is empty or not.
	virtual Node* next()=0;
	~ARTraverser();
};

//----------------------------------------------DERIVED ARTRAVERSER CLASSES-----------------------------------------------

class ARTF :public ARTraverser {
public:
	ARTF(Node*);
	Node* next();
};

class ARTL :public ARTraverser {
public:
	ARTL(Node*);
	Node* next();
};

//----------------------------------------------ADDER REMOVER FUNCTIONS-----------------------------------------------

Node::Node(int i) {
	number = i;
}

/*AdderRemover::AdderRemover() {
	cout << "Adder Remover Constructer\n" << endl;
}*/

void AdderRemover::removeAll() {
	nodeCount = 0;
	Node* traverse;
	while (head) {
		traverse = head;
		head = head->next;
		delete traverse;
	}
}

void AdderRemover::display() const{
	Node* traverse;
	traverse = head;
	cout << name << "|" << "Node Count: " << nodeCount << endl << "------" << endl;
	if (head == NULL)
		cout << "There is no element to print." << endl << endl;
	else {
		while (traverse) {
			cout << traverse->number << endl;
			traverse = traverse->next;
		}
	}
}

void AdderRemover::setTraverser() {
	if (name == "FAFR" || name == "FALR") {
		traverser = new ARTF(head);
	}
	else { 
		traverser = new ARTL(tail); 
	}
}

void AdderRemover::traverse()const {
	Node* temp;
	temp = traverser->next();
	cout << name << "|" << "Node Count: " << nodeCount << endl << "------" << endl;
	if (traverser->hasNode()) {
		while (temp) {
			cout << temp->number << endl;
			temp = traverser->next();
		}
	}
	else 
		cout << "There is no element to print." << endl << endl;
}

AdderRemover::~AdderRemover() {
	//cout << "Adder Remover Destructer\n" << endl;
	delete traverser;
}

//----------------------------------------------ARTRAVERSER FUNCTIONS-----------------------------------------------

/*ARTraverser::ARTraverser(){
	current = NULL;
}*/

bool ARTraverser::hasNode() {
	if (current)
		return true;
	else
		return false;
}

ARTF::ARTF(Node* firstElement) {
	current = firstElement;
}

ARTL::ARTL(Node* lastElement) {
	current = lastElement;
}

Node* ARTF::next() {
	Node* temp;
	temp = current;
	if (current) //if it is not NULL
		current = current->next;
	return temp;
}

Node* ARTL::next() {
	Node* temp;
	temp = current;
	if(current)  //if it is not NULL
		current = current->previous;
	return temp;
}

ARTraverser::~ARTraverser() {
	delete current;
}

//---------------------------------------------FAFR FUNCTIONS----------------------------------------------

void FAFR::add(int num) {
	FAFR::nodeCount++;
	Node *newNode;
	newNode = new Node(num);
	newNode->next = NULL;
	newNode->previous = NULL;

	if (head == NULL) {
		head = newNode;
		tail = newNode;
		head->next = tail->next = head->previous = tail->previous = NULL;
	}
	else if (head->next == NULL) {
		head = newNode;
		head->next = tail;
		tail->previous = head;
	}
	else {
		newNode->next = head;
		head->previous = newNode;
		head = newNode;
	}
}

void FAFR::remove() {
	FAFR::nodeCount--;
	Node* delNode;
	if (head) {
		if (head->next) {
			delNode = head;
			head->next->previous = NULL;
			head = head->next;		
			delete delNode;
		}
		else {
			delete head;
			delete tail;					//??
		}
	}
}

FAFR::~FAFR() {
	Node* traverse;
	while (head) {
		traverse = head;
		head = head->next;
		delete traverse;
	}
}

//---------------------------------------------FALR FUNCTIONS----------------------------------------------

void FALR::add(int num) {
	FALR::nodeCount++;
	Node *newNode;
	newNode = new Node(num);
	newNode->next = NULL;
	newNode->previous = NULL;

	if (head == NULL) {
		head = newNode;
		tail = newNode;
		head->next = tail->next = head->previous = tail->previous = NULL;
	}
	else if (head->next == NULL) {
		head = newNode;
		head->next = tail;
		tail->previous = head;
	}
	else {
		newNode->next = head;
		head->previous = newNode;
		head = newNode;
	}
}

void FALR::remove() {
	FALR::nodeCount--;
	Node* delNode;
	if (head) {
		if (tail->previous) {
			delNode = tail;
			tail->previous->next = NULL;
			tail = tail->previous;
			delete delNode;
		}
		else {
			delete head;
			delete tail;					//??
		}
	}
}

FALR::~FALR() {
	Node* traverse;
	while (head) {
		traverse = head;
		head = head->next;
		delete traverse;
	}
}

//---------------------------------------------LAFR FUNCTIONS----------------------------------------------

void LAFR::add(int num) {
	LAFR::nodeCount++;
	Node *newNode;
	newNode = new Node(num);
	newNode->next = NULL;
	newNode->previous = NULL;

	if (head == NULL) {
		head = newNode;
		tail = newNode;
		head->next = tail->next = head->previous = tail->previous = NULL;
	}
	else if (tail->previous == NULL) {
		tail = newNode;
		tail->previous = head;
		head->next = tail;
	}
	else {
		newNode->previous = tail;
		tail->next = newNode;
		tail = newNode;
	}
}

void LAFR::remove() {
	LAFR::nodeCount--;
	Node* delNode;
	if (head) {
		if (head->next) {
			delNode = head;
			head->next->previous = NULL;
			head = head->next;
			delete delNode;
		}
		else {
			delete head;
			delete tail;					//??
		}
	}
}

LAFR::~LAFR() {
	Node* traverse;
	while (head) {
		traverse = head;
		head = head->next;
		delete traverse;
	}
}

//---------------------------------------------LALR FUNCTIONS----------------------------------------------

void LALR::add(int num) {
	LALR::nodeCount++;
	Node *newNode;
	newNode = new Node(num);
	newNode->next = NULL;
	newNode->previous = NULL;

	if (head == NULL) {
		head = newNode;
		tail = newNode;
		head->next = tail->next = head->previous = tail->previous = NULL;
	}
	else if (tail->previous == NULL) {
		tail = newNode;
		tail->previous = head;
		head->next = tail;
	}
	else {
		newNode->previous = tail;
		tail->next = newNode;
		tail = newNode;
	}
}

void LALR::remove() {
	LALR::nodeCount--;
	Node* delNode;
	if (head) {
		if (tail->previous) {
			delNode = tail;
			tail->previous->next = NULL;
			tail = tail->previous;
			delete delNode;
		}
		else {
			delete head;
			delete tail;					//??
		}
	}
}

LALR::~LALR() {
	Node* traverse;
	while (head) {
		traverse = head;
		head = head->next;
		delete traverse;
	}
}