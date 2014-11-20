
all: ppm

ppm: ppm.c picture.o
	g++ -Wall -o ppm ppm.c picture.o

picture.o: picture.h picture.c
	g++ -Wall -c -o picture.o picture.c

clean :
	rm *.o

mrproper: clean
	rm ppm

