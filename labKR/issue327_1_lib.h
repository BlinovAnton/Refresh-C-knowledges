#ifndef __ISSUE327_1_LIB_H__
#define __ISSUE327_1_LIB_H__

#include <sched.h>
#include <pthread.h>
#include <sys/wait.h>
#include "common_functions.h"

#define DEF_SIZE        500000
#define DEF_MIN         0
#define DEF_MAX         100
#define ADD_NEG         1 /* include neg vals too */
#define CT_STR_MAXLEN   30
#define BIN_SEARCH_STEP 2
#define NUM_OF_ALGOS    4
#define STACK_SIZE      (1024 * 1024) /* stack size for cloned child */
#define CLONE_FLAGS     (CLONE_NEWUTS | SIGCHLD)

enum counter_types
{
    CT_POS = 0, //count positive vals
    CT_NEG,     //count negative vals
    CT_ZER,     //count number of zeros
    CT_NUM      //number of types
};

static const char counter_types_str[CT_NUM][CT_STR_MAXLEN] =
{
    "positive",
    "negative",
    "zero"
};

struct thread_arg
{
    int        *arr;
    __uint64_t size;
} typedef th_arg_t;

struct algo_arguments
{
    int        *arr;
    __uint64_t size;
    __uint64_t *counter;
    int        is_print_res;
} typedef algo_arg_t;

struct thread_ret
{
    __uint64_t thread_counter[CT_NUM];
} typedef th_ret_t;

const char *stringize_CT_TYPE(int);
__uint64_t get_counter_v0(void *);
__uint64_t get_counter_v1(void *);
__uint64_t get_counter_v2(void *);
__uint64_t get_counter_v3(void *);

#endif