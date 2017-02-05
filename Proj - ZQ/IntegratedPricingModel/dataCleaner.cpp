//
//  dataCleaner.cpp
//  IntegratedPricingModel
//
//  Created by Qi Zheng on 12/13/16.
//  Copyright © 2016 Qi ZHENG. All rights reserved.
//

#include <stdio.h>
#include "functions.h"

void cleanOutrights(vector<vector<string> >&data, vector<string> &time){
    int i = 0, j = 0;
    while(data[2][j] != "LAST_PRICE" && i < data[0].size()) ++j;
    while(data[i][j] != "LAST_PRICE" && i < 100) ++i;
    ++i;
    FILE *output;
    output = fopen("/Users/zhengq/Documents/Cpp/IntegratedPricingModel/output/cleanData/Outrights.dat", "w");
    while(data[i][j] != "" && i < data.size()){
        fprintf(output, "%s,%s\n", data[i][0].c_str(), data[i][j].c_str());
        time.push_back(data[i][0]);
        ++i;
    }
    fclose(output);
}

void cleanSpreadData(vector<vector<string> > &data, vector<string> &time, string fileName){
    int nRows = (int)data.size();
    if(nRows == 0) return;
    int nCols = (int)data[0].size();
    int nTimes = (int)time.size();
    int j1 = 0, j2 = 0, nSpreads = 0;
    vector<int> priceCol;
    vector<int> dateCol;
    while(j2 < nCols){
        while(data[2][j1] != "Date" && j1 < nCols) ++j1;
        while(data[2][j2] != "LAST_PRICE" && j2 < nCols) ++j2;
        if(data[2][j1] == "Date")
            dateCol.push_back(j1);
        if(data[2][j2] == "LAST_PRICE")
            priceCol.push_back(j2);
        ++j1;++j2;
        ++nSpreads;
    }
    --nSpreads;
    if(data[2][nCols-5] == "Date" || data[2][nCols-1] == "LAST_PRICE"){
        dateCol.push_back(nCols-5);
        priceCol.push_back(nCols-1);
        ++nSpreads;
    }
    for(j1 = 0; j1 < nSpreads; ++j1)
        if(data[3][dateCol[j1]] == "#NAME?") data[3][dateCol[j1]] = "11/1/16 9:00";
    FILE *output;
    fileName = "/Users/zhengq/Documents/Cpp/IntegratedPricingModel/output/cleanData/"+fileName+".dat";
    output = fopen(fileName.c_str(), "w");
    for(int j3 = 0; j3 < nTimes; ++j3){
        vector<string> spreadPrices(nSpreads);
        for(j1 = 0; j1 < nSpreads; ++j1){
            if(data[4][priceCol[j1]] != "" && data[3][dateCol[j1]] != "#N/A Invalid Security"){
                int j4 = 3;
                while(j4 < nRows && data[j4][priceCol[j1]] != "" && data[3][dateCol[j1]] != "#N/A Invalid Security" && data[j4][dateCol[j1]] < time[j3]) ++j4;
                if(j4 < nRows) spreadPrices[j1] = data[j4][priceCol[j1]];
            }
        }
        fprintf(output, "%s", time[j3].c_str());
        int j = 0;
        while(j < nSpreads) {fprintf(output, ",%s", spreadPrices[j].c_str());++j;}
        fprintf(output, "\n");
    }
    fclose(output);
    return;
}

void pushCorrectData(const vector<string> &dataOnePeriod, double &outright, vector<double> &oneMonthSpread, vector<double> &threeMonthSpread, vector<double> &sixMonthSpread, vector<double> &oneYearSpread, int nCols[]){
    int i = 0;++i;
    outright = atof(dataOnePeriod[i].c_str());
    ++i; ++i;
    int index = nCols[0] + nCols[1];
    while(dataOnePeriod[i] != "" && i < index){
        oneMonthSpread.push_back(atof(dataOnePeriod[i].c_str()));
        ++i;
    }
    while(dataOnePeriod[i] == "") ++i;
    index += nCols[2]; ++i;
    while(dataOnePeriod[i] != "" && i < index){
        threeMonthSpread.push_back(atof(dataOnePeriod[i].c_str()));
        ++i;
    }
    while(dataOnePeriod[i] == "") ++i;
    index += nCols[3]; ++i;
    while(dataOnePeriod[i] != "" && i < index){
        sixMonthSpread.push_back(atof(dataOnePeriod[i].c_str()));
        ++i;
    }
    while(dataOnePeriod[i] == "") ++i;
    index += nCols[4]; ++i;
    while(dataOnePeriod[i] != "" && i < index){
        oneYearSpread.push_back(atof(dataOnePeriod[i].c_str()));
        ++i;
    }
}


void showData(const double &outright, const vector<double> &oneMonthSpread, const vector<double> &threeMonthSpread, const vector<double> &sixMonthSpread, const vector<double> &oneYearSpread){
    cout << outright << endl << endl;
    for(int i = 0; i < oneMonthSpread.size(); ++i) cout << oneMonthSpread[i] << " ";
    cout << endl << endl;
    for(int i = 0; i < threeMonthSpread.size(); ++i) cout << threeMonthSpread[i] << " ";
    cout << endl << endl;
    for(int i = 0; i < sixMonthSpread.size(); ++i) cout << sixMonthSpread[i] << " ";
    cout << endl << endl;
    for(int i = 0; i < oneYearSpread.size(); ++i) cout << oneYearSpread[i] << " ";
    cout << endl << endl;
}




