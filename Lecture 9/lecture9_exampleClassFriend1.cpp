
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Class example 
// Friend class

class Square; // forward declaration of Square needed by Rectangle

class Rectangle {

	int width;
	int height;

public:
	
	// Default Constructor
	Rectangle (){
		width =4; 
		height=10;
	}
	
	// Constructor
	Rectangle (int x1, int y1){
		width=x1; 
		height=y1;
	}
	
	int area (){
		return (width * height);
	}

	void convert (Square a);

	friend Rectangle duplicate (const Rectangle&);
};

//void Rectangle::convert (Square a) {
//	width = a.side;
//	height = a.side;
//}

Rectangle duplicate (const Rectangle& param)
{
	Rectangle res;
	res.width = param.width*2;
	res.height = param.height*2;
	return res;
}

class Square {

	friend class Rectangle;

private:

	int side;

public:

	Square (int a) : side(a) {}
};

// has to be here 
void Rectangle::convert (Square a) {
	width = a.side;
	height = a.side;
}


int main() 
{

	Rectangle foo;
	cout << "before -- rectangle foo.area():" << foo.area() << endl;
	Rectangle bar (2,3);
	foo = duplicate (bar);
	cout << "after -- rectangle foo.area():" << foo.area() << endl;

	Rectangle rect;
	cout << "rectangle rect.area():" << rect.area() << endl;
	
	Square sqr (4);
	
	rect.convert(sqr);
	cout << "rectangle converted to square area:" << rect.area() << endl;

	return 0;
}
