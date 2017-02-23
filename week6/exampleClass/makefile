CC = g++
LD = g++
CFLAGS = -c -g -O
LIBS = -ldl

PROG_OBJS = lecture6_exampleClass1.o
//PROG_OBJS = lecture6_exampleClassDynamicAllocation1a.o
//PROG_OBJS = lecture6_exampleClassDynamicAllocation1b.o

TGTS = exampleClass.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
