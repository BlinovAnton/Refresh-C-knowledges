.PHONY: all lib.o main.o allg clean clean_all

CC = gcc
FLAGS = -Werror -Wall
LDIR = Lib
SDIR = Src
BIN = prog

#не получается с vpath у меня чё-то...
#vpath %.o $(LDIR):$(SDIR)

all: lib.o main.o
	$(CC) $(FLAGS) $(LDIR)/lib.o $(SDIR)/main.o -o $(BIN)

allg: lib.o main.o
	$(CC) $(FLAGS) -g -O0 $(LDIR)/lib.o $(SDIR)/main.o -o $(BIN)
	valgrind -v ./$(BIN)

lib.o:
	make -C $(LDIR)

main.o:
	make -C $(SDIR)

clean:
	rm -f $(BIN)

clean_all:
	make -C $(LDIR) clean
	make -C $(SDIR) clean
	make clean