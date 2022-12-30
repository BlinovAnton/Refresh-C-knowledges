.PHONY: all clean

CC = gcc
FLAGS = -Werror -Wall
IPATH = ../Inc
OBJ = list.o menu.o

list.o: list.c
	$(CC) $(FLAGS) -c -I$(IPATH) -o $@ $^

list.i: list.c
	$(CC) $(FLAGS) -E -I$(IPATH) -o $@ $^

list.s: list.c
	$(CC) $(FLAGS) -S -I$(IPATH) -o $@ $^

#Why I don't need list.o compiling menu.o ?
menu.o:  menu.c
	$(CC) $(FLAGS) -c -I$(IPATH) -o $@ $^

all: $(OBJ)
	

debug: list.c menu.c
	$(CC) $(FLAGS) -DDEBUG -g -O0 -c -I$(IPATH) -o list.o list.c
	$(CC) $(FLAGS) -DDEBUG -g -O0 -c -I$(IPATH) -o menu.o menu.c

clean_all:
	rm -f *.o *.i *.s
