.PHONY: all clean

IPATH="../Inc/"
SRC=main.c
CC=gcc
FLAGS=-Werror -Wall -c

main.o: $(SRC)
	$(CC) $(FLAGS) -I$(IPATH) -o $@ $^

clean:
#	rm -f $(ls | grep -v *.c | grep -v Makefile)
	rm -f *.o
