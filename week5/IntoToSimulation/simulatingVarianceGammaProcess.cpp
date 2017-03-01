#include "functions.h"

#include <iostream>
#include <iomanip>
#include <ios>
#include <math.h>  /* log & exp */
#include <stdio.h>
#include <sys/time.h> 
#include <cstdlib>

using namespace std;

int main(int argc, char*argv[])
{

	long idum = atol(argv[1]);

	double   sigma=0.20, nu=0.17, theta=-0.15;

	double   maturity = 0.5;
	double   s0 = 1800.0;
	double   strike = 1650.0;
	double   rfr=0.005, div=0.0135;

	int nSimulationPaths = 400000;
	int nTimeSteps = 30;

	double dt = maturity/nTimeSteps;

	double drift = (rfr-div)*dt + (dt/nu)*log(1.0-theta*nu-sigma*sigma*nu/2.0);
	double payoff1 = 0.0;
	double payoff2 = 0.0;
	double price1, price2, avgPrice;
	double downAndOutPut1, downAndOutPut2;

	int iI, jJ;
	double g1, u1, z1;
	double fd1, feed1;
	double fd2, feed2;
	int flag1 = 0;
	int flag2 = 0;


	for (jJ = 0; jJ<nSimulationPaths; jJ++){

		fd1 = log(s0);
		fd2 = log(s0);
		flag1 = 0;
		flag2 = 0;

		for (iI = 0; iI<nTimeSteps; iI++){

			g1 = samplingFromGammaProcess(dt/nu, nu, &idum);
			u1 = ran2_mod(&idum);
			z1 = invertingStandardNormalDistribution(u1);
			//cout << g1 << " " << u1 << " " << z1 << endl;
			feed1 = theta*g1 + sigma*sqrt(g1)*z1;
			fd1 = fd1+feed1+drift;
			//
			feed2 = theta*g1 - sigma*sqrt(g1)*z1;
			fd2 = fd2+feed2+drift;

			price1 = exp(fd1);
			price2 = exp(fd2);

			//if (price1<=lowBarrier)
				flag1 = 1;

			//if (price2<=lowBarrier)
				flag2 = 1;

		}
		if ((flag1 == 1) || (flag1 == 0)){
			if (price1 < strike){
				payoff1 = payoff1 + (strike-price1);
			}
		}

		if (flag2 == 0){
			if (price2 < strike){
				payoff2 = payoff2 + (strike-price2);
			}
		}
	}

	downAndOutPut1 = exp(-rfr*maturity)*payoff1/nSimulationPaths;
	downAndOutPut2 = exp(-rfr*maturity)*(payoff1+payoff2)/(2.0*nSimulationPaths);
	cout << "Down-and-Out Put (DOP) premium: " << downAndOutPut1 << " " << downAndOutPut2 << endl;

}
