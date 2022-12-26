#include <stdio.h>
#include "lib.h"

int main()
{
    int *arr = NULL;
    int min_val = 100;
    int max_val = 200;
    int num_of_vals = 20;

    generate_rand_array(&arr, min_val, max_val, num_of_vals);
    if (arr)
	free(arr);
    return 0;
}