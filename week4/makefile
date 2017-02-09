CC = g++
CFLAGS = -c -g -O
LIBS = -ldl 

PROG_OBJS = builder.o lecture4_exampleMemoryCorruption.o
//PROG_OBJS = builder.o lecture4_exampleArrays.o
//PROG_OBJS = builder.o lecture4_examplePointers.o
PROG_OBJS = builder.o lecture4_exampleDynamicMemory.o
//PROG_OBJS = builder.o lecture4_exampleStrings.o

TGTS = example.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
