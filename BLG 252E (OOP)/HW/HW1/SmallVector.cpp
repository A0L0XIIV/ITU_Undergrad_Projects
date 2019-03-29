//Baran Kaya - 150130032

#include<iostream>
#include"SmallVector.h"


void printSmallVector(const char* const message, const SmallVector& in_vector) {
	std::cout << message << ": ";
	for (int i = 0; i < in_vector.getSize(); i++)
	{
		std::cout << in_vector[i] << " ";
	}
	std::cout << std::endl;
}

//--------------------------------------------------CONSTRUCTORS--------------------------------------------------

SmallVector::SmallVector() {	//Default constructor
	capacity = 32;
	size = 0;
	overloaded_size = 0;
}


SmallVector::SmallVector(int array[], int user_size) {	//Constructor with array and size
	if (user_size > 32) {//Dynamic - Overloaded
		capacity = user_size;
		size = user_size;
		overloaded_size = user_size - 32;
		Dynamic_Buffer = new int[overloaded_size]; //New memory allocation
		for (int i = 0; i < size; i++) {
			if (i < 32)
				Static_Buffer[i] = array[i];
			else
				Dynamic_Buffer[i - 32] = array[i];
		}

	}
	else {//Static (size <= 32)
		capacity = 32;
		size = user_size;
		for (int i = 0; i < user_size; i++) {
			Static_Buffer[i] = array[i];
		}
	}
}


SmallVector::SmallVector(int user_size, int *array) {	//Constructor with array and size for operator
	if (user_size > 32) {//Dynamic - Overloaded
		capacity = user_size;
		size = user_size;
		overloaded_size = user_size - 32;
		Dynamic_Buffer = new int[overloaded_size]; //New memory allocation
		for (int i = 0; i < size; i++) {
			if (i < 32)
				Static_Buffer[i] = array[i];
			else
				Dynamic_Buffer[i - 32] = array[i];
		}
	}
	else {//Static (size <= 32)
		capacity = 32;
		size = user_size;
		for (int i = 0; i < user_size; i++) {
			Static_Buffer[i] = array[i];
		}
	}
	delete[] array;//Against memory leak
}


SmallVector::SmallVector(const SmallVector &copy) {	//Copy constructor
	capacity = copy.capacity;
	size = copy.size;
	overloaded_size = copy.overloaded_size;

	if (size > 32) {//Dynamic - Overloaded
		Dynamic_Buffer = new int[overloaded_size];	//New memory allocations
		for (int i = 0; i < size; i++) {
			if (i < 32)
				Static_Buffer[i] = copy.Static_Buffer[i];
			else
				Dynamic_Buffer[i - 32] = copy.Dynamic_Buffer[i - 32];
		}
	}
	else {//Static (size <= 32)
		for (int i = 0; i < size; i++) {
			Static_Buffer[i] = copy.Static_Buffer[i];
		}
	}
}

//---------------------------------------------------FUNCTIONS---------------------------------------------------

int SmallVector::getSize() const{
	return size;
}

int SmallVector::getCapacity() const{
	return capacity;
}


void SmallVector::push_back(int number) {
	if (size > 32)	//If static buffer is overloaded
		push_back(number, size);
	else {
		size += 1;
		Static_Buffer[size - 1] = number;
	}
}


void SmallVector::push_back(int number, int ar_size) {
	size += 1;
	capacity += 1;
	int *temp_ptr;
	temp_ptr = new int[overloaded_size + 1];	//New memory allocation

	for (int i = 0; i < overloaded_size; i++) {	//Copying the old one to the new one
		temp_ptr[i] = Dynamic_Buffer[i];
	}
	delete[] Dynamic_Buffer;

	overloaded_size += 1;
	Dynamic_Buffer = new int[overloaded_size];
	for (int i = 0; i < overloaded_size; i++) {	//Copying temp_ptr to dynamic_buffer
		 Dynamic_Buffer[i] = temp_ptr[i];
	}
	delete[] temp_ptr;
	//Dynamic_Buffer = temp_ptr;
}


int SmallVector::pop_back(int last_element) {
	int temp = 0;

	if (size > 32) {//Dynamic - Overloaded
		size -= 1;
		capacity -= 1;
		temp = Dynamic_Buffer[overloaded_size];	//Copy the last element to temp
		overloaded_size -= 1;					//Decrease the overloaded_size

		if (overloaded_size != 0) {//If dynamic_buffer has more than one elements
			int *temp_ptr;
			temp_ptr = new int[overloaded_size];		//New memory allocation

			for (int i = 0; i < overloaded_size; i++) {	//Copying the old one to the new one
				temp_ptr[i] = Dynamic_Buffer[i];
			}
			delete[] Dynamic_Buffer;

			Dynamic_Buffer = new int[overloaded_size];
			for (int i = 0; i < overloaded_size; i++) {	//Copying temp_ptr to dynamic_buffer
				Dynamic_Buffer[i] = temp_ptr[i];
			}
			delete[] temp_ptr;
			//Dynamic_Buffer = temp_ptr;
		}
		else	//If dynamic_buffer has only one element
			delete[] Dynamic_Buffer;
	}

	else {//Static (size <= 32)
		temp = Static_Buffer[size - 1];
		//Static_Buffer[size - 1] = NULL;
		size -= 1;
	}
	return temp;
}


SmallVector& SmallVector::reverse() {
	int *temp;
	temp = new int[size];
	int i = 0, j = (size - 1);

	if (size > 32) {//Dynamic - Overloaded
		for (i = 0; i < size; i++) {
			if(i < 32)
				temp[i] = Static_Buffer[i];
			else
				temp[i] = Dynamic_Buffer[i - 32];
		}
		//Temp has all elements, now time to insert them buffers to reverse order
		for (i = 0; i < size; i++, j--) {
			if(i < 32)
				Static_Buffer[i] = temp[j];
			else
				Dynamic_Buffer[i - 32] = temp[j];
		}
	}

	else {//Static (size <= 32)
		for (int i = 0; i < (size/2); i++) {
			temp[i] = Static_Buffer[i];
			Static_Buffer[i] = Static_Buffer[(size - 1) - i];
			Static_Buffer[(size - 1) - i] = temp[i];
		}
	}
	delete[] temp;
	return *this;
}

//---------------------------------------------------OPERATORS---------------------------------------------------

SmallVector SmallVector::operator+(const SmallVector& op2){
	int *new_array;
	int new_size = (this->size + op2.size);
	new_array = new int[new_size];
	int i = 0, j = 0;

	if (new_size > 32) {//Dynamic - Overloaded

		for (i = 0; i < this->size; i++) {//Adding first (this) array's elements to the new_array

			if (i < 32)//this->Static_Buffer
				new_array[i] = this->Static_Buffer[i];

			else//this->Dynamic_Buffer
				new_array[i] = this->Dynamic_Buffer[i - 32];
		}
		for (j = 0; j < op2.size; j++, i++) {//Adding second (op2) array's elements to the new_array

			if (j < 32)//op2->Static_Buffer
				new_array[i] = op2.Static_Buffer[j];

			else//op2->Dynamic_Buffer
				new_array[i] = op2.Dynamic_Buffer[j - 32];
		}
	}

	else {//Static (size <= 32)
		for (i = 0; i < new_size; i++) {

			if (i < this->size)//First one copying to  the new_array
				new_array[i] = this->Static_Buffer[i];

			else				//Second one copying to the new_array
				new_array[i] = op2.Static_Buffer[i - this->size];
		}
	}
	//delete[] new_array;
	return SmallVector(new_size, new_array);
}


SmallVector SmallVector::operator*(int number){
	int *new_array;
	int new_size = this->size * number;
	new_array = new int[new_size];
	int i = 0, j = 0;

	if (new_size > 32) {//Dynamic - Overloaded
		for (i = 0; i < new_size; i++) {
			if (i < 32)
				new_array[i] = Static_Buffer[i % size];
			else
				new_array[i] = Dynamic_Buffer[(i - 32) % size];
		}
	}

	else {//Static (size <= 32)
		for (i = 0; i < new_size; i++) {
			new_array[i] = Static_Buffer[i % size];
		}
	}

	//delete[] new_array;
	return SmallVector(new_size, new_array);
}


SmallVector& SmallVector::operator=(const SmallVector &obj) {
	if (size != obj.size) {
		size = obj.size;
		capacity = obj.capacity;
		if (size > 32) {
			delete[] this->Dynamic_Buffer;
			this->Dynamic_Buffer = new int[size - 32];
		}
	}
	for (int i = 0; i < obj.size; i++) {
		if (i < 32)
			this->Static_Buffer[i] = obj.Static_Buffer[i];
		else
			this->Dynamic_Buffer[i - 32] = obj.Dynamic_Buffer[i - 32];
	}
	return *this;
}


const int& SmallVector::operator[](int index) const{

	if (index >= 0) {
		if (index < size) {//Positive & In the range
			if (index < 32)
				return Static_Buffer[index];
			else
				return Dynamic_Buffer[index - 32];
		}
		else {//Positive & Out of range
			if (index < 32)
				return Static_Buffer[size - 1];
			else
				return Dynamic_Buffer[size - 33];
		}
	}
	else {
		index += size;
		if (index < size) {//Negative & In the range
			if (index < 32)
				return Static_Buffer[index];
			else
				return Dynamic_Buffer[index - 32];
		}

		else {//Negative & Our of range
			if (index < 32)
				return Static_Buffer[size - 1];
			else
				return Dynamic_Buffer[size - 33];
		}
	}
}


int& SmallVector::operator[](int index) {
	if (index >= 0) {
		if (index < size) {//Positive & In the range
			if (index < 32)
				return Static_Buffer[index];
			else
				return Dynamic_Buffer[index - 32];
		}
		else{//Positive & Out of range
			if (index < 32)
				return Static_Buffer[size - 1];
			else
				return Dynamic_Buffer[size - 33];
		}
	}
	else {
		index += size;
		if (index < size) {//Negative & In the range
			if (index < 32)
				return Static_Buffer[index];
			else
				return Dynamic_Buffer[index - 32];
		}

		else{//Negative & Our of range
			if (index < 32)
				return Static_Buffer[size - 1];
			else
				return Dynamic_Buffer[size - 33];
		}
	}
}

//--------------------------------------------------DESTRUCTOR--------------------------------------------------

SmallVector::~SmallVector() {	//Destructor
	if( size > 32 )	
		delete [] Dynamic_Buffer;
}

//-----------------------------------------------------MAIN-----------------------------------------------------

int main() {
	int temp[35];
	for (int i = 0; i < 35; i++) {
		temp[i] = i;
	}
	SmallVector test(temp, 10); // Creating SmallVector with 10 elements
	SmallVector test2(temp, 35); // Creating SmallVector with 35 elements
								 // print test in reverse order
	printSmallVector("Printing test in reverse", test.reverse());
	SmallVector test3; // Empty SmallVector
	test3 = test2 + test; // Concatenate two SmallVectors
	printSmallVector("Printing test3", test3);
	SmallVector test4(test); // Copy SmallVector
	SmallVector test5(temp, 2);
	test5 = test5 * 5; // Replicate elements
	test5.push_back(12); // Add 12 at the end
	test5[0] = 4; // Modify the first element of test5
	std::cout << "Printing test5 in reverse: ";
	for (int i = 1; i < test5.getSize() + 1; i++)
	{
		// Testing negative numbers as indices
		std::cout << test5[-i] << " ";
	}
	return 0;
}