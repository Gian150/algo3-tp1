CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
OFLAGS=-c -g -ggdb -Wall -std=c++11
CFLAGS=-g -ggdb -Wall -std=c++11

SOURCESE1=numberPainter.o Ej1.o
SOURCESE2=numberPainter.o Ej2.o 
SOURCESE3=numberPainter.o Ej3.o
#SOURCESTIEMPOS=numberPainter.o tiempos.o

tp:
	make ej1
	make ej2
	make ej3
#	make tiempos

ej1: $(SOURCESE1)
	$(CC) $(CFLAGS) $(SOURCESE1) -o Ej1

ej2: $(SOURCESE2)
	$(CC) $(CFLAGS) $(SOURCESE2) -o Ej2

ej3: $(SOURCESE3)
	$(CC) $(CFLAGS) $(SOURCESE3) -o Ej3
	
#tiempos: $(SOURCETIEMPOS)
#	$(CC) $(CFLAGS) $(SOURCESE3) -o tiempos

*.o: *.cpp *.hpp
	$(CC) $(OFLAGS) *.cpp

clean:
	rm *.o
	rm Ej1
	rm Ej2
	rm Ej3
	rm tiempos