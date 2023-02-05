/*******************************/
/* LeetCode: fizz-buzz problem */
/*******************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **gen_str_arr(int);
void free_str_arr(char **, int);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
	printf("Usage: ./prog [n]\n");
	return 0;
    }

    int i = 0;
    int n = 0;
    char **buf = NULL;

    n = atoi(argv[1]);
    if (n < 1 || n > 1000)
    {
	printf("Constrains: 1 <= n <= 10^4\n");
	return 0;
    }

    buf = gen_str_arr(n);
    if (!buf)
	return 0;

    printf("[");
    for (i = 0; i < n; i++)
    {
	if (buf[i])
	    printf("\"%s\"%s", buf[i], i == n - 1 ? "" : ",");
    }
    printf("]\n");

    free_str_arr(buf, n);
    return 0;
}

char **gen_str_arr(int size)
{
    int i = 0;
    int max_len = 0;
    char **buf = NULL;

    max_len = strlen("FizzBuzz") + 1;
    buf = (char **)malloc(sizeof(char *) * size);
    if (!buf)
	return NULL;

    for (i = 0; i < size; i++)
    {
	buf[i] = (char *)calloc(max_len, sizeof(char));
	if (!buf[i])
	{
	    free_str_arr(buf, i /* as size we use here 'i', not 'size' */);
	    return NULL;
	}

	snprintf(buf[i], max_len, "%s%s",
	         (i + 1) % 3 == 0 ? "Fizz" : "", (i + 1) % 5 == 0 ? "Buzz" : "");
	if (buf[i][0] == '\0')
	    snprintf(buf[i], max_len, "%d", i + 1);
    }

    return buf;
}

void free_str_arr(char **arr, int size)
{
    int i = 0;

    if (arr)
    {
	for (i = 0; i < size; i++)
	    if (arr[i]) free(arr[i]);
	free(arr);
    }
}