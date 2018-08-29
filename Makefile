CC=g++
CFLAGS=-c -fPIC

all: lib/libfalcon.a

lib/libfalcon.a: src/hello.o
	 ar cr lib/libfalcon.a src/hello.o

src/hello.o: src/hello.cpp
	 $(CC) $(CFLAGS) src/hello.cpp -o src/hello.o

clean:
	 rm src/*.o
	 rm lib/*.a
	 rm .DS_Store
