#include <stdio.h>

enum types
{
    TYPE_0 = 0,
    TYPE_1,
    TYPE_2,
    TYPES_NUM
};

const char types_str[TYPES_NUM][30] =
{
    "type 0",
    "type_first",
    "type_second"
};

const char *strgz_type(int type)
{
    return types_str[type];
}

int main()
{
    for (int i = 0; i < TYPES_NUM; i++)
	printf("%s\n", strgz_type(i));
    return 0;
}