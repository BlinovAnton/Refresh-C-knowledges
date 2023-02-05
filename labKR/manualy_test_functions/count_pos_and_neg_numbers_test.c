#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "../common_functions.h"

#define SIZE 100
#define BIN_SEARCH_STEP 2

int counter(int *, __uint32_t);
int find_first_positive(int *, int, int);
int find_last_negative(int *, int, int);

int main()
{
    int *arr = NULL;

    srand(time(NULL));
    generate_rand_array((const int **)&arr, SIZE, 0, 100, 1);
    if (!arr) return 0;
    qsort(arr, SIZE, sizeof(int), qsort_non_decreased);
    print_arr(arr, SIZE);
    printf("%d\n", counter(arr, SIZE));

    free(arr);
    return 0;
}

int counter(int *arr, __uint32_t size)
{
    int i = 0;
    int j = 0;
    int counter_of_pos = 0;
    int counter_of_neg = 0;

    i = find_first_positive(arr, 0, size - 1);
    counter_of_pos = i < 0 ? 0 : size - i;

    j = find_last_negative(arr, 0, i < 0 ? size - 1 : i - 1);
    counter_of_neg = j < 0 ? 0 : j + 1;

    printf("result: %d %d\n", counter_of_pos, counter_of_neg);
    return max(counter_of_pos, counter_of_neg);
}

int find_first_positive(int *arr, int start, int end)
{
    int i = 0;

    if (arr[end] <= 0)
	return -1;

    while (start < end)
    {
	i = (start + end) / BIN_SEARCH_STEP;
#if DEBUG
	printf("%4d->%3d; range %2d..%d\n", i, arr[i], start, end);
#endif
	if (arr[i] > 0)
	    end = i;
	else
	    start = i + 1;
    }
    if (arr[end] <= 0)
	return -1;

    return end;
}

int find_last_negative(int *arr, int start, int end)
{
    int i = 0;

    if (arr[start] >= 0)
	return -1;

    while (start < end)
    {
	i = (start + end) / BIN_SEARCH_STEP;
#if DEBUG
	printf("%4d->%3d; range %2d..%d\n", i, arr[i], start, end);
#endif
	if (arr[i] < 0)
	    start = i + 1;
	else
	    end = i;
    }

    if (arr[end] == 0)
	return end - 1;

    return end;
}