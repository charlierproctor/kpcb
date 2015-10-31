# compiler flags
CC	= gcc
CFLAGS  = -g3 -std=c99 -pedantic -Wall

# make the play environment
play: play.o hash.o
	${CC} ${CFLAGS} -o $@ $^

# make the test script
test: test.o hash.o
	${CC} ${CFLAGS} -o $@ $^

# dependencies
hash.o: hash.h

# clean out the executables
clean: 
	$(RM) play test *.o
