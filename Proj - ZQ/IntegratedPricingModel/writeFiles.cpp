//
//  writeFiles.cpp
//  IntegratedPricingModel
//
//  Created by Qi Zheng on 12/14/16.
//  Copyright © 2016 Qi ZHENG. All rights reserved.
//

#include <stdio.h>
#include "functions.h"

void writePrice(const vector<vector<double> > &price, string &t){
    FILE *output;
    betterName(t);
    string fileName = "/Users/zhengq/Documents/Cpp/IntegratedPricingModel/output/price/Prices At " + t + ".dat";
    output = fopen(fileName.c_str(), "w");
    
    int n = (int)price.size();
    if(n == 0) return;
    for(int i = 0; i < n; ++i){
        fprintf(output, "When current period is %d\n", i+1);
        int m = (int)price[i].size();
        for(int j = 0; j < m; ++j){
            fprintf(output, "%.2lf  ", price[i][j]);
        }
        fprintf(output, "\n");
    }
    fclose(output);
    return;
}

void writePath(const vector<vector<string> > &path){
    FILE *output;
    string fileName = "/Users/zhengq/Documents/Cpp/IntegratedPricingModel/output/path/Paths.dat";
    output = fopen(fileName.c_str(), "w");
    
    int n = (int)path.size();
    if(n == 0) return;
    for(int i = 0; i < n; ++i){
        fprintf(output, "When current period is %d\n", i+1);
        int m = (int)path[i].size();
        for(int j = 0; j < m; ++j){
            fprintf(output, "%.2s  ", path[i][j].c_str());
        }
        fprintf(output, "\n");
    }
    fclose(output);
    return;
}

void writeFrequency(const vector<vector<pair<double,int>> > &frequency, string &t){
    FILE *output;
    betterName(t);
    string fileName = "/Users/zhengq/Documents/Cpp/IntegratedPricingModel/output/frequency/Frequencies At " + t + ".dat";
    output = fopen(fileName.c_str(), "w");
    
    int n = (int)frequency.size();
    if(n == 0) return;
    for(int i = 0; i < n; ++i){
        fprintf(output, "When current period is %d\n", i+1);
        int m = (int)frequency[i].size();
        for(int j = 0; j < m; ++j){
            string s = '(' + convertToString(frequency[i][j].first) + ", " + convertToString(frequency[i][j].second) + ')';
            fprintf(output, "%s  ", s.c_str());
        }
        fprintf(output, "\n");
    }
    fclose(output);
    return;
}

void betterName(string &t){
    for(int i = 0; i < t.length(); ++i){
        if(t[i] == '/') t[i] = '_';
    }
}

void writeCertainPrice(const vector<vector<double> > &price, string &t, int n){
    FILE *output;
    betterName(t);
    string fileName = "/Users/zhengq/Documents/Cpp/IntegratedPricingModel/output/price/CertainPrices At " + t + ".csv";
    output = fopen(fileName.c_str(), "w");
    
//    int n = (int)price.size();
    if(n == 0) return;
    int m = (int)price[n-1].size();
    for(int j = 0; j < m; ++j){
        fprintf(output, "%.2lf\n", price[n-1][j]);
    }
    fclose(output);
    return;

}
