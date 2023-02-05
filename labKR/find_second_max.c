/*******************************************************/
/* Programm find in array second max element           */
/* Example: arr = 1, 2, 3, 10, 4                       */
/*          so max elem is 10 and second max elem is 4 */
/*                                                     */
/* Why not qsort and print arr[1]? Because it is part  */
/* of bet with friend                                  */
/*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common_functions.h"

#define MAX_LEN            100
#define DYNAMIC_ARR        1
#define DEFAULT_SIZE       10
#define DEFAULT_RAND_MAX   50
#define DEFAULT_RAND_MIN   1

int main (int argc, char *argv[])
{
    if (argc != 1 && argc != 3)
    {
	printf("Usage: ./prog OR ./prog 'size' 'rand_board'\n");
	return 0;
    }

    int i                  = 0;
    int max1               = 0;
    int max2               = 0;
    int size               = 0;
    int rand_board         = 0;
    char max2_str[MAX_LEN] = {};

    size       = argc == 3 ? atoi(argv[1]) : DEFAULT_SIZE;
    rand_board = argc == 3 ? atoi(argv[2]) : DEFAULT_RAND_MAX;
    if (!size)
    {
	printf("Error: Array size is 0\n");
	return -1;
    }
    if (!rand_board)
    {
	printf("Math error: Rand board is zero, math\n");
	return -1;
    }

#if DYNAMIC_ARR
    int *arr = NULL;
    if (generate_rand_array(
        (const int **)&arr, size, DEFAULT_RAND_MIN, rand_board, 0 /*only unsigned vals*/)
        == EXIT_FAILURE)
    {
	printf("Error: alloc failed");
	return -1;
    }
#else
    /* Static case for manual self-test */
    int arr[size] = { 10, 9, 1, 2 };
#endif

    /* Find 2-nd max */
    max1 = arr[0];
    max2 = arr[1];
    for (i = 1; i < size; i++)
    {
	if (arr[i] > max1)
	{
	    max2 = max1;
	    max1 = arr[i];
	    continue;
	}
	if (arr[i] > max2)
	    max2 = arr[i];
    }

    printf("Arr:");
    for (i = 0; i < size; i++)
	printf(" %d", arr[i]);
    snprintf(max2_str, MAX_LEN, "%d", max2);
    printf("\nMax1 = %d\nMax2 = %s\n", max1, size == 1 ? "undefined" : max2_str);

#if DYNAMIC_ARR
    free(arr);
#endif

    return 0;
}