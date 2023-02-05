/********************************************************************/
/* This prog only need to practise function pointer and binary math */
/********************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define DYNAMIC_ARR 1

enum bit_menu
{
    BIT_MENU_ONE = 1,
    BIT_MENU_ZERO,
    BIT_MENU_CHANGE,
    BIT_MENU_EXIT
};

/* macroses need because no matter which type is 'val' */
#define _bit_to_one(val, bit)   ( (val) |= 1 << (bit)    )
#define _bit_to_zero(val, bit)  ( (val) &= ~(1 << (bit)) )
#define _bit_to_other(val, bit) ( (val) ^= 0x1 << (bit)  )

/* bit functions need for func array, but functions have types */
__uint32_t bit_to_one  (__uint32_t val, char bit);
__uint32_t bit_to_zero (__uint32_t val, char bit);
__uint32_t bit_to_other(__uint32_t val, char bit);

int main ()
{
    __uint32_t val = 0;
    int op_type = 0;
    int bit_num = 0;

#if DYNAMIC_ARR
    __uint32_t (**bit_opers)(__uint32_t, char) = NULL;
    bit_opers = malloc(sizeof(__uint32_t *) * (BIT_MENU_EXIT - 1));
    bit_opers[BIT_MENU_ONE - 1]    = bit_to_one;
    bit_opers[BIT_MENU_ZERO - 1]   = bit_to_zero;
    bit_opers[BIT_MENU_CHANGE - 1] = bit_to_other;
#else
    __uint32_t (*bit_opers[BIT_MENU_EXIT - 1])(__uint32_t, char)
                = { bit_to_one, bit_to_zero, bit_to_other };
#endif

    printf("\n\nInput type of operation and position of bit\n");
    printf("%d. Make bit a 1\n", BIT_MENU_ONE);
    printf("%d. Make bit a 0\n", BIT_MENU_ZERO);
    printf("%d. Change bit\n",   BIT_MENU_CHANGE);
    printf("%d. Exit\n",         BIT_MENU_EXIT);
    while (op_type != BIT_MENU_EXIT)
    {
	scanf("%d", &op_type);
	if (op_type != BIT_MENU_EXIT)
	{
	    scanf("%d", &bit_num);
	    val = bit_opers[op_type - 1](val, bit_num);
	    printf("val = %d\n", val);
	}
    }

#if 0
    /* Test how to make 'the rightest' bit (which is eq 1) to 0 */
    int x = 113;
    for (; x != 0; x &= (x - 1))
    {
	printf("x = %d\n", x);
    }
#endif

    return 0;
}

__uint32_t bit_to_one(__uint32_t val, char bit)
{
    return _bit_to_one(val, bit);
}

__uint32_t bit_to_zero(__uint32_t val, char bit)
{
    return _bit_to_zero(val, bit);
}

__uint32_t bit_to_other(__uint32_t val, char bit)
{
    return _bit_to_other(val, bit);
}
