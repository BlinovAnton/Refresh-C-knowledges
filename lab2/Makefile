.PHONY: all all_debug clean clean_all

CC = gcc
FLAGS = -Werror -Wall
LDIR = Lib
SDIR = Src
BIN = prog

all: main.o list.o menu.o
	$(CC) $(FLAGS) -o $(BIN) $(LDIR)/menu.o $(LDIR)/list.o $(SDIR)/main.o

all_debug:
	make -C $(LDIR) debug
	make -C $(SDIR) debug
	$(CC) $(FLAGS) -g -O0 -o $(BIN) $(LDIR)/menu.o $(LDIR)/list.o $(SDIR)/main.o

menu.o:
	make -C $(LDIR) $@

list.o:
	make -C $(LDIR) $@

main.o:
	make -C $(SDIR) $@

clean:
	rm -f $(BIN)

clean_all: clean
	make -C $(SDIR) clean
	make -C $(LDIR) clean_all
