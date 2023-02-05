#include "common_functions.h"

int generate_rand_array(const int **arr, int num, int min, int max, int neg_flag)
{
    /* if "max == 0" then math error cause of "rand() % max" */
    if (!max)
	return EXIT_FAILURE;

    int i = 0;
    int *t = NULL;
    *arr = (int *)malloc(num * sizeof(int));
    if (!*arr)
	return EXIT_FAILURE;

    /* 't' need for not losing addr of '*arr' */
    t = (int *)*arr;

    for (i = 0; i < num; i++, t++)
	*t = (min + (int)rand() % max) * (!neg_flag ? 1 : (rand() % 2 == 0 ? 1 : -1));

    return EXIT_SUCCESS;
}

/*******************************************/
/*            Kurnosov timer               */
/* To calculate durability of section use: */
/*                                         */
/* double t = wtime();                     */
/* *SOME CODE*                             */
/* t = wtime() - t;                        */
/*******************************************/
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int qsort_non_decreased(const void *a, const void *b)
{
    return *(const int *)a > *(const int *)b;
}

void print_arr(int *arr, __uint32_t size)
{
    printf("Arr:\n");
    for (int i = 0; i < size; i++)
	printf("%d ", arr[i]);
    printf("\n");
}
