#include "issue327_1_lib.h"

inline const char *stringize_CT_TYPE(int ct_type)
{
    return (ct_type >= 0 && ct_type < CT_NUM) ? counter_types_str[ct_type] : "";
}

static void print_res(__uint64_t size, __uint64_t *counter, double t)
{
    int i = 0;
    __uint64_t err_check = 0;

    printf("From array of %lld elements counted:\n", size);
    for (i = 0; i < CT_NUM; err_check += counter[i], i++)
	printf("%lld (%s values)%s ", counter[i],
	        stringize_CT_TYPE(i), i == CT_NUM - 1 ? "" : ",");
    printf("for %.6f sec%s\n", t, err_check == size ? "" : " [Calc error!]");
}

/* size = 2*10^7 for 0,227-0,245 sec */
//__uint64_t get_counter_v0(int *arr, __uint64_t size, __uint64_t *counter, int is_print_res)
__uint64_t get_counter_v0(void *args)
{
    int i = 0;
    double t = 0;

    algo_arg_t *arg = NULL;
    int *arr = NULL;
    __uint64_t size = 0;
    __uint64_t *counter = NULL;
    int is_print_res = 0;

    arg = (algo_arg_t *)args;
    arr = arg->arr;
    size = arg->size;
    counter = arg->counter;
    is_print_res = arg->is_print_res;

    t = wtime();
    for (i = 0; i < arg->size; i++)
    {
	if (arr[i] > 0)
	    counter[CT_POS]++;
	else if (arr[i] < 0)
	    counter[CT_NEG]++;
	else
	    counter[CT_ZER]++;
    }
    t = wtime() - t;

    if (is_print_res)
	print_res(size, counter, t);

    return max(counter[CT_POS], counter[CT_NEG]);
}

/* size = 2*10^7 for 0,169-0,176 */
//__uint64_t get_counter_v1(int *arr, __uint64_t size, __uint64_t *counter, int is_print_res)
__uint64_t get_counter_v1(void *args)
{
    int i = 0;
    double t = 0;
    algo_arg_t *arg = NULL;
    int *arr = NULL;
    __uint64_t size = 0;
    __uint64_t *counter = NULL;
    int is_print_res = 0;

    arg = (algo_arg_t *)args;
    arr = arg->arr;
    size = arg->size;
    counter = arg->counter;
    is_print_res = arg->is_print_res;

    t = wtime();
    for (i = 0; i < size; i++)
    {
	counter[CT_POS] += (arr[i] > 0);
	counter[CT_NEG] += (arr[i] < 0);
	counter[CT_ZER] += (arr[i] == 0);
    }
    t = wtime() - t;

    if (is_print_res)
	print_res(size, counter, t);

    return max(counter[CT_POS], counter[CT_NEG]);
}

static void *thread_func (void *arg)
{
    int i = 0;
    th_arg_t *thread_arg = NULL;
    thread_arg = (th_arg_t *)arg;
    th_ret_t *ret_struct = NULL;

    ret_struct = (th_ret_t *)calloc(1, sizeof(th_ret_t));
    if (!ret_struct)
	return NULL;

    for (i = 0; i < thread_arg->size; i++)
    {
	ret_struct->thread_counter[CT_POS] += (thread_arg->arr[i] > 0);
	ret_struct->thread_counter[CT_NEG] += (thread_arg->arr[i] < 0);
	ret_struct->thread_counter[CT_ZER] += (thread_arg->arr[i] == 0);
    }

    return ret_struct;
}

/***********************************************/
/* size = 2 * 10^7 for 0.176-0.198 sec         */
/* Parallel algorithm 'Reduce':                */
/* Every thread calculate values ONLY from his */
/*     part of array. And then result of every */
/*     thread additing to common result        */
/***********************************************/
//__uint64_t get_counter_v2(int *arr, __uint64_t size, __uint64_t *counter, int is_print_res)
__uint64_t get_counter_v2(void *args)
{
    int i = 0;
    int j = 0;
    int thread_num = 0;
    pthread_t *threads = NULL;
    th_arg_t *thread_args = NULL;
    void *thread_rets = NULL;
    double t = 0;

    algo_arg_t *arg = NULL;
    int *arr = NULL;
    __uint64_t size = 0;
    __uint64_t *counter = NULL;
    int is_print_res = 0;

    arg = (algo_arg_t *)args;
    arr = arg->arr;
    size = arg->size;
    counter = arg->counter;
    is_print_res = arg->is_print_res;

    t = wtime();
    thread_num = size > DEF_SIZE ? (size / DEF_SIZE) : 1;
    threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_num);
    if (!threads)
    {
	printf("%d: Allocation failed!\n", __LINE__);
	goto exit;
    }

    thread_args = (th_arg_t *)malloc(sizeof(th_arg_t) * thread_num);
    if (!thread_args)
    {
	printf("%d: Allocation failed!\n", __LINE__);
	goto exit;
    }

#if DEBUG
    printf("Arr: %p-%p %lld size, %d threads\n", arr, arr + size, size, thread_num);
#endif
    for (i = 0; i < thread_num; i++)
    {
	thread_args[i].arr = (int *)(arr + i * (size / thread_num));
	thread_args[i].size = i == thread_num - 1 ?
	               size - (size / thread_num * (thread_num - 1)) :
	               size / thread_num;
#if DEBUG
	printf("[%d] %p %lld\n", i, thread_args[i].arr, thread_args[i].size);
#endif
	if (pthread_create(&threads[i], NULL, &thread_func, &thread_args[i]) != 0)
	{
	    printf("pthread_create(%d) failed!\n", i);
	    goto exit;
	}
    }

    for (i = 0; i < thread_num; i++)
    {
	if (pthread_join(threads[i], &thread_rets) != 0)
	{
	    printf("pthread_join(%d) failed!\n", i);
	    goto exit;
	}
	for (j = 0; j < CT_NUM; j++)
	    counter[j] += ((th_ret_t *)thread_rets)->thread_counter[j];
	free(thread_rets);
    }
    t = wtime() - t;

    if (is_print_res)
	print_res(size, counter, t);

exit:
    if (threads) free(threads);
    if (thread_args) free(thread_args);

    return max(counter[CT_POS], counter[CT_NEG]);
}

static __uint64_t find_first_positive(int *arr, __uint64_t start, __uint64_t end)
{
    int i = 0;

    if (arr[end] <= 0)
	return -1;

    while (start < end)
    {
	i = (start + end) / BIN_SEARCH_STEP;
	if (arr[i] > 0)
	    end = i;
	else
	    start = i + 1;
    }
    if (arr[end] <= 0)
	return -1;

    return end;
}

static __uint64_t find_last_negative(int *arr, __uint64_t start, __uint64_t end)
{
    int i = 0;

    if (arr[start] >= 0)
	return -1;

    while (start < end)
    {
	i = (start + end) / BIN_SEARCH_STEP;
	if (arr[i] < 0)
	    start = i + 1;
	else
	    end = i;
    }

    if (arr[end] == 0)
	return end - 1;

    return end;
}

/************************************************/
/* size = 2 * 10^7 for 0.000005-0.0000009 sec   */
/* Find 'i' - index of last neg elem, so number */
/*     of neg elems eq to 'i + 1'               */
/* Then find 'i' - index of first pos elem, so  */
/*     num of pos elems eq to 'size - i'        */
/************************************************/
//__uint64_t get_counter_v3(int *arr, __uint64_t size, __uint64_t *counter, int is_print_res)
__uint64_t get_counter_v3(void *args)
{
    int i = 0;
    int j = 0;
    double t = 0;

    algo_arg_t *arg = NULL;
    int *arr = NULL;
    __uint64_t size = 0;
    __uint64_t *counter = NULL;
    int is_print_res = 0;

    arg = (algo_arg_t *)args;
    arr = arg->arr;
    size = arg->size;
    counter = arg->counter;
    is_print_res = arg->is_print_res;

    t = wtime();
    i = find_first_positive(arr, 0, size - 1);
    counter[CT_POS] = i < 0 ? 0 : size - i;

    j = find_last_negative(arr, 0, i < 0 ? size - 1 : i - 1);
    counter[CT_NEG] = j < 0 ? 0 : j + 1;

    counter[CT_ZER] = size - counter[CT_POS] - counter[CT_NEG];
    t = wtime() - t;

    if (is_print_res)
	print_res(size, counter, t);

    return max(counter[CT_POS], counter[CT_NEG]);
}
