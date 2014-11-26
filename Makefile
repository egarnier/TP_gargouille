
all: ppm

ppm: ppm.cpp picture.o
	g++ -Wall -o ppm ppm.cpp picture.o

picture.o: picture.h picture.cpp
	g++ -Wall -c -o picture.o picture.cpp

clean :
	rm *.o

mrproper: clean
	rm ppm

