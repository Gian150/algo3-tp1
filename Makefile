CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
OFLAGS= -c -g -ggdb -Wall -std=c++11
CFLAGS = -g -ggdb -Wall -std=c++11

SOURCESE1 = Ej1.o numberPainter.o
SOURCESE2 = Ej2.o numberPainter.o
SOURCESE3 = Ej3.o numberPainter.o

tp:
	make ej1
	make ej2
	make ej3

ej1: $(SOURCESE1)
	$(CC) $(CFLAGS) $(SOURCESE1) -o Ej1

ej2: $(SOURCESE2)
	$(CC) $(CFLAGS) $(SOURCESE2) -o Ej2

ej3: $(SOURCESE3)
	$(CC) $(CFLAGS) $(SOURCESE3) -o Ej3

*.o: *.cpp
	$(CC) $(OFLAGS) *.cpp

clean:
	rm *.o
	rm Ej1
	rm Ej2
	rm Ej3