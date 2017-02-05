//
//  main.cpp
//  IntegratedPricingModel
//
//  Created by Qi Zheng on 12/13/16.
//  Copyright © 2016 Qi ZHENG. All rights reserved.
//

#include "allincludes.h"
#include "functions.h"

#define nDataSet 5

int main(int argc, const char * argv[]) {
    string inputFileName[nDataSet] = {"Outrights", "1M spread", "3M spread", "6M spread", "1Y spread"};
    string absoluteInputFileName[nDataSet];
    vector<vector<string> > data[nDataSet];
    for (int i = 0; i < nDataSet; ++i){
        absoluteInputFileName[i] = "/Users/zhengq/Documents/Cpp/IntegratedPricingModel/input/"+inputFileName[i]+".csv";
        int nRows = 0, nCols = 0;
        getTotalRowAndCol(absoluteInputFileName[i], nCols, nRows);
        data[i] = vector<vector<string> >(nRows, vector<string>(nCols, ""));
        getInfo(absoluteInputFileName[i], data[i]);
    }
    
    int nTimes = (int)data[0].size();
    vector<string> time;
    time.reserve(nTimes);
    cleanOutrights(data[0], time);
    vector<vector<string> >().swap(data[0]);
    for(int i = 1; i < nDataSet; ++i){
        cleanSpreadData(data[i], time, inputFileName[i]);
        vector<vector<string> >().swap(data[i]);
    }
    vector<string> ().swap(time);
    
    int nCols[nDataSet];
    string newInputFileName[nDataSet];
    vector<string> dataOnePeriod;
    string currentTime;
    for (int i = 0; i < nDataSet; ++i){
        newInputFileName[i] = "/Users/zhengq/Documents/Cpp/IntegratedPricingModel/output/cleanData/"+inputFileName[i]+".dat";
        getTotalCol(newInputFileName[i], nCols[i]);
        getOneLineData(newInputFileName[i], currentTime, dataOnePeriod, 0, nCols[i]);
    }
    int nPeriods = nCols[1]; //nPeriods = 48
    vector<vector<string> > path(nPeriods);
    int nSpread[nDataSet-1];
    {
        double outright;
        vector<double> oneMonthSpread, threeMonthSpread, sixMonthSpread, oneYearSpread;
        pushCorrectData(dataOnePeriod, outright, oneMonthSpread, threeMonthSpread, sixMonthSpread, oneYearSpread, nCols);
        nSpread[0] = (int)oneMonthSpread.size();
        nSpread[1] = (int)threeMonthSpread.size();
        nSpread[2] = (int)sixMonthSpread.size();
        nSpread[3] = (int)oneYearSpread.size();
    }
    calculate(path, nSpread, nPeriods);
    writePath(path);
    nTimes = 4;
    for(int t = 0; t < nTimes; ++t){
        vector<string> ().swap(dataOnePeriod);
        for(int i = 0; i < nDataSet; ++i) getOneLineData(newInputFileName[i], currentTime, dataOnePeriod, t, nCols[i]);
        double outright;
        vector<double> oneMonthSpread, threeMonthSpread, sixMonthSpread, oneYearSpread;
        pushCorrectData(dataOnePeriod, outright, oneMonthSpread, threeMonthSpread, sixMonthSpread, oneYearSpread, nCols);
        vector<vector<double> > price(nPeriods);
        calculatePrice(price, path, outright, oneMonthSpread, threeMonthSpread, sixMonthSpread, oneYearSpread);
        writePrice(price, currentTime);
        writeCertainPrice(price, currentTime,(int)price.size());
        vector<vector<pair<double,int>> > frequency(nPeriods);
        getFrequency(frequency, price);
        writeFrequency(frequency, currentTime);
    }
    return 0;
}
