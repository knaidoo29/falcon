CC = g++

OPTIMIZE = -g

FALCON_INC = -I/Users/krishna/Research/github/falcon/include
FALCON_LIB = -L/Users/krishna/Research/github/falcon/lib -lfalcon

INC = $(FALCON_INC)
LIBS = -lm $(FALCON_LIB)
CFLAGS = $(OPTIMIZE)

OBJS = test1.o test2.o test3.o test4.o

all: $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) $(INC) $< $(LIBS) -o $@

clean:
	rm -r *.o*
	rm -r *.txt
	rm .DS_Store
