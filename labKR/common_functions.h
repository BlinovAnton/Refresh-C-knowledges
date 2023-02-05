#ifndef __COMMON_FUNCTIONS_H__
#define __COMMON_FUNCTIONS_H__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define max(a, b) (a) > (b) ? (a) : (b)

int generate_rand_array(const int **, int, int, int, int);
double wtime();
int qsort_non_decreased(const void *, const void *);
void print_arr(int *, __uint32_t);

#endif
