#.PHONY: find_second_max func_pointers issue327_1 fizzbuzz

CC = gcc
FLAGS = -Werror -Wall -g
COMMON = ../common_functions.c

#if file is 'example.c' do 'make example' (without '.c')
%: %.c $(COMMON)
	$(CC) $(FLAGS) -o $@ $^

