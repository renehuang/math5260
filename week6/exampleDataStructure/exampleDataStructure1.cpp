#include "myStructures.h"
#include "functions.h"

#include <sys/time.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Simple example on data structures

// Also, data structure could be a member of another data structure

int main(int argc, char*argv[])
{
	
	cout << "argc=" << argc << endl;
	cout << "argv[0]=" << argv[0] << endl;

	string market       = argv[1];
	string symbolName   = argv[2];
	string exchangeName = argv[3];

	cout << "market:"       << market << endl;
	cout << "symbolName:"   << symbolName << endl;
	cout << "exchangeName:" << exchangeName << endl;

	marketAttributes myMarket;
	myMarket.market = market;
	myMarket.symbolName = symbolName;
	myMarket.exchangeName = exchangeName;

	// atoi, atol, atof, strtol
	int hour = atoi(argv[4]);
	int min  = atoi(argv[5]);

	cout << "hh:mm " << hour << ":" << min << endl;


	dataAttributes myData, *myDataPtr;
	myData.myMarket = myMarket;
	myData.date = 42788;
	myData.dateTimeLocal    = 42788+10.0/24.0+5.0/24.0/60.0;
	myData.dateTimeExchange = 42788+10.0/24.0+5.0/24.0/60.0+6.0/24.0;
	myData.hour = hour;
	myData.min = min;
	myData.price = 148.17;
	myData.volume = 985763;

	cout << "myData:    " << myData.myMarket.market << " " << myData.myMarket.symbolName << " " << myData.myMarket.exchangeName << endl;
	
	myDataPtr = &myData;

	cout << "myDataPtr: " << myDataPtr->myMarket.market << " " << myDataPtr->myMarket.symbolName << " " << myDataPtr->myMarket.exchangeName << endl;


	cout << "(*myDataPtr): " << (*myDataPtr).myMarket.market << " " << (*myDataPtr).myMarket.symbolName << " " << (*myDataPtr).myMarket.exchangeName << endl;
    
	myMarket.market = "SoybeanOil";
	myMarket.symbolName = "BO";
	myMarket.exchangeName = "CME";
	//myData.myMarket = myMarket;

	myFunc2(myData);
	cout << "(a) calling myFunc2 - By Value: " << myData.myMarket.market << " " << myData.myMarket.symbolName << " " << myData.myMarket.exchangeName << endl;
	
	(*myDataPtr).myMarket = myMarket;

	cout << "(b) " << (*myDataPtr).myMarket.market << " " << (*myDataPtr).myMarket.symbolName << " " << (*myDataPtr).myMarket.exchangeName << endl;

	myFunc1(*myDataPtr);
	cout << "(c) calling myFunc1 - By Reference: " << myDataPtr->myMarket.market << " " << myDataPtr->myMarket.symbolName << " " << myDataPtr->myMarket.exchangeName << endl;
	cout << "(d) calling myFunc1 - By Reference: " << (*myDataPtr).myMarket.market << " " << (*myDataPtr).myMarket.symbolName << " " << (*myDataPtr).myMarket.exchangeName << endl;
	return 0;

} // END OF FILE


