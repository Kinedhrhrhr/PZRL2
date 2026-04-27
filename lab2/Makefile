.PHONY: clean all

all: Stack.o liststack.o vectorstack.o
	g++ Stack.o liststack.o vectorstack.o -o test -L. -lStackTest

Stack.o: Stack.cpp Stack.h liststack.h vectorstack.h
	g++ -c Stack.cpp -o Stack.o

liststack.o: liststack.cpp liststack.h StackImplementation.h
	g++ -c liststack.cpp -o liststack.o

vectorstack.o: vectorstack.cpp vectorstack.h StackImplementation.h
	g++ -c vectorstack.cpp -o vectorstack.o

clean:
	rm -f Stack.o liststack.o vectorstack.o test
