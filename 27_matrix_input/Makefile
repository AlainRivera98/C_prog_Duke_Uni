CFLAGS=-ggdb3 -pedantic -std=gnu99 -Wall -Werror

rotateMatrix: rotateMatrix.o rotate.o
	gcc -o rotateMatrix rotateMatrix.o rotate.o
rotateMatrix.o: rotateMatrix.c
	gcc $(CFLAGS) -c rotateMatrix.c
rotate.o: rotate.c
	gcc $(CFLAGS) -c rotate.c
clean:
	rm rotateMatrix *~ *#
