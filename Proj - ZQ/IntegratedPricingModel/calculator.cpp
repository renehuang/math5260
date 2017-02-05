//
//  calculator.cpp
//  IntegratedPricingModel
//
//  Created by Qi Zheng on 12/13/16.
//  Copyright © 2016 Qi ZHENG. All rights reserved.
//

#include <stdio.h>
#include "functions.h"

#define tolerance 0.001

void calculate(vector<vector<string> > &path, const int nSpread[], int nPeriods){
    string tmp = "";
    calculateHelper(path, tmp, 0, nSpread, nPeriods);
}

void calculateHelper(vector<vector<string> > &path, string curr, int currPeriod, const int nSpread[], int nPeriods){
    if(currPeriod > nPeriods) return;
    if(currPeriod == nPeriods){
        path[currPeriod-1].push_back(curr);
        return;
    }
    else{
        if(currPeriod != 0) path[currPeriod-1].push_back(curr);
        if(currPeriod < nSpread[0]){
            calculateHelper(path, curr+'A', currPeriod+1, nSpread, nPeriods);
        }
        if(currPeriod % 3 == 0 && currPeriod/3 < nSpread[1]){
            calculateHelper(path, curr+'B', currPeriod+3, nSpread, nPeriods);
        }
        if(currPeriod % 6 == 0 && currPeriod/6 < nSpread[2]){
            calculateHelper(path, curr+'C', currPeriod+6, nSpread, nPeriods);
        }
        if(currPeriod % 12 == 0 && currPeriod/12 < nSpread[3]){
            calculateHelper(path, curr+'D', currPeriod+12, nSpread, nPeriods);
        }
    }
}

void calculatePrice(vector<vector<double> > &price, const vector<vector<string> > &path, const double &outright, const vector<double> &oneMonthSpread, const vector<double> &threeMonthSpread, const vector<double> &sixMonthSpread, const vector<double> &oneYearSpread){
    int n = (int)path.size();
    if(n == 0) return;
    for(int i = 0; i < n; ++i){
        int m = (int)path[i].size();
        if(m == 0) continue;
        for(int j = 0; j < m; ++j)
            price[i].push_back(calculatePriceHelper(path[i][j], outright, oneMonthSpread, threeMonthSpread, sixMonthSpread, oneYearSpread));
    }
}

double calculatePriceHelper(const string &path, const double &outright, const vector<double> &oneMonthSpread, const vector<double> &threeMonthSpread, const vector<double> &sixMonthSpread, const vector<double> &oneYearSpread){
    int n = (int)path.length();
    if(n == 0) return 0;
    int currPeriod = 0;
    double price = outright;
    for(int i = 0; i < n; ++i){
        if(path[i] == 'A'){
            ++currPeriod;
            price += oneMonthSpread[i];
        }else if(path[i] == 'B'){
            currPeriod += 3;
            price += threeMonthSpread[i/3];
        }else if(path[i] == 'C'){
            currPeriod += 6;
            price += sixMonthSpread[i/6];
        }else if(path[i] == 'D'){
            currPeriod += 12;
            price += oneYearSpread[i/12];
        }
    }
    return price;
}

void getFrequency(vector<vector<pair<double, int>> > &frequency, const vector<vector<double> > &price){
    int n = (int)price.size();
    if(n == 0) return;
    for(int i = 0; i < n; ++i){
        vector<double> tmp;
        tmp.assign(price[i].begin(), price[i].end());
        sort(tmp.begin(), tmp.end());
        int m = (int)tmp.size();
        if(m == 0) continue;
        vector<int> count;
        vector<double> tmp2;
        count.push_back(1); tmp2.push_back(tmp[0]);
        int num = 0;
        for(int j = 1; j < tmp.size(); ++j){
            if((tmp[j]-tmp2[num]) < tolerance) ++count[num];
            else{
                tmp2.push_back(tmp[j]);
                count.push_back(1);
                ++num;
            }
        }
        for(int j = 0; j < tmp2.size(); ++j){
            frequency[i].push_back(make_pair(tmp2[j],count[j]));
        }
    }
}


