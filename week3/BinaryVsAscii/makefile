CC = g++
LD = g++
CFLAGS = -c -g -O
LIBS = -ldl 

PROG_OBJS = rem.o exampleReadingBinaryAscii.o
//PROG_OBJS = rem.o exampleWritingBinaryAscii.o

TGTS = example.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
