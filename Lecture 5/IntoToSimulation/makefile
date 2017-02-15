CC = g++
LD = g++
CFLAGS = -c -O
LIBS = -ldl

//PROG_OBJS = invertingStandardNormalDistribution.o samplingFromGammaProcess.o ran2_mod.o simulatingVarianceGammaProcess.o
PROG_OBJS = ran2_mod.o invertingStandardNormalDistribution.o pricingViaSimulation_BlackMertonScholes.o
//PROG_OBJS = ran2_mod.o invertingStandardNormal.o samplingFromGammaProcess.o pricingViaSimluation_VarianceGamma.o

TGTS = simulationExample.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o

