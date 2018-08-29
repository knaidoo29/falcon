CC=g++
CFLAGS=-c -fPIC

all: lib/libfalcon.a

lib/libfalcon.a: src/indexing.o src/randoms.o src/sort.o
	 ar cr lib/libfalcon.a src/indexing.o src/randoms.o src/sort.o

src/indexing.o: src/indexing.cpp
	 $(CC) $(CFLAGS) src/indexing.cpp -o src/indexing.o

src/randoms.o: src/randoms.cpp
	 $(CC) $(CFLAGS) src/randoms.cpp -o src/randoms.o

src/sort.o: src/sort.cpp
	 $(CC) $(CFLAGS) src/sort.cpp -o src/sort.o

clean:
	 rm src/*.o
	 rm lib/*.a
	 rm .DS_Store
