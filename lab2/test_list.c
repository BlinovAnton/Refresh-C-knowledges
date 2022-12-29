#include <list.h>

static int a[10] = {322, 228, 1, 5, 13, 78, 55, 39, 48, 100};

int main()
{
    list_ *list = NULL;
    int i = 0;

    list_init(&list);
    for (i =0; i < 10; i++)
	list_add(&list, a[i]);
    list_print(&list);
    list_free(&list);
    return 0;
}