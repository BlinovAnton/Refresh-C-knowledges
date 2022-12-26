#include <lib.h>

void generate_rand_array(int **arr, int min, int max, int num)
{
    int i = 0;
    int *t = NULL;
    *arr = (int *)malloc(num * sizeof(int));

    /* t нужен, чтобы не потерять указатель на начало массив           */
    /* arr - указатель на массив, а t указатель на массив, но бегающий */
    t = *arr;

    for (i = 0; i < num; i++, t++)
	*t = min + (int)rand() % max;

}