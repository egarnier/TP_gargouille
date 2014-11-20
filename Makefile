
all: ppm

ppm: ppm.c picture.o
	gcc -Wall -o ppm ppm.c picture.o

picture.o: picture.h picture.c
	gcc -Wall -c -o picture.o picture.c

clean :
	rm *.o

mrproper: clean
	rm ppm

