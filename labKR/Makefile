#.PHONY: find_second_max func_pointers issue327_1 fizzbuzz

CC = gcc
FLAGS = -Werror -Wall -g
COMMON = common_functions.c
BINS = find_second_max func_pointers issue327_1 fizzbuzz
BIN1 = issue327_1
BIN2 = func_pointers

#if file is 'example.c' do 'make example' (without '.c')
%: %.c $(COMMON)
	$(CC) $(FLAGS) -o $@ $^

$(BIN2): $(BIN2).c
	$(CC) $(FLAGS) -o $@ $^

$(BIN1): $(BIN1).c $(COMMON) $(BIN1)_lib.c
	$(CC) $(FLAGS) -D_GNU_SOURCE -o $(BIN1) $^ -pthread

$(BIN1)-debug: $(BIN1).c $(COMMON) $(BIN1)_lib.c
	$(CC) $(FLAGS) -DDEBUG -D_GNU_SOURCE -o $(BIN1) $^ -pthread