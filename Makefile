CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
OFLAGS= -c -g -ggdb -Wall -std=c++11
CFLAGS = -g -ggdb -Wall -std=c++11

SOURCES = main.o numberPainter.o

TP: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o tp


*.o: *.cpp
	$(CC) $(OFLAGS) *.cpp

clean:
	rm -f *.o
	rm -f Ej1
	rm -f testsMain
