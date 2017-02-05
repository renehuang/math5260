//
//  readFiles.cpp
//  IntegratedPricingModel
//
//  Created by Qi Zheng on 12/13/16.
//  Copyright © 2016 Qi ZHENG. All rights reserved.
//

#include <stdio.h>
#include "functions.h"

void getTotalRowAndCol(string &inputFileName, int &nCols, int &nRows){
    ifstream inputFile;
    inputFile.open(inputFileName.c_str());
    if (!inputFile.is_open()){
        cout << "could not open the input file.";
        return;
    }
    string headerLine;
    getline(inputFile, headerLine);
    stringstream lineToProcess(headerLine);
    string cellData;
    nCols = 0;
    while (getline(lineToProcess, cellData, ','))
        ++nCols;
    string fieldLine;
    nRows = 0;
    while(getline(inputFile, fieldLine))
        ++nRows;
    inputFile.close();
}

void getInfo(string &inputFileName, vector<vector<string> > &data){
    ifstream inputFile;
    string lineData;
    inputFile.open(inputFileName.c_str());
    if (!inputFile.is_open()) {
        cout << "could not open the input file." << endl;
        return;
    }
    size_t nRows = data.size();
    if(nRows == 0) return;
    size_t nCols = data[0].size();
    for (int i = 0; i < nRows; ++i){
        getline(inputFile, lineData);
        std::stringstream lineToProcess(lineData);
        for (int j = 0; j < nCols; j++){
            getline(lineToProcess, data[i][j], ',');
        }
    }
    inputFile.close();
}

void getTotalCol(string &inputFileName, int &nCols){
    ifstream inputFile;
    inputFile.open(inputFileName.c_str());
    if (!inputFile.is_open()){
        cout << "could not open the input file.";
        return;
    }
    string headerLine;
    getline(inputFile, headerLine);
    stringstream lineToProcess(headerLine);
    string cellData;
    nCols = 0;
    while (getline(lineToProcess, cellData, ',')){
        nCols++;
    }
    inputFile.close();
}

void getOneLineData(string &inputFileName, string &currentTime, vector<string> &data, int row, int nCols){
    ifstream inputFile;
    string lineData;
    inputFile.open(inputFileName.c_str());
    if (!inputFile.is_open()) {
        cout << "could not open the input file." << endl;
        return;
    }
    while(--row >= 0) getline(inputFile, lineData);
    getline(inputFile, lineData);
    std::stringstream lineToProcess(lineData);
    for (int i = 0; i < nCols; ++i){
        string dataString;
        getline(lineToProcess, dataString, ',');
        if(i == 0) currentTime = dataString;
        data.push_back(dataString);
    }
}





