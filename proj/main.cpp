//  Real Time Pricing
//  Created by Paulo Becerril on 1/10/17.
//  Copyright © 2017 Paulo Becerril. All rights reserved.


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

// If I want to start in November start=0, December start=1 ...
int start = 0;

// Number represent the last month, 49 is equivalent to November 2020
int number=49;

int col=49;
int row=460000;

int monthindexF[49];
int monthindexB[49];

string trackerF_Bid[49];
string trackerF_Ask[49];

string trackerB_Bid[49];
string trackerB_Ask[49];

string trackerMatrixF_Bid[49][49];
string trackerMatrixF_Ask[49][49];

string trackerMatrixB_Bid[49][49];
string trackerMatrixB_Ask[49][49];

int totalpathsF[49][49];
int totalpathsB[49][49];

float totalprices[49][460000][49];

float maxPricesF[50][49];
float maxPricesB[50][49];

float minPricesF[50][49];
float minPricesB[50][49];

float** matrixF;
float** matrixB;

std::vector<char*> outrightF;
std::vector<char*> onemonthF;
std::vector<char*> threemonthF;
std::vector<char*> sixmonthF;
std::vector<char*> oneyearF;

// Create vectors for Backwards prices
float outrightB[49];
int sizeOutright=49;

float onemonthB[48];
int sizeOneM=48;

float threemonthB[16];
int sizeThreeM=16;

float sixmonthB[8];
int sizeSixM=8;

float oneyearB[4];
int sizeOneY=4;


// Definition of formulas
void forwards(int start, int number);
void backwards(int start, int number);


// Main begin

int main ()
{
    // 1: Read input files ----------------------------------------------------------------------------------------------------
    // 1.1: Outright
    streampos size;
    char * memblock;
    ifstream file ("/Users/paulobecerril/Desktop/Pricing/Paulo/C++/PricingV2/Inputs/outright.csv", ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        // Get the length of the file
        size = file.tellg();
        file.seekg (0, ios::beg);
        // Allocate memory
        memblock = new char [size];
        // Read data as block
        file.read (memblock, size);
        file.close();
        //cout << "outright price content is in memory"<<endl;
        
        // Create our array of outrights
        // We get the pointers of the beginning of each outright
        char* chars_array = strtok(memblock, ",\n");
        // Copy outrights from memblock in the vector outright
        while(chars_array)
        {
            outrightF.push_back(chars_array);
            // Convert to a null character after reading
            chars_array = strtok(NULL, ",\n");
        }
        //cout<<"Size of vector outright "<<outrightF.size()<<endl;
        
        // Print some outrights
        //for (int i=0; i<42;i++){
        //    cout << "outrightF= " << outrightF[i] <<endl;
        //}
    }
    else cout << "Unable to open file";
    
    
    // 1.2: 1 Month
    streampos size1;
    char * memblock1;
    ifstream file1 ("/Users/paulobecerril/Desktop/Pricing/Paulo/C++/PricingV2/Inputs/onemonth.csv", ios::in|ios::binary|ios::ate);
    if (file1.is_open())
    {
        size1 = file1.tellg();
        memblock1 = new char [size1];
        file1.seekg (0, ios::beg);
        file1.read (memblock1, size1);
        file1.close();
        //cout << "one month content is in memory"<<endl;
        
        char* chars_array = strtok(memblock1, ",\n");
        while(chars_array)
        {
            onemonthF.push_back(chars_array);
            chars_array = strtok(NULL, ",\n");
        }
        //cout<<"Size of vector one month "<<onemonthF.size()<<endl;
        
        //for (int i=0; i<12;i++){
        //cout << "one-month spread=" << onemonthF[i] <<endl;
        //}
    }
    else cout << "Unable to open file";
    
    
    // 1.3: 3 Months
    streampos size2;
    char * memblock2;
    ifstream file2 ("/Users/paulobecerril/Desktop/Pricing/Paulo/C++/PricingV2/Inputs/threemonth.csv", ios::in|ios::binary|ios::ate);
    if (file2.is_open())
    {
        size2 = file2.tellg();
        memblock2 = new char [size2];
        file2.seekg (0, ios::beg);
        file2.read (memblock2, size2);
        file2.close();
        //cout << memblock <<endl;
        //cout << "three month content is in memory"<<endl;
        
        
        char* chars_array = strtok(memblock2, ",\n");
        while(chars_array)
        {
            threemonthF.push_back(chars_array);
            chars_array = strtok(NULL, ",\n");
        }
        //cout<<"Size of vector three month "<<threemonthF.size()<<endl;
        
    }
    else cout << "Unable to open file";
    
    
    // 1.4: 6 Months
    streampos size3;
    char * memblock3;
    ifstream file3 ("/Users/paulobecerril/Desktop/Pricing/Paulo/C++/PricingV2/Inputs/sixmonth.csv", ios::in|ios::binary|ios::ate);
    if (file3.is_open())
    {
        size3 = file3.tellg();
        memblock3 = new char [size3];
        file3.seekg (0, ios::beg);
        file3.read (memblock3, size3);
        file3.close();
        //cout << memblock <<endl;
        //cout << "six month content is in memory"<<endl;
        
        char* chars_array = strtok(memblock3, ",\n");
        while(chars_array)
        {
            sixmonthF.push_back(chars_array);
            chars_array = strtok(NULL, ",\n");
        }
        //cout<<"Size of vector six month "<<sixmonthF.size()<<endl;
    }
    else cout << "Unable to open file";
    
    
    //1.5: 1 year
    streampos size4;
    char * memblock4;
    ifstream file4 ("/Users/paulobecerril/Desktop/Pricing/Paulo/C++/PricingV2/Inputs/oneyear.csv", ios::in|ios::binary|ios::ate);
    if (file4.is_open())
    {
        size4 = file4.tellg();
        memblock4 = new char [size4];
        file4.seekg (0, ios::beg);
        file4.read (memblock4, size4);
        file4.close();
        //cout << memblock <<endl;
        //cout << "one year content is in memory"<<endl;
        
        char* chars_array = strtok(memblock4, ",\n");
        while(chars_array)
        {
            oneyearF.push_back(chars_array);
            chars_array = strtok(NULL, ",\n");
        }
        //cout<<"Size of vector one year "<<oneyearF.size()<<endl;
    }
    else cout << "Unable to open file";
    
    // Fill Backwards Prices
    // Outright
    for(int k=0; k<sizeOutright; k++){
        outrightB[k]=atof(outrightF[sizeOutright-1-k]);
        //outrightB[k]=atof(outrightF[k]);
    }
    
    // One Month
    for(int k=0; k<sizeOneM; k++){
        onemonthB[k]=atof(onemonthF[sizeOneM-1-k]);
        //onemonthB[k]=atof(onemonthF[k]);
    }
    
    // Three Months
    for(int k=0; k<sizeThreeM; k++){
        threemonthB[k]=atof(threemonthF[sizeThreeM-1-k]);
        //threemonthB[k]=atof(threemonthF[k]);
    }
    
    // Six Months
    for(int k=0; k<sizeSixM; k++){
        sixmonthB[k]=atof(sixmonthF[sizeSixM-1-k]);
        //sixmonthB[k]=atof(sixmonthF[k]);
    }
    
    // One Year
    for(int k=0; k<sizeOneY; k++){
        oneyearB[k]=atof(oneyearF[sizeOneY-1-k]);
        //oneyearB[k]=atof(oneyearF[k]);
    }
    
    
    
    // 2: Initialize Matrices -------------------------------------------------------------------------------------------------
    // 2.1: Total Paths
    for (int r=0; r<number;r++){
        for (int s=0; s<number;s++){
            totalpathsF[s][r] = 0;
            totalpathsB[s][r] = 0;
            
        }
    }
    
    // 2.2 Max Price Matrix. The matrix has dim [50][49], because the first row is for the max of each column
    for (int r=0; r<number;r++){
        for (int s=0; s<(number+1);s++){
            maxPricesF[s][r] = 0;
            maxPricesB[s][r] = 0;
            minPricesF[s][r] = 0;
            minPricesB[s][r] = 0;
        }
    }
    
    cout << "Empezamos Forwards" << endl;
    
    // 3a: Loop: for all starting months Forwards: -----------------------------------------------------------------------------
    
    for (int j=start; j<number; j++){
        
        // 3.1: Create a matrix to store prices
        matrixF = new float*[row];
        for(int i = 0; i < row; ++i){
            matrixF[i] = new float[col];
        }
        
        // 3.2: Fill the matrix with zeros
        for(int i=0;i<row;i++) {
            for(int k=0;k<col;k++) {
                matrixF[i][k]=0;
            }
        }
        
        // 3.3: Initialize the month matrix index counter
        for (int r=0; r<number;r++){
            monthindexF[r] = 0;
            trackerF_Bid[r]="";
            trackerF_Ask[r]="";
        }
        
        // 3.4: Call function "constructPaths"
        string indexF;
        indexF=to_string(j+1);
        
        forwards(j,number);
        
        // Prueba
        /*
         for (int r=1; r<number;r++){
         cout << "Start: "<< j << " Mes: " << r << " Tracker: "<< trackerV[r] << endl;
         }
         */
        
        
        // 3.5: Fill Total Path Matrix and Tracker Matrix
        for (int r=1; r<number;r++){
            totalpathsF[r-1][j]=monthindexF[r];
            if (atof(outrightF[j])>0){
                //cout << "j: " << j << " " << outrightF[j] << endl;
                trackerMatrixF_Bid[j][r-1]=trackerF_Bid[r];
                trackerMatrixF_Ask[j][r-1]=trackerF_Ask[r];
            }
        }
        
        // 3.6: Fill Total Path Matrix and Export prices to csv
        //ofstream mytotalpriceF;
        //mytotalpriceF.open ("pricesF"+indexF+".csv");
        for (int m=0; m<row; m++){
            for (int n=0; n<col; n++){
                totalprices[j][m][n]=matrixF[m][n];
                //mytotalpriceF << totalprices[j][m][n]<<",";
            }
            //mytotalpriceF<<"\n";
        }
        //mytotalpriceF.close();
        
        
    } // Close the loop for all months ----------------------------------------------------------------------------------------
    
    
    // 4: Export Total Paths Forwards to csv
    /*
    ofstream mytotalpathF;
    mytotalpathF.open ("totalpathF.csv");
    for (int m=0; m<number; m++){
        for (int n=0; n<number; n++){
            mytotalpathF << totalpathsF[m][n]<<",";
        }
        mytotalpathF<<"\n";
    }
    mytotalpathF.close();
    */
    // Total Paths exported ---------------------------------------------------------------------------------------------------
    
    
    // 5: Export Tracker Bid and Ask to csv
    
    ofstream mytrackerF_Bid;
    mytrackerF_Bid.open ("trackerF_Bid.csv");
    for (int m=0; m<number; m++){
        for (int n=0; n<number; n++){
            mytrackerF_Bid << trackerMatrixF_Bid[m][n]<<",";
        }
        mytrackerF_Bid<<"\n";
    }
    mytrackerF_Bid.close();
    
    ofstream mytrackerF_Ask;
    mytrackerF_Ask.open ("trackerF_Ask.csv");
    for (int m=0; m<number; m++){
        for (int n=0; n<number; n++){
            mytrackerF_Ask << trackerMatrixF_Ask[m][n]<<",";
        }
        mytrackerF_Ask<<"\n";
    }
    mytrackerF_Ask.close();
    
    // Tracker exported ---------------------------------------------------------------------------------------------------
    
    
    // 6: Max Price Matrix
    // 6.1: Fill Max and Min Price Matrix. It starts in j+1 because the first row is for the max/min of the maxs/mins of each column
    
    float auxMaxF=0;
    float auxMinF=1000;
    
    for (int j=0; j<number; j++){
        for (int n=0; n<col; n++){
            for (int m=0; m<row; m++){
                if(totalprices[j][m][n]>auxMaxF){
                    auxMaxF=totalprices[j][m][n];
                }
                if(totalprices[j][m][n]<auxMinF && totalprices[j][m][n]>0){
                    auxMinF=totalprices[j][m][n];
                }
            }
            maxPricesF[j+1][n]=auxMaxF;
            auxMaxF=0;
            minPricesF[j+1][n]=auxMinF;
            auxMinF=1000;
        }
    }
    // 6.2: The Max of Maxs and Min of the Mins
    float auxMaxMax=0;
    float auxMinMin=1000;
    
    for (int j=0; j<number; j++){
        for (int m=1; m<(number+1); m++){
            if(maxPricesF[m][j]>auxMaxMax){
                auxMaxMax=maxPricesF[m][j];
            }
            if(minPricesF[m][j]<auxMinMin && minPricesF[m][j]>0){
                auxMinMin=minPricesF[m][j];
            }
        }
        maxPricesF[0][j]=auxMaxMax;
        auxMaxMax=0;
        minPricesF[0][j]=auxMinMin;
        auxMinMin=1000;
    }
    
    // 6.3: Export Max and Min Prices to csv
    ofstream mymaxpriceF;
    mymaxpriceF.open ("maxpriceF.csv");
    for (int m=0; m<(number+1); m++){
        for (int n=0; n<number; n++){
            mymaxpriceF << maxPricesF[m][n]<<",";
        }
        mymaxpriceF<<"\n";
    }
    mymaxpriceF.close();
    
    ofstream myminpriceF;
    myminpriceF.open ("minpriceF.csv");
    for (int m=0; m<(number+1); m++){
        for (int n=0; n<number; n++){
            myminpriceF << minPricesF[m][n]<<",";
        }
        myminpriceF<<"\n";
    }
    myminpriceF.close();
    
    // Forwards Ends!! ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    
    // 3b: Loop: for all starting months Backwards: ----------------------------------------------------------------------------
    
    cout << "Pasamos a Backwards" << endl;
    
    for (int j=start; j<number; j++){
        
        // 3.1: Create a matrix to store prices
        matrixB = new float*[row];
        for(int i = 0; i < row; ++i){
            matrixB[i] = new float[col];
        }
        
        // 3.2: Fill the matrix with zeros
        for(int i=0;i<row;i++) {
            for(int k=0; k<col; k++) {
                matrixB[i][k]=0;
            }
        }
        
        // 3.3: Initialize the month matrix index counter
        for (int r=0; r<number;r++){
            monthindexB[r] = 0;
            trackerB_Bid[r]="";
            trackerB_Ask[r]="";
        }
        
        // 3.4: Call function "constructPaths"
        string indexB;
        indexB=to_string(j+1);
        
        backwards(j,number);
        
        
        // 3.5: Fill Total Path Matrix and Tracker Matrix
        for (int r=1; r<number;r++){
            totalpathsB[r-1][j]=monthindexB[r];
            if (outrightB[j]>0){
                //cout << "j: " << j << " " << outrightB[j] << endl;
                trackerMatrixB_Bid[j][r-1]=trackerB_Bid[r];
                trackerMatrixB_Ask[j][r-1]=trackerB_Ask[r];
            }
        }
        
        // 3.6: Fill Total Path Matrix and Export prices to csv
        //ofstream mytotalpriceB;
        //mytotalpriceB.open ("pricesB"+indexB+".csv");
        for (int m=0; m<row; m++){
            for (int n=0; n<col; n++){
                totalprices[j][m][n]=matrixB[m][n];
                //mytotalpriceB << totalprices[j][m][n]<<",";
            }
            //mytotalpriceB<<"\n";
        }
        //mytotalpriceB.close();
        
        
    } // Close the loop for all months ----------------------------------------------------------------------------------------
    
    
    // 4: Export Total Paths Backwards to csv
    /*
     ofstream mytotalpathB;
     mytotalpathB.open ("totalpathB.csv");
     for (int m=0; m<number; m++){
        for (int n=0; n<number; n++){
            mytotalpathB << totalpathsB[m][n]<<",";
        }
        mytotalpathB<<"\n";
     }
     mytotalpathB.close();
     */
    // Total Paths exported ---------------------------------------------------------------------------------------------------
    
    
    // 5: Export Trackers to csv
    
    ofstream mytrackerB_Bid;
    mytrackerB_Bid.open ("trackerB_Bid.csv");
    for (int m=0; m<number; m++){
        for (int n=0; n<number; n++){
            mytrackerB_Bid << trackerMatrixB_Bid[m][n]<<",";
        }
        mytrackerB_Bid<<"\n";
    }
    mytrackerB_Bid.close();
    
    ofstream mytrackerB_Ask;
    mytrackerB_Ask.open ("trackerB_Ask.csv");
    for (int m=0; m<number; m++){
        for (int n=0; n<number; n++){
            mytrackerB_Ask << trackerMatrixB_Ask[m][n]<<",";
        }
        mytrackerB_Ask<<"\n";
    }
    mytrackerB_Ask.close();
    
    // Tracker exported ---------------------------------------------------------------------------------------------------
    
    
    // 6: Max Price Matrix
    // 6.1: Fill Max Price Matrix. It starts in j+1 because the first row is for the max of the maxs of each column
    float auxMaxB=0;
    float auxMinB=1000;
    
    for (int j=0; j<number; j++){
        for (int n=0; n<col; n++){
            for (int m=0; m<row; m++){
                if(totalprices[j][m][n]>auxMaxB){
                    auxMaxB=totalprices[j][m][n];
                }
                if(totalprices[j][m][n]<auxMinB && totalprices[j][m][n]>0){
                    auxMinB=totalprices[j][m][n];
                }
            }
            maxPricesB[j+1][n]=auxMaxB;
            auxMaxB=0;
            minPricesB[j+1][n]=auxMinB;
            auxMinB=1000;
        }
    }
    // 6.2: The Max of Maxs and the Min of the Mins
    float auxMaxMaxB=0;
    float auxMinMinB=1000;
    
    for (int j=0; j<number; j++){
        for (int m=1; m<(number+1); m++){
            if(maxPricesB[m][j]>auxMaxMaxB){
                auxMaxMaxB=maxPricesB[m][j];
            }
            if(minPricesB[m][j]<auxMinMinB && minPricesB[m][j]>0){
                auxMinMinB=minPricesB[m][j];
            }
        }
        maxPricesB[0][j]=auxMaxMaxB;
        auxMaxMaxB=0;
        minPricesB[0][j]=auxMinMinB;
        auxMaxMaxB=1000;
    }
    
    // 6.3: Export Max and Min Prices to csv
    // Best Bid Backwards
    ofstream mymaxpriceB;
    mymaxpriceB.open ("maxpriceB.csv");
    for (int m=0; m<(number+1); m++){
        for (int n=0; n<number; n++){
            mymaxpriceB << maxPricesB[m][n]<<",";
        }
        mymaxpriceB<<"\n";
    }
    mymaxpriceB.close();
    
    // Best Ask Backwards
    ofstream myminpriceB;
    myminpriceB.open ("minpriceB.csv");
    for (int m=0; m<(number+1); m++){
        for (int n=0; n<number; n++){
            myminpriceB << minPricesB[m][n]<<",";
        }
        myminpriceB<<"\n";
    }
    myminpriceB.close();
    
    // Backwards Ends!!---------------------------------------------------------------------------------------------------------
    
    return 0;
    
}


void forwards(int start, int number){
    //If you are selling a stock, you are going to get the bid price (MAX Price), if you are buying a stock you are going to get the ask price (MIN Price).
    
    monthindexF[start]=1;
    // The first non-zero entry of the matrix of prices is the outright
    matrixF[0][start]=atof(outrightF[start]);
    
    
    //cout << "Start: "<< start << endl;
    //cout << "Number of months: "<< number << endl;
    
    for (int i=(start+1); i<number; i++){
        
        // 1 Month
        if(i%3>0 & i%6>0 & i%12>0){
            
            for(int j=0; j<monthindexF[i-1]; j++){
                matrixF[j][i]=matrixF[j][i-1]-atof(onemonthF[i-1]);
            }
            
            // Number of paths
            monthindexF[i]=monthindexF[i-1];
            
            // Tracker
            string tracker1F="1M-";
            trackerF_Bid[i]=tracker1F;
            trackerF_Ask[i]=tracker1F;
            //cout << "Start: " <<start<< "tracker: " << tracker1 << endl;
            
        } // Close 1 Month
        
        
        // 3 Months
        if(i%3==0)
        {
            // For 1 month
            double aux3m1F_Bid=0;
            double aux3m1F_Ask=1000;
            for(int j=0; j<monthindexF[i-1]; j++){
                matrixF[j][i]=matrixF[j][i-1]-atof(onemonthF[i-1]);
                if (matrixF[j][i]>aux3m1F_Bid){
                    aux3m1F_Bid=matrixF[j][i];
                }
                if (matrixF[j][i]<aux3m1F_Ask){
                    aux3m1F_Ask=matrixF[j][i];
                }
            }
            
            double aux3m3F_Bid=0;
            double aux3m3F_Ask=1000;
            // For 3 months
            for(int j=0; j<monthindexF[i-3]; j++){
                matrixF[monthindexF[i-1]+j][i]=matrixF[j][i-3]-atof(threemonthF[i/3-1]);
                if (matrixF[monthindexF[i-1]+j][i]>aux3m3F_Bid){
                    aux3m3F_Bid=matrixF[monthindexF[i-1]+j][i];
                }
                if (matrixF[monthindexF[i-1]+j][i]<aux3m3F_Ask){
                    aux3m3F_Ask=matrixF[monthindexF[i-1]+j][i];
                }
            }
            
            // Number of paths
            monthindexF[i]=monthindexF[i-1]+monthindexF[i-3];
            
            // Tracker
            double maxAux3F=0;
            double minAux3F=1000;
            maxAux3F=max({aux3m1F_Bid,aux3m3F_Bid});
            minAux3F=min({aux3m1F_Ask,aux3m3F_Ask});
            
            string tracker3F_Bid="";
            string tracker3F_Ask="";
            
            if (aux3m1F_Bid==maxAux3F)
                tracker3F_Bid=tracker3F_Bid+"1M-";
            if (aux3m3F_Bid==maxAux3F)
                tracker3F_Bid=tracker3F_Bid+"3M";
            trackerF_Bid[i]=tracker3F_Bid;
            
            if (aux3m1F_Ask==minAux3F)
                tracker3F_Ask=tracker3F_Ask+"1M-";
            if (aux3m3F_Ask==minAux3F)
                tracker3F_Ask=tracker3F_Ask+"3M";
            trackerF_Ask[i]=tracker3F_Ask;
            
            //cout << "Start: " <<start<< "tracker: " << tracker3 << endl;
            
        } // Close 3 Months
        
        
        // 6 Months
        if(i%6==0)
        {
            // For 1 month
            double aux6m1F_Bid=0;
            double aux6m1F_Ask=1000;
            for(int j=0; j<monthindexF[i-1]; j++){
                matrixF[j][i]=matrixF[j][i-1]-atof(onemonthF[i-1]);
                if (matrixF[j][i]>aux6m1F_Bid){
                    aux6m1F_Bid=matrixF[j][i];
                }
                if (matrixF[j][i]<aux6m1F_Ask){
                    aux6m1F_Ask=matrixF[j][i];
                }
            }
            
            // For 3 months
            double aux6m3F_Bid=0;
            double aux6m3F_Ask=1000;
            for(int j=0; j<monthindexF[i-3]; j++){
                matrixF[monthindexF[i-1]+j][i]=matrixF[j][i-3]-atof(threemonthF[i/3-1]);
                if (matrixF[monthindexF[i-1]+j][i]>aux6m3F_Bid){
                    aux6m3F_Bid=matrixF[monthindexF[i-1]+j][i];
                }
                if (matrixF[monthindexF[i-1]+j][i]<aux6m3F_Ask){
                    aux6m3F_Ask=matrixF[monthindexF[i-1]+j][i];
                }
            }
            
            // For 6 months
            double aux6m6F_Bid=0;
            double aux6m6F_Ask=1000;
            for(int j=0; j<monthindexF[i-6]; j++){
                matrixF[monthindexF[i-1]+monthindexF[i-3]+j][i]=matrixF[j][i-6]-atof(sixmonthF[i/6-1]);
                if (matrixF[monthindexF[i-1]+monthindexF[i-3]+j][i]>aux6m6F_Bid){
                    aux6m6F_Bid=matrixF[monthindexF[i-1]+monthindexF[i-3]+j][i];
                }
                if (matrixF[monthindexF[i-1]+monthindexF[i-3]+j][i]<aux6m6F_Ask){
                    aux6m6F_Ask=matrixF[monthindexF[i-1]+monthindexF[i-3]+j][i];
                }
            }
            
            // Number of paths
            monthindexF[i]=monthindexF[i-1]+monthindexF[i-3]+monthindexF[i-6];
            
            // Tracker
            double maxAux6F=0;
            double minAux6F=1000;
            maxAux6F=max({aux6m1F_Bid,aux6m3F_Bid,aux6m6F_Bid});
            minAux6F=min({aux6m1F_Ask,aux6m3F_Ask,aux6m6F_Ask});

            string tracker6F_Bid="";
            string tracker6F_Ask="";
            
            if (aux6m1F_Bid==maxAux6F)
                tracker6F_Bid=tracker6F_Bid+"1M-";
            if (aux6m3F_Bid==maxAux6F)
                tracker6F_Bid=tracker6F_Bid+"3M-";
            if (aux6m6F_Bid==maxAux6F)
                tracker6F_Bid=tracker6F_Bid+"6M";
            trackerF_Bid[i]=tracker6F_Bid;
            
            if (aux6m1F_Ask==minAux6F)
                tracker6F_Ask=tracker6F_Ask+"1M-";
            if (aux6m3F_Ask==minAux6F)
                tracker6F_Ask=tracker6F_Ask+"3M-";
            if (aux6m6F_Ask==minAux6F)
                tracker6F_Ask=tracker6F_Ask+"6M";
            trackerF_Ask[i]=tracker6F_Ask;
            
            //cout << "Start: " <<start<< "tracker: " << tracker6 << endl;
            
        } // Close 6 Months
        
        
        // 12 Months
        if(i%12==0)
        {
            // For 1 month
            double aux12m1F_Bid=0;
            double aux12m1F_Ask=1000;
            for(int j=0; j<monthindexF[i-1]; j++){
                matrixF[j][i]=matrixF[j][i-1]-atof(onemonthF[i-1]);
                if (matrixF[j][i]>aux12m1F_Bid){
                    aux12m1F_Bid=matrixF[j][i];
                }
                if (matrixF[j][i]<aux12m1F_Ask){
                    aux12m1F_Ask=matrixF[j][i];
                }
            }
            
            // For 3 months
            double aux12m3F_Bid=0;
            double aux12m3F_Ask=1000;
            for(int j=0; j<monthindexF[i-3]; j++){
                matrixF[monthindexF[i-1]+j][i]=matrixF[j][i-3]-atof(threemonthF[i/3-1]);
                if (matrixF[monthindexF[i-1]+j][i]>aux12m3F_Bid){
                    aux12m3F_Bid=matrixF[monthindexF[i-1]+j][i];
                }
                if (matrixF[monthindexF[i-1]+j][i]<aux12m3F_Ask){
                    aux12m3F_Ask=matrixF[monthindexF[i-1]+j][i];
                }
            }
            
            // For 6 months
            double aux12m6F_Bid=0;
            double aux12m6F_Ask=1000;
            for(int j=0; j<monthindexF[i-6]; j++){
                matrixF[monthindexF[i-1]+monthindexF[i-3]+j][i]=matrixF[j][i-6]-atof(sixmonthF[i/6-1]);
                if (matrixF[monthindexF[i-1]+monthindexF[i-3]+j][i]>aux12m6F_Bid){
                    aux12m6F_Bid=matrixF[monthindexF[i-1]+monthindexF[i-3]+j][i];
                }
                if (matrixF[monthindexF[i-1]+monthindexF[i-3]+j][i]<aux12m6F_Ask){
                    aux12m6F_Ask=matrixF[monthindexF[i-1]+monthindexF[i-3]+j][i];
                }
            }
            
            // For 1 year
            double aux12m12F_Bid=0;
            double aux12m12F_Ask=1000;
            for(int j=0; j<monthindexF[i-12]; j++){
                matrixF[monthindexF[i-1]+monthindexF[i-3]+monthindexF[i-6]+j][i]=matrixF[j][i-12]-atof(oneyearF[i/12-1]);
                if (matrixF[monthindexF[i-1]+monthindexF[i-3]+monthindexF[i-6]+j][i]>aux12m12F_Bid){
                    aux12m12F_Bid=matrixF[monthindexF[i-1]+monthindexF[i-3]+monthindexF[i-6]+j][i];
                }
                if (matrixF[monthindexF[i-1]+monthindexF[i-3]+monthindexF[i-6]+j][i]<aux12m12F_Ask){
                    aux12m12F_Ask=matrixF[monthindexF[i-1]+monthindexF[i-3]+monthindexF[i-6]+j][i];
                }
                
            }
            
            // Number of paths
            monthindexF[i]=monthindexF[i-1]+monthindexF[i-3]+monthindexF[i-6]+monthindexF[i-12];
            
            double maxAux12F=0;
            double minAux12F=1000;
            maxAux12F=max({aux12m1F_Bid,aux12m3F_Bid,aux12m6F_Bid,aux12m12F_Bid});
            minAux12F=min({aux12m1F_Ask,aux12m3F_Ask,aux12m6F_Ask,aux12m12F_Ask});
            
            string tracker12F_Bid="";
            string tracker12F_Ask="";
            
            if (aux12m1F_Bid==maxAux12F)
                tracker12F_Bid=tracker12F_Bid+"1M-";
            if (aux12m3F_Bid==maxAux12F)
                tracker12F_Bid=tracker12F_Bid+"3M-";
            if (aux12m6F_Bid==maxAux12F)
                tracker12F_Bid=tracker12F_Bid+"6M-";
            if (aux12m12F_Bid==maxAux12F)
                tracker12F_Bid=tracker12F_Bid+"1Y";
            trackerF_Bid[i]=tracker12F_Bid;
            
            if (aux12m1F_Ask==minAux12F)
                tracker12F_Ask=tracker12F_Ask+"1M-";
            if (aux12m3F_Ask==minAux12F)
                tracker12F_Ask=tracker12F_Ask+"3M-";
            if (aux12m6F_Ask==minAux12F)
                tracker12F_Ask=tracker12F_Ask+"6M-";
            if (aux12m12F_Ask==minAux12F)
                tracker12F_Ask=tracker12F_Ask+"1Y";
            trackerF_Ask[i]=tracker12F_Ask;
            
            //cout << "Start: " <<start<< "tracker: " << tracker12 << endl;
        }
        
    }
}


void backwards(int start, int number){
    
    monthindexB[start]=1;
    // The first non-zero entry of the matrix of prices is the outright
    matrixB[0][start]=outrightB[start];
    
    
    //cout << "Start: "<< start << endl;
    //cout << "Number of months: "<< number << endl;
    
    for (int i=(start+1); i<number; i++){
        
        // 1 Month
        if(i%3>0 & i%6>0 & i%12>0){
            
            for(int j=0; j<monthindexB[i-1]; j++){
                matrixB[j][i]=matrixB[j][i-1]+onemonthB[i-1];
            }
            
            // Number of paths
            monthindexB[i]=monthindexB[i-1];
            
            // Tracker
            string tracker1B="1M-";
            trackerB_Bid[i]=tracker1B;
            trackerB_Ask[i]=tracker1B;
            //cout << "Start: " <<start<< "tracker: " << tracker1 << endl;
            
        } // Close 1 Month
        
        
        // 3 Months
        if(i%3==0)
        {
            // For 1 month
            double aux3m1B_Bid=0;
            double aux3m1B_Ask=1000;
            for(int j=0; j<monthindexB[i-1]; j++){
                matrixB[j][i]=matrixB[j][i-1]+onemonthB[i-1];
                if (matrixB[j][i]>aux3m1B_Bid){
                    aux3m1B_Bid=matrixB[j][i];
                }
                if (matrixB[j][i]<aux3m1B_Ask){
                    aux3m1B_Ask=matrixB[j][i];
                }
            }
            
            double aux3m3B_Bid=0;
            double aux3m3B_Ask=1000;
            // For 3 months
            for(int j=0; j<monthindexB[i-3]; j++){
                matrixB[monthindexB[i-1]+j][i]=matrixB[j][i-3]+threemonthB[i/3-1];
                if (matrixB[monthindexB[i-1]+j][i]>aux3m3B_Bid){
                    aux3m3B_Bid=matrixB[monthindexB[i-1]+j][i];
                }
                if (matrixB[monthindexB[i-1]+j][i]<aux3m3B_Ask){
                    aux3m3B_Ask=matrixB[monthindexB[i-1]+j][i];
                }
            }
            
            // Number of paths
            monthindexB[i]=monthindexB[i-1]+monthindexB[i-3];
            
            // Tracker
            double maxAux3B=0;
            double minAux3B=1000;
            maxAux3B=max({aux3m1B_Bid,aux3m3B_Bid});
            minAux3B=min({aux3m1B_Ask,aux3m3B_Ask});
            
            string tracker3B_Bid="";
            string tracker3B_Ask="";
            
            if (aux3m1B_Bid==maxAux3B)
                tracker3B_Bid=tracker3B_Bid+"1M-";
            if (aux3m3B_Bid==maxAux3B)
                tracker3B_Bid=tracker3B_Bid+"3M";
            trackerB_Bid[i]=tracker3B_Bid;
            
            if (aux3m1B_Ask==minAux3B)
                tracker3B_Ask=tracker3B_Ask+"1M-";
            if (aux3m3B_Ask==minAux3B)
                tracker3B_Ask=tracker3B_Ask+"3M";
            trackerB_Ask[i]=tracker3B_Ask;
            
            //cout << "Start: " <<start<< "tracker: " << tracker3 << endl;
            
        } // Close 3 Months
        
        
        // 6 Months
        if(i%6==0)
        {
            // For 1 month
            double aux6m1B_Bid=0;
            double aux6m1B_Ask=1000;
            for(int j=0; j<monthindexB[i-1]; j++){
                matrixB[j][i]=matrixB[j][i-1]+onemonthB[i-1];
                if (matrixB[j][i]>aux6m1B_Bid){
                    aux6m1B_Bid=matrixB[j][i];
                }
                if (matrixB[j][i]<aux6m1B_Ask){
                    aux6m1B_Ask=matrixB[j][i];
                }
            }
            
            // For 3 months
            double aux6m3B_Bid=0;
            double aux6m3B_Ask=1000;
            for(int j=0; j<monthindexB[i-3]; j++){
                matrixB[monthindexB[i-1]+j][i]=matrixB[j][i-3]+threemonthB[i/3-1];
                if (matrixB[monthindexB[i-1]+j][i]>aux6m3B_Bid){
                    aux6m3B_Bid=matrixB[monthindexB[i-1]+j][i];
                }
                if (matrixB[monthindexB[i-1]+j][i]<aux6m3B_Ask){
                    aux6m3B_Ask=matrixB[monthindexB[i-1]+j][i];
                }
            }
            
            // For 6 months
            double aux6m6B_Bid=0;
            double aux6m6B_Ask=1000;
            for(int j=0; j<monthindexB[i-6]; j++){
                matrixB[monthindexB[i-1]+monthindexB[i-3]+j][i]=matrixB[j][i-6]+sixmonthB[i/6-1];
                if (matrixB[monthindexB[i-1]+monthindexB[i-3]+j][i]>aux6m6B_Bid){
                    aux6m6B_Bid=matrixB[monthindexB[i-1]+monthindexB[i-3]+j][i];
                }
                if (matrixB[monthindexB[i-1]+monthindexB[i-3]+j][i]<aux6m6B_Ask){
                    aux6m6B_Ask=matrixB[monthindexB[i-1]+monthindexB[i-3]+j][i];
                }
            }
            
            // Number of paths
            monthindexB[i]=monthindexB[i-1]+monthindexB[i-3]+monthindexB[i-6];
            
            // Tracker
            double maxAux6B=0;
            double minAux6B=1000;
            maxAux6B=max({aux6m1B_Bid,aux6m3B_Bid,aux6m6B_Bid});
            minAux6B=min({aux6m1B_Ask,aux6m3B_Ask,aux6m6B_Ask});
            
            string tracker6B_Bid="";
            string tracker6B_Ask="";
            
            if (aux6m1B_Bid==maxAux6B)
                tracker6B_Bid=tracker6B_Bid+"1M-";
            if (aux6m3B_Bid==maxAux6B)
                tracker6B_Bid=tracker6B_Bid+"3M-";
            if (aux6m6B_Bid==maxAux6B)
                tracker6B_Bid=tracker6B_Bid+"6M";
            trackerB_Bid[i]=tracker6B_Bid;
            
            if (aux6m1B_Ask==minAux6B)
                tracker6B_Ask=tracker6B_Ask+"1M-";
            if (aux6m3B_Ask==minAux6B)
                tracker6B_Ask=tracker6B_Ask+"3M-";
            if (aux6m6B_Ask==minAux6B)
                tracker6B_Ask=tracker6B_Ask+"6M";
            trackerB_Ask[i]=tracker6B_Ask;
            
            //cout << "Start: " <<start<< "tracker: " << tracker6 << endl;
            
        } // Close 6 Months
        
        
        // 12 Months
        if(i%12==0)
        {
            // For 1 month
            double aux12m1B_Bid=0;
            double aux12m1B_Ask=1000;
            for(int j=0; j<monthindexB[i-1]; j++){
                matrixB[j][i]=matrixB[j][i-1]+onemonthB[i-1];
                if (matrixB[j][i]>aux12m1B_Bid){
                    aux12m1B_Bid=matrixB[j][i];
                }
                if (matrixB[j][i]<aux12m1B_Ask){
                    aux12m1B_Ask=matrixB[j][i];
                }
            }
            
            // For 3 months
            double aux12m3B_Bid=0;
            double aux12m3B_Ask=1000;
            for(int j=0; j<monthindexB[i-3]; j++){
                matrixB[monthindexB[i-1]+j][i]=matrixB[j][i-3]+threemonthB[i/3-1];
                if (matrixB[monthindexB[i-1]+j][i]>aux12m3B_Bid){
                    aux12m3B_Bid=matrixB[monthindexB[i-1]+j][i];
                }
                if (matrixB[monthindexB[i-1]+j][i]<aux12m3B_Ask){
                    aux12m3B_Ask=matrixB[monthindexB[i-1]+j][i];
                }
                
            }
            
            // For 6 months
            double aux12m6B_Bid=0;
            double aux12m6B_Ask=1000;
            for(int j=0; j<monthindexB[i-6]; j++){
                matrixB[monthindexB[i-1]+monthindexB[i-3]+j][i]=matrixB[j][i-6]+sixmonthB[i/6-1];
                if (matrixB[monthindexB[i-1]+monthindexB[i-3]+j][i]>aux12m6B_Bid){
                    aux12m6B_Bid=matrixB[monthindexB[i-1]+monthindexB[i-3]+j][i];
                }
                if (matrixB[monthindexB[i-1]+monthindexB[i-3]+j][i]<aux12m6B_Ask){
                    aux12m6B_Ask=matrixB[monthindexB[i-1]+monthindexB[i-3]+j][i];
                }
                
            }
            
            // For 1 year
            double aux12m12B_Bid=0;
            double aux12m12B_Ask=1000;
            
            for(int j=0; j<monthindexB[i-12]; j++){
                matrixB[monthindexB[i-1]+monthindexB[i-3]+monthindexB[i-6]+j][i]=matrixB[j][i-12]+oneyearB[i/12-1];
                if (matrixB[monthindexB[i-1]+monthindexB[i-3]+monthindexB[i-6]+j][i]>aux12m12B_Bid){
                    aux12m12B_Bid=matrixB[monthindexB[i-1]+monthindexB[i-3]+monthindexB[i-6]+j][i];
                }
                if (matrixB[monthindexB[i-1]+monthindexB[i-3]+monthindexB[i-6]+j][i]<aux12m12B_Ask){
                    aux12m12B_Ask=matrixB[monthindexB[i-1]+monthindexB[i-3]+monthindexB[i-6]+j][i];
                }
                
            }
            
            // Number of paths
            monthindexB[i]=monthindexB[i-1]+monthindexB[i-3]+monthindexB[i-6]+monthindexB[i-12];
            
            double maxAux12B=0;
            double minAux12B=1000;
            maxAux12B=max({aux12m1B_Bid,aux12m3B_Bid,aux12m6B_Bid,aux12m12B_Bid});
            minAux12B=min({aux12m1B_Ask,aux12m3B_Ask,aux12m6B_Ask,aux12m12B_Ask});
            
            string tracker12B_Bid="";
            string tracker12B_Ask="";
            
            if (aux12m1B_Bid==maxAux12B)
                tracker12B_Bid=tracker12B_Bid+"1M-";
            if (aux12m3B_Bid==maxAux12B)
                tracker12B_Bid=tracker12B_Bid+"3M-";
            if (aux12m6B_Bid==maxAux12B)
                tracker12B_Bid=tracker12B_Bid+"6M-";
            if (aux12m12B_Bid==maxAux12B)
                tracker12B_Bid=tracker12B_Bid+"1Y";
            trackerB_Bid[i]=tracker12B_Bid;
            
            if (aux12m1B_Ask==minAux12B)
                tracker12B_Ask=tracker12B_Ask+"1M-";
            if (aux12m3B_Ask==minAux12B)
                tracker12B_Ask=tracker12B_Ask+"3M-";
            if (aux12m6B_Ask==minAux12B)
                tracker12B_Ask=tracker12B_Ask+"6M-";
            if (aux12m12B_Ask==minAux12B)
                tracker12B_Ask=tracker12B_Ask+"1Y";
            trackerB_Ask[i]=tracker12B_Ask;
            
            //cout << "Start: " <<start<< "tracker: " << tracker12 << endl;
        }
        
    }
}