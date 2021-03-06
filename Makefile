CC = g++
CFLAGS = -c

INC =
LIBS =

OBJS = src/indexing.o src/randoms.o src/sort.o src/read.o src/write.o

all: lib/libfalcon.a

lib/libfalcon.a: $(OBJS)
	 ar cr lib/libfalcon.a $(OBJS)

.cpp.o:
	 $(CC) $(CFLAGS) $(INC) $< $(LIBS) -o $@

clean:
	 rm src/*.o*
	 rm lib/*.a*
	 rm .DS_Store
