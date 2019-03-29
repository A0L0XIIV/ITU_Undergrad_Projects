#include <iostream>
#include <cstdlib>

class SmallVector{

	int size;
	int capacity;
	int overloaded_size;
	int Static_Buffer[32];
	int *Dynamic_Buffer;

	public:

	SmallVector();													//Default constructor
	SmallVector(int array[], int user_size = 0);					//Constructor with array and size
	SmallVector(int user_size, int *array);							//Constructor with array and size for operators
	SmallVector(const SmallVector&);								//Copy constructor
	int getSize() const;
	int getCapacity() const;
	void push_back(int);
	void push_back(int, int);
	int pop_back(int);
	SmallVector& reverse();
	SmallVector operator+(const SmallVector&);
	SmallVector operator*(int);
	SmallVector& operator=(const SmallVector&);
	const int& operator[](int) const;
	int& operator[](int);

	~SmallVector();													//Destructor
};