CC=gcc
CFLAGS=-Wall -Werror -ggdb3 -std=gnu99 -pedantic $(OTHERFLAGS)
poker: cards.o  deck.o  eval.o  future.o  input.o  main.o
		gcc -o $@ $(CFLAGS) $^
clean:
		rm -rf *.o poker *~

cards.o: cards.h
deck.o: deck.h
eval.o: eval.h
future.o: future.h
input.i: input.h
main.o: input.h
main.o: future.h
main.o: eval.h
main.o: deck.h
main.o: cards.h
