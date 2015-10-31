CC	= gcc
CFLAGS  = -g3 -std=c99 -pedantic -Wall

hash: main.o hash.o
	${CC} ${CFLAGS} -o $@ $^

hash.o: hash.h

clean: 
	$(RM) hash *.o
