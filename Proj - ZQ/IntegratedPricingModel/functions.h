//
//  functions.h
//  IntegratedPricingModel
//
//  Created by Qi Zheng on 12/13/16.
//  Copyright © 2016 Qi ZHENG. All rights reserved.
//

#ifndef functions_h
#define functions_h


#endif /* functions_h */

#include "allincludes.h"

void getTotalRowAndCol(string &inputFileName, int & nCols, int & nRows);
void getInfo(string &inputFileName, vector<vector<string> >& data);
void getTotalCol(string &inputFileName, int &nCols);
void getOneLineData(string &inputFileName, string &currentTime, vector<string> &data, int row, int nCols);

void cleanOutrights(vector<vector<string> >&data, vector<string> &time);
void cleanSpreadData(vector<vector<string> > &data, vector<string> &time, string fileName);
void pushCorrectData(const vector<string> &dataOnePeriod, double &outright, vector<double> &oneMonthSpread, vector<double> &threeMonthSpread, vector<double> &sixMonthSpread, vector<double> &oneYearSpread, int nCols[]);
void showData(const double &outright, const vector<double> &oneMonthSpread, const vector<double> &threeMonthSpread, const vector<double> &sixMonthSpread, const vector<double> &oneYearSpread);

void calculate(vector<vector<string> > &path, const int nSpread[], int nPeriods);
void calculateHelper(vector<vector<string> > &path, string curr, int currPeriod, const int nSpread[], int nPeriods);
void calculatePrice(vector<vector<double> > &price, const vector<vector<string> > &path, const double &outright, const vector<double> &oneMonthSpread, const vector<double> &threeMonthSpread, const vector<double> &sixMonthSpread, const vector<double> &oneYearSpread);
double calculatePriceHelper(const string &path, const double &outright, const vector<double> &oneMonthSpread, const vector<double> &threeMonthSpread, const vector<double> &sixMonthSpread, const vector<double> &oneYearSpread);
void getFrequency(vector<vector<pair<double, int>> > &frequency, const vector<vector<double> > &price);

void writePrice(const vector<vector<double> > &price, string &t);
void writeFrequency(const vector<vector<pair<double,int>> > &frequency, string &t);
void writePath(const vector<vector<string> > &path);
void writeCertainPrice(const vector<vector<double> > &price, string &t, int n);
void betterName(string &t);

template <class T>
string convertToString(T value){
    std::stringstream ss;
    ss << value;
    return ss.str();
}

