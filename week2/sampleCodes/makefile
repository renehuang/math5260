CC = g++
LD = g++
CFLAGS = -c -g -O
LIBS = -ldl 

PROG_OBJS = lecture2_firstExample1a.o

TGTS = example.out

$(TGTS):$(PROG_OBJS)
	$(CC) $(LFLAGS) $(PROG_OBJS) $(LIBS) -o $(TGTS)
 
.SUFFIXES:.cpp
 
.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(TGTS)
	rm -f *.o
