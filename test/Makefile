CC=g++

FALCON_ROOT=/Users/krishna/Research/github/falcon
FALCON_LIB=$(FALCON_ROOT)/lib
FALCON_INC=$(FALCON_ROOT)/include
LFALCON=-lfalcon

EXEC=main

all:
	g++ -I$(FALCON_INC) -L$(FALCON_LIB) test1.cpp $(LFALCON) -o $(EXEC).o

clean:
	 rm $(EXEC).o
	 rm .DS_Store
