CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
PROGRAM=test_future

$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~

cards.o: cards.h
deck.o: deck.h
eval.o: eval.h
future.o: future.h
input.o: input.h
main.o: input.h
main.o: future.h
main.o: eval.h
main.o: deck.h
main.o: cards.h
