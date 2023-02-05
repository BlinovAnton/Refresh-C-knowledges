/********************************************************/
/* Need find maximum between number of positive element */
/*     and number of negative elements at array         */
/********************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "issue327_1_lib.h"

int main(int argc, char **argv)
{
    int i = 0;
    int algo = 0;
    __uint64_t counter[CT_NUM] = { 0 };
    __uint64_t max = 0;
    int *arr = NULL;
    __uint64_t size = 0;
    algo_arg_t algo_arg = { 0 };
    pid_t pid[NUM_OF_ALGOS] = { 0 };
    int wait_status[NUM_OF_ALGOS] = { 0 };
    char *stack[NUM_OF_ALGOS] = { 0 };
    char *stack_top[NUM_OF_ALGOS] = { 0 };
    __uint64_t (*algos_arr[NUM_OF_ALGOS])(void *) =
    {
        get_counter_v0,
        get_counter_v1,
        get_counter_v2,
        get_counter_v3
    };

    /* BUG: name of file is argv[0]            */
    /* but in some cases name out of arguments */
    if (argc < 2 || argc > 3)
    {
	printf("Usage: ./prog [algo] (n)\n");
	return 0;
    }
    size = argc == 3 ? atoi(argv[2]) : DEF_SIZE;
    algo = atoi(argv[1]);

    srand(time(NULL));
    if (generate_rand_array(
        (const int **)&arr, (__uint32_t)size, DEF_MIN, DEF_MAX, ADD_NEG) == EXIT_FAILURE)
    {
	printf("Allocation fauled\n");
	return 0;
    }
    qsort(arr, size, sizeof(int), qsort_non_decreased);

#if DEBUG
    printf("Genered arr:\n");
    for (i = 0; i < size; i++)
	printf("%d ", arr[i]);
    printf("\n");
#endif

    algo_arg.arr = arr;
    algo_arg.size = size;
    algo_arg.counter = counter;
    algo_arg.is_print_res = 1; /* print result and timer stats */

    if (algo < NUM_OF_ALGOS)
    {
	max = algos_arr[algo](&algo_arg);
    }
    else
    {
	/* I used 'clone' like at example from 'man 2 clone' */
	for (i = 0; i < NUM_OF_ALGOS; i++)
	{
	    stack[i] = (char *)malloc(STACK_SIZE);
	    if (!(stack[i]))
	    {
		printf("%d: Allocation failed!\n", __LINE__);
		goto exit;
	    }
	    stack_top[i] = stack[i] + STACK_SIZE; /* Assume stack grows downward */
	}

	for (i = 0; i < NUM_OF_ALGOS; i++)
	{
	    pid[i] = clone((int (*)(void *))algos_arr[i], stack_top[i], CLONE_FLAGS, &algo_arg);
	    if (pid[i] == -1)
	    {
		perror("clone(#%d) failed!");
		goto exit;
	    }
#if DEBUG
	    else
		printf("pid[%d] = %d succesfully executed\n", i, pid[i]);
#endif
	}
	printf("Waiting all pids...\n");
	for (i = 0; i < NUM_OF_ALGOS; i++)
	{
	    if (waitpid(pid[i], &wait_status[i], 0) == -1)
		printf("waitpid(#%d) failed!\n", i);
#if DEBUG
	    else
		printf("pid[%d] = %d succesfully terminated (%d)\n", i, pid[i], wait_status[i]);
	    printf("%d %d\n", WIFEXITED(wait_status[i]), WEXITSTATUS(wait_status[i]));
#endif
	    /*if (WIFEXITED(wait_status[i]))
		printf("Answer: %lld\n", WEXITSTATUS(wait_status[i]));*/
	}
    }

    for (i = 0; i < NUM_OF_ALGOS; i++)
	printf("%p\n", stack[i]);
    printf("Answer: %lld\n", max);

exit:
    free(arr);
    return 0;
}
