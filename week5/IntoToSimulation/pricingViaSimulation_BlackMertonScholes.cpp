#include "functions.h"

#include <iostream>
#include <iomanip>
#include <ios>
#include <math.h>  /* log & exp */
#include <stdio.h>
#include <sys/time.h> 
#include <cstdlib>

using namespace std;

// Pricing Back-Nerton-Scholes via Simulation

// Vanillla (Call/Put) , Barriers (UOC, UOP, DOC, DOP) & etc
// 

int main(int argc, char*argv[])
{

	long idum = atol(argv[1]);

	double   sigma=0.20;

	double   maturity = 0.25;
	double   s0 = 1975.0;
	double   strike = 1800.0;
	double   rfr=0.005, div=0.015;

	int nSimulationPaths = 4000000;
	int nTimeSteps = 30;

	double dt = maturity/nTimeSteps;

	double drift = (rfr-div-sigma*sigma/2.0)*dt;
	double payoff1 = 0.0;
	double put;

	int iI, jJ;
	double u1, z1;
	double fd1, feed1;


	for (jJ = 0; jJ<nSimulationPaths; jJ++){

		fd1 = log(s0);

		for (iI = 0; iI<nTimeSteps; iI++){

			u1 = ran2_mod(&idum);
			z1 = invertingStandardNormalDistribution(u1);
			feed1 = sigma*sqrt(dt)*z1;
			fd1 = fd1+feed1+drift;
}

			if (exp(fd1) > strike){
				payoff1 = payoff1 - (strike-exp(fd1));
			}
}
	put = exp(-rfr*maturity)*payoff1/nSimulationPaths;
	cout << "European Call premium: " << put << endl;

}
