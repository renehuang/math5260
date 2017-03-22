#include <stdio.h>
#include <math.h>
#include <iostream>
#include <complex>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <math.h>
#include "simplex.h"

using namespace std;

typedef complex<double> dcmplx;
typedef dcmplx (*charFuncOfLogOfStock)(dcmplx&, double, double, double, double, double, double, double);

#define PI  3.1415926535897932

//---------------------------------------------------------------
// FFT functions
dcmplx* FFT_simple(dcmplx*, int);
dcmplx* IFFT_simple(dcmplx*, int);
void FFT_calculate(dcmplx*, int, int, dcmplx*, dcmplx*, dcmplx*);
dcmplx* FFT_get_twiddle_factors(int);

// 
double parMapping(double, double, double);

// characteristic related functions
dcmplx charFuncOfLogOfStock_Generic(dcmplx&, double, double, double, double, double, double , double);

// pricing function
dcmplx optModifiedCFunc(dcmplx&, double, double, double, double, double, double, double, double, charFuncOfLogOfStock);
void optPriceFFT(double, double, double, double, double, double, double, double, double, int, charFuncOfLogOfStock, double*, double*); 

// misc
double interpolate(double, double, double, double, double);
void printprice(double*, double*, double*, int);
void getPrice(double *price, double *strike, double *k , double*p, int N);

//---------------------------------------------------------------
// N must be a power of 2 
//---------------------------------------------------------------
dcmplx* FFT_simple(dcmplx* x, int N) 
{
	dcmplx* out = new dcmplx [N]; 
	dcmplx* scratch = new dcmplx [N];
	dcmplx* twiddles = FFT_get_twiddle_factors(N);

	FFT_calculate(x, N, 1, out, scratch, twiddles);

	delete [] twiddles;
	delete [] scratch;
	return out;
}

//---------------------------------------------------------------
dcmplx* IFFT_simple(dcmplx* x, int N) 
{
	dcmplx* out = new dcmplx [N];
	dcmplx* scratch = new dcmplx [N];
	dcmplx* twiddles = FFT_get_twiddle_factors(N);

	FFT_calculate(x, N, 1, out, scratch, twiddles);

	delete [] twiddles;
	delete [] scratch;

	// Calculate IFFT via reciprocity property of DFT. 
	int N2 = N/2;
	double tmp0, tmp1;
	out[0]   = dcmplx(real(out[0])/N, imag(out[0])/N);
	out[N2]  = dcmplx(real(out[N2])/N, imag(out[N2])/N);

	for(int i=1; i<N2; i++) {
		tmp0 = real(out[i])/N;      
		tmp1 = imag(out[i])/N;
		out[i] = dcmplx(real(out[N-i])/N, imag(out[N-i])/N);
		out[N-i] = dcmplx(tmp0, tmp1);
	}
	return out;
}


//---------------------------------------------------------------
void FFT_calculate(dcmplx* x, int N, int skip, dcmplx* X, dcmplx* D, dcmplx* twiddles) {
	dcmplx * E = D + N/2;
	int k;

	if (N == 1) {
		X[0] = x[0];
		return;
	}

	// use X as a scratch buffer 
	FFT_calculate(x, N/2, skip*2, E, X, twiddles);
	FFT_calculate(x + skip, N/2, skip*2, D, X, twiddles);

	for(k = 0; k < N/2; k++) {
		D[k] = twiddles[k*skip] * D[k]; 
	}

	for(k = 0; k < N/2; k++) {
		X[k]       = E[k] + D[k];
		X[k + N/2] = E[k] - D[k];
	}
}


//---------------------------------------------------------------
dcmplx* FFT_get_twiddle_factors(int N) {
	dcmplx* twiddles = new dcmplx[N/2];
	int k;
	for (k = 0; k != N/2; ++k) {
		twiddles[k] = exp(dcmplx(0, -2.0*PI*k/N));
	}
	return twiddles;
}


//---------------------------------------------------------------
dcmplx charFuncOfLogOfStock_Generic(dcmplx& u, double s0, double r, double q, double t, double sigma, double v, double theta)
{
	
	// CF of GBM
	//dcmplx a(0.0, log(s0)+(r-q-sigma*sigma/2.0)*t);
	//dcmplx b(0.5*sigma*sigma*t, 0.0);
	//dcmplx c = a*u - b*u*u;
	//return exp(c);


	// model parameter

	//double v = 0.5;
	//double theta = -0.25;

	dcmplx IC(0.0, 1.0);

	// CF of Variance Gamma
	dcmplx a =  IC*u*(log(s0)+(r-q+1.0/v*log(1.0-sigma*sigma*v/2.0-theta*v))*t);
	dcmplx b = 1.0/(1.0-IC*u*theta*v+sigma*sigma*u*u*v/2.0);
	dcmplx c = pow(b, t/v);

	return exp(a)*c;


}

// Periodic Linear Extension
double parMapping(double x, double c , double d)
{
	double y;
	
	if ((x>=c) && (x<=d)){
        y = x;
	}
    else{
		double range;
		int n;
        range = d-c;
        n = floor((x-c)/range);
        if (n%2 == 0){
            y = x - n*range;
		}
        else{
            y = d + n*range - (x-c);
		}
    }
	return y;
}



//---------------------------------------------------------------
dcmplx optModifiedCFunc(dcmplx& v, double alpha, double s0, double r, double q, double t, double sig, double nu, double th,
	charFuncOfLogOfStock logCF)
{
	dcmplx IC(0.0, 1.0);
	dcmplx u = v - (alpha+1.0)*IC;
	double u1 = exp(-r*t);
	dcmplx u2 = (*logCF)(u, s0, r, q, t, sig, nu, th);
	dcmplx u3 = (alpha+IC*v) * (alpha+IC*v+1.0);

	return (u1*u2/u3);
}


//---------------------------------------------------------------
void optPriceFFT(double alpha, double s0, double r, double q, double t, double eta, double sig, double nu, double th, int N, charFuncOfLogOfStock logCF, 
	double* strike, double* price)
{
	double lambda = 2.0*PI/(N*eta);
	double b      = log(s0) -  0.5*N*lambda;
	dcmplx *fftin = new dcmplx[N];   

	for (int i = 0; i<N; ++i) {
		double j  = i + 1.0;
		double vj_re = eta * (j - 1.0);
		double wj = eta/3.*(3. + pow(-1., j));
		if (i==0) wj = eta/3.;

		dcmplx vj = dcmplx(vj_re, 0.0);
		dcmplx zz1 = optModifiedCFunc(vj, alpha, s0, r, q, t, sig, nu, th, logCF);
		dcmplx IC(0.0, -1.0);

		dcmplx fac = exp(IC*b*vj)*wj;
		fftin[i] = fac * zz1;
	}

	dcmplx *fftout = FFT_simple(fftin, N);

	for (int i=0; i<N; ++i) {
		double k = b + lambda * i;
		strike[i] = exp(k);
		price[i] = exp(-alpha*k)/PI * fftout[i].real(); 
	}
	delete [] fftin;
	delete [] fftout;
}


//---------------------------------------------------------------
double interpolate(double x1, double x2, double y1, double y2, double x)
{
	double y = y1 + (x-x1)/(x2-x1)*(y2-y1);
	return y;
}


//--------------------------------------------------
void printprice(double* price, double* strike, double*k ,int N)
{
	int j=0;
	for (int i=0; i<N; ++i) {
		if ((strike[i] < k[j]) && (strike[i+1] >= k[j])) {
			printf("strike=%7.2f, price=%6.4f\n", k[j], interpolate(strike[i], strike[i+1], price[i], price[i+1], k[j]));
			++j;
		}
	}
}

void getPrice(double *price, double *strike, double *k , double*p, int N)
{
	int j=0;
	for (int i=0; i<N; ++i) {
		if ((strike[i] < k[j]) && (strike[i+1] >= k[j])) {
			p[j] = interpolate(strike[i], strike[i+1], price[i], price[i+1], k[j]);
			++j;
		}
	}
}



double objFunc1(vector<double> x){
	
	double alpha = 1.5;
	double eta = 0.25;

	double s0 = 200;
	double r = 0.0075;
	double q = 0.0175;
	double t = 0.25;

	int pow2 = 11;
	int N = pow(2,pow2);

	double rms = 0.0;

	double *strike = new double [N]; // N strikes
	double *price  = new double [N]; // N option prices

	int numOfInstruments = 11;

	double *k        = new double [numOfInstruments]; // numOfInstruments strikes
	double *p        = new double [numOfInstruments]; // numOfInstruments option prices
	double *pMarket  = new double [numOfInstruments]; // numOfInstruments option prices

	k[0]  = 175.0;
	k[1]  = 180.5;
	k[2]  = 185.0;
	k[3]  = 190.0;
	k[4]  = 195.0;
	k[5]  = 200.0;
	k[6]  = 205.0;
	k[7]  = 210.0;
	k[8]  = 215.0;
	k[9]  = 220.5;
	k[10] = 225.0;

	// FFT
	double gbmsigma = 0.2;
	//printf ("FFT\nGBM\n");

	/*
	pMarket[0] = 30.250;
	pMarket[1] = 26.290;
	pMarket[2] = 22.366;
	pMarket[3] = 18.602;
	pMarket[4] = 15.032;
	pMarket[5] = 11.700;
	pMarket[6] =  8.6786;
	pMarket[7] =  6.1243;
	pMarket[8] =  4.5823;
	pMarket[9] =  3.6004;
	pMarket[10] = 2.8859;
	*/
	
	// Black-Merton-Scholes Prices
	pMarket[0]  = 30.1848;
	pMarket[1]  = 26.4377;
	pMarket[2]  = 23.5929;
	pMarket[3]  = 20.6822;
	pMarket[4]  = 18.0304;
	pMarket[5]  = 15.6335;
	pMarket[6]  = 13.4836;
	pMarket[7]  = 11.5696;
	pMarket[8]  =  9.8799;
	pMarket[9]  =  8.25523;
	pMarket[10] =  7.0983;

	/*
	pMarket[0] = 29.787;
	pMarket[1] = 26.085;
	pMarket[2] = 22.635;
	pMarket[3] = 19.470;
	pMarket[4] = 16.626;
	pMarket[5] = 14.134;
	pMarket[6] = 12.008;
	pMarket[7] = 10.217;
	pMarket[8] =  8.7094;
	pMarket[9] =  7.4414;
	pMarket[10] = 6.3735;
	*/	

	/*
	pMarket[0]  = 31.776;
	pMarket[1]  = 27.700;
	pMarket[2]  = 23.728;
	pMarket[3]  = 19.875;
	pMarket[4]  = 16.158;
	pMarket[5]  = 12.602;
	pMarket[6]  =  9.2386;
	pMarket[7]  =  6.118;
	pMarket[8]  =  3.3262;
	pMarket[9]  =  1.0906;
	pMarket[10] = 0.404812;
	*/

	double sig = parMapping(x[0],  0.0, 1.0);
	double nu  = parMapping(x[1],  0.0, 0.9);
	double th  = parMapping(x[2], -0.9, 0.0);

	optPriceFFT(alpha, s0, r, q, t, eta, sig, nu, th, N, &charFuncOfLogOfStock_Generic, strike, price);
	getPrice(price, strike, k , p, N);

	for (int i1=0; i1<numOfInstruments; ++i1){
		rms = rms + (pMarket[i1]-p[i1])*(pMarket[i1]-p[i1]);
		//rms = rms + 1.0*(pMarket[i1]-p[i1])*(pMarket[i1]-p[i1]);
	}

        rms = sqrt(rms);

	delete [] k;
	delete [] p;
	delete [] pMarket;

	delete [] strike;
	delete [] price;

	return rms;
}



template<class Con>
void printcon(const Con& c){
	std::cout.precision(8);
	cout << "results are:";
	copy( c.begin(), c.end(), ostream_iterator<typename Con::value_type>(cout, "  ") );
	cout << endl;
}

//---------------------------------------------------------------
int main(int argc, char** argv) 
{

	using BT::Simplex;

	//initial guessing value for the objective function
	vector<double> init;
	init.push_back(9.0);
	init.push_back(3.0);
	init.push_back(-4.0);

	//initial trial simplex
	//double a0[] = {-1.5, -1};
	//double a1[] = {-2, -2};
	//double a2[] = { 2.5, 1.5};

	double a0[] = {-2.5, -0.5};
	double a1[] = {-3, -2};
	double a2[] = { 3.5, 1.5};

	vector<vector<double> > simplex;
	simplex.push_back( vector<double>(a0, a0+2) );
	simplex.push_back( vector<double>(a1, a1+2) );
	simplex.push_back( vector<double>(a2, a2+2) );

	//optimizating ...
	//printcon is a function printing container values

	cout <<"objFunc1 achieves minimum at:" << endl;
	vector<double> optimalParams;
	optimalParams = Simplex(objFunc1, init, 1e-8);
	optimalParams[0] = parMapping(optimalParams[0],  0.0, 1.0);
	optimalParams[1] = parMapping(optimalParams[1],  0.0, 0.9);
	optimalParams[2] = parMapping(optimalParams[2], -0.9, 0.0);
	printcon(optimalParams);
	cout << endl;


}
