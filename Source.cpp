#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

class Car
{
public:
	bool search(const string) const;
	void isMoved();
	void setlicense(string);
	void setarriveOrdepart(string);
	string getlicense() const;
	string getarriveOrdepart() const;
	int getTimesMoved() const;
	Car();

private:
	string arriveOrdepart;
	string licenseplate;
	int numberOfTimesMoved;
}; 

template <class Type>
class stackADT
{
public:
	virtual void initializeStack() = 0;

	virtual bool isEmptyStack() const = 0;

	virtual bool isFullStack() const = 0;

	virtual void push(const Type& newItem) = 0;

	virtual Type top() const = 0;

	virtual void pop() = 0;

};
template <class Type>
class stackType : public stackADT<Type>
{
public:
	void initializeStack();
	//Function to initialize the stack to an empty state.
	bool isEmptyStack() const;
	//Function to determine whether the stack is empty.
	bool isFullStack() const;
	//Function to determine whether the stack is full.
	void push(const Type& newItem);
	//Function to add newItem to the stack.
	Type top() const;
	//Function to return the top element of the stack.
	void pop();
	//Function to remove the top element of the stack.
	string get(int) const;
	//Function to return the stack element located at the index
	stackType(int stackSize = 10);
	//Constructor
	//Create an array of the size stackSize to hold
	//the stack elements.
	~stackType();
	//Destructor
private:
	int maxStackSize; //variable to store the maximum stack size
	int stackTop; //variable to point to the top of the stack
	Type* list; //pointer to the array that holds the
	//stack elements
};


template <class Type>
stackType<Type>::stackType(int stackSize)
{
	if (stackSize <= 0)
	{
		cout << "Size of the array to hold the stack must "
			<< "be positive." << endl;
		cout << "Creating an array of size 10." << endl;
		maxStackSize = 10;
	}
	else
		maxStackSize = stackSize; //set the stack size to
		//the value specified by
		//the parameter stackSize
	stackTop = 0; //set stackTop to 0
	list = new Type[maxStackSize]; //create the array to
	//hold the stack elements
}//end constructor


template <class Type>
stackType<Type>::~stackType() //destructor
{
	delete[] list; //deallocate the memory occupied
	//by the array
}//


template <class Type>
void stackType<Type>::initializeStack()
{
	stackTop = 0;
}//end initializeStack

template <class Type>
bool stackType<Type>::isEmptyStack() const
{
	return(stackTop == 0);
}//end isEmptyStack

template <class Type>
bool stackType<Type>::isFullStack() const
{
	return (stackTop == maxStackSize);
} //end isFullStack

template <class Type>
void stackType<Type>::push(const Type& newItem)
{
	if (!isFullStack())
	{
		list[stackTop] = newItem; //add newItem to the
		//top of the stack
		stackTop++; //increment stackTop
	}
	else
		cout << "Cannot add to a full stack." << endl;
}//end push

template <class Type>
Type stackType<Type>::top() const
{
	assert(stackTop != 0); //if stack is empty,
	//terminate the program
	return list[stackTop - 1]; //return the element of the
	//stack indicated by
	//stackTop - 1
}//end top


template <class Type>
void stackType<Type>::pop()
{
	if (!isEmptyStack())
		stackTop--; //decrement stackTop
	else
		cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
string stackType<Type>::get(int i) const {
	if (i < 10)
		if (stackTop == 1 && i > stackTop)
			return list[1];
		else if (stackTop == 0)
			return list[0];
		else
			return list[i];

	else
		return "error"; //lanes only hold ten cars, so there is an error if index is greater than 9
}
Car::Car() {
	numberOfTimesMoved = 0;
}

void Car::isMoved() {
	numberOfTimesMoved++;
}

void Car::setarriveOrdepart(string AorD) {
	arriveOrdepart = AorD;
}

string Car::getarriveOrdepart() const {
	return arriveOrdepart;
}

void Car::setlicense(string license) {
	licenseplate = license;
}

string Car::getlicense() const {
	return licenseplate;
}

int Car::getTimesMoved() const {
	return numberOfTimesMoved;
}

bool Car::search(const string license)const {
	if (license == licenseplate)
		return true;
	return false;
}

int main() {

	int counter = 9, x = 0, y = 0, z = 0;
	stackType<string> lane1(10);
	stackType<string> lane2(10);
	stackType<string> street(10);
	ifstream inFile;
	bool found = false, foundInLane1 = false, foundInLane2 = false;
	string restofline, licensehelper, arriveordepart, tempcar, tempcar2;

	lane1.initializeStack();
	lane2.initializeStack();
	street.initializeStack();

	inFile.open("Cars.txt");
	if (!inFile.is_open()) {
		cout << "File not found." << endl;
		exit(1);
	}

	Car cars[17];

	// The following while loop will read in cars from the file
	while (x < 17) {

		inFile >> arriveordepart;
		inFile >> licensehelper;
		getline(inFile, restofline);
		cars[x].setarriveOrdepart(arriveordepart);
		cars[x].setlicense(licensehelper);


		// the license plates of arriving (A) cars are "pushed" into the lanes.
		if (cars[x].getarriveOrdepart() == "A") {
			if (!lane1.isFullStack()) {
				lane1.push(cars[x].getlicense());
				cars[x].isMoved();
				cout << cars[x].getlicense() << " has arrived at Lane 1.\n";
				y++;
			}
			else if (!lane2.isFullStack()) {
				lane2.push(cars[x].getlicense());
				cars[x].isMoved();
				cout << cars[x].getlicense() << " has arrived at Lane 2.\n";
				z++;
			}
			else if (lane1.isFullStack() && lane2.isFullStack())
				cout << "Sorry, both lanes are full. We have no more room.\n";
		}


		// the license plates of departing (D) cars are "popped" from the lanes.
		else if (cars[x].getarriveOrdepart() == "D") {
			//check if the departing car is found in Lane 1
			for (int i = 0; i < y && foundInLane1 == false; i++) {
				tempcar2 = lane1.get(i);
				found = cars[x].search(tempcar2);
				if (found == true) {
					foundInLane1 = true;
					foundInLane2 = false; //car can't be in two places at once.
				}
			}
			//check if the departing car is found in Lane 2
			for (int i = 0; i < z && foundInLane2 == false; i++) {
				tempcar2 = lane2.get(i);
				found = cars[x].search(tempcar2);
				if (found == true) {
					foundInLane2 = true;
					foundInLane1 = false; //car can't be in two places at once.
				}
			}

			// moving a car from lane 1 to lane 2 in order to make room for car departing from lane 1
			if (foundInLane1 == true) {
				while ((cars[x].getlicense() != lane1.get(counter))) {
					if (!lane2.isFullStack()) {
						if (cars[x].getlicense() != lane1.top())
							lane2.push(lane1.top());
						tempcar = lane1.top();
						//keep track of the number of times the cars are moved
						for (int i = 0; i < x; i++) {
							if (cars[i].getlicense() == tempcar)
								cars[i].isMoved();
						}
						lane1.pop();
					}
					else if (lane2.isFullStack()) {
						if (cars[x].getlicense() != lane1.top())
							street.push(lane1.top());
						tempcar = lane1.top();
						//keep track of the number of times the cars are moved
						for (int i = 0; i < x; i++) {
							if (cars[i].getlicense() == tempcar)
								cars[i].isMoved();
						}
						lane1.pop();
					}
					if (counter != 0)
						counter--;
				}

				//The car departs.
				found = true;
				foundInLane1 = false;
				counter = 9;
				lane1.pop();
				cout << cars[x].getlicense() << " has departed from Lane1.\n";
				cout << cars[x].getlicense() << " has moved out of the way " << cars[x].getTimesMoved() << " times.\n";
			}

			// moving a car from lane 2 to lane 1 in order to make room for car departing from lane 2
			if (foundInLane2 == true) {
				while ((cars[x].getlicense() != lane2.get(counter))) {
					if (!lane1.isFullStack()) {
						if (cars[x].getlicense() != lane2.top())
							lane1.push(lane2.top());
						tempcar = lane2.top();
						//keep track of the number of times the cars are moved
						for (int i = 0; i < x; i++) {
							if (cars[i].getlicense() == tempcar)
								cars[i].isMoved();
						}
						lane2.pop();
					}
					else if (lane1.isFullStack()) {
						if (cars[x].getlicense() != lane2.top())
							street.push(lane2.top());
						tempcar = lane2.top();
						//keep track of the number of times the cars are moved
						for (int i = 0; i < x; i++) {
							if (cars[i].getlicense() == tempcar)
								cars[i].isMoved();
						}
						lane2.pop();
					}
					if (counter != 0)
						counter--;
				}
				//The car departs
				found = true;
				foundInLane2 = false;
				counter = 9;
				lane2.pop();
				cout << cars[x].getlicense() << " has departed from Lane 2.\n";
				cout << cars[x].getlicense() << " has moved out of the way " << cars[x].getTimesMoved() << " times.\n";
			}

			if (found == false) {
				cout << "Sorry, that car is not in our garage. Contact the police in case";
				cout << " it was stolen." << endl;
			}
			found = false;
			street.isEmptyStack();

			//move any cars in the street back into any available lanes
			while ((!lane1.isFullStack() && !street.isEmptyStack()) || (!lane2.isFullStack() && !street.isEmptyStack())) {
				if (!lane1.isFullStack() && (!street.isEmptyStack())) {
					lane1.push(street.top());
					street.pop();
					street.isEmptyStack();
				}
				else if (!lane2.isFullStack() && (!street.isEmptyStack())) {
					lane2.push(street.top());
					street.pop();
					street.isEmptyStack();
				}
			}
		}//end of code segment for departing (D) cars
		x++;
	} //end of the while loop
	inFile.close(); //closes the file

	if (street.isEmptyStack())
		cout << endl << "At this time, there are no cars in the street." << endl << endl;

	//printing out cars in lanes 1, 2 and the street
	cout << "Lane 1: exit <-- ";
	while (!lane1.isEmptyStack()) //print Lane1. remember Last In First Out.
	{
		cout << lane1.top() << " ";
		lane1.pop();
	}
	cout << endl;

	cout << "Lane 2: exit <-- ";
	while (!lane2.isEmptyStack()) //print Lane2. remember Last In First Out.
	{
		cout << lane2.top() << " ";
		lane2.pop();
	}
	cout << endl;

	if (!street.isEmptyStack()) //don't print anything if the street is empty.
		cout << "The cars in the street: ";
	while (!street.isEmptyStack()) //print Street. remember Last In First Out.
	{
		cout << street.top() << " ";
		street.pop();
	}
	cout << endl;

	system("pause");
	return 0;
}



