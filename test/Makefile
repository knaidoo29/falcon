CC = g++

OPTIMIZE =

FALCON_INC = -I/Users/krishna/Research/github/falcon/include
FALCON_LIB = -L/Users/krishna/Research/github/falcon/lib -lfalcon

FFTW3_INC = -I/Users/krishna/Research/compiled/fftw3/include
FFTW3_LIB = -L/Users/krishna/Research/compiled/fftw3/lib -lfftw3

INC = $(FALCON_INC) $(FFTW3_INC)
LIBS = -lm $(FALCON_LIB) $(FFTW3_LIB)
CFLAGS = $(OPTIMIZE)

OBJS = test1.o test2.o test3.o test4.o test5.o test6.o

all: $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) $(INC) $< $(LIBS) -o $@

clean:
	rm -r *.o*
	rm -r *.txt
	rm .DS_Store
