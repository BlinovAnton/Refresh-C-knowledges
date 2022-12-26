.PHONY: all clean

IPATH = "../Inc"
SRC=lib.c
CC=gcc
FLAGS=-Werror -Wall -c

lib.o: $(SRC)
	$(CC) $(FLAGS) -I $(IPATH) -o $@ $^

clean:
#	rm -f $(ls | grep -v *.c | grep -v Makefile)
	rm -f *.o