CC=g++

FALCON_ROOT=/Users/krishna/Research/github/falcon
FALCON_LIB=$(FALCON_ROOT)/lib
FALCON_INC=$(FALCON_ROOT)/include
LFALCON=-lfalcon

all:
	g++ -I$(FALCON_INC) -L$(FALCON_LIB) test1.cpp $(LFALCON) -o test1.o
	g++ -I$(FALCON_INC) -L$(FALCON_LIB) test2.cpp $(LFALCON) -o test2.o

clean:
	 rm $(EXEC).o
	 rm .DS_Store
