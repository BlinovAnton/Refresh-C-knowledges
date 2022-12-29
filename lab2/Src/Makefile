.PHONY: all clean debug

CC = gcc
FLAGS = -Werror -Wall -c
IPATH = ../Inc
LPATH = ../Lib

#Do I need list.o and menu.o to compiling main.o
main.o: main.c
	$(CC) $(FLAGS) -o $@ -I$(IPATH) $^

debug: main.c
	$(CC) $(FLAGS) -g -O0 -o main.o -I$(IPATH) $^

clean:
	rm -f *.o
