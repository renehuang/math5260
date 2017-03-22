
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Simple example on Inheritance (1)
// with Base & Derived Classes Constructors
// Implicit Call of the Base Class Constructor


// Base class
class Polygon {

public:

	int width, height;

	Polygon (int a, int b){ 
		cout << "Base Class Constructor called" << endl;
		width=a; 
		height=b;
	}
};

// Derived classes
class Rectangle: protected Polygon {

public:

		Rectangle (int a, int b) : Polygon(a, b){
		cout << "Rectangle Class Constructor called" << endl;
		width=a; 
		height=b;
		
	}
	int area (){ 
		return width * height; 
	}
};

class Triangle: protected Polygon {
 
public:
		Triangle (int a, int b) : Polygon(a, b){
		cout << "Triangle Class Constructor called" << endl;
		width=a; 
		height=b;
		
	}
	int area (){
		return (width* height/2); 
	}
};
  

int main() 
{

	Rectangle rect(4,5);
	Triangle trgl(4,5);

	cout << "rectangle area:" << rect.area() << endl;
	cout << "triangle  area:" << trgl.area() << endl;

	return 0;
}
