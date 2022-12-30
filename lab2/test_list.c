#include <list.h>

static int a[10] = {322, 228, 1, 5, 13, 78, 55, 39, 48, 100};


/* Manual testing */
int main()
{
    list_ *list = NULL;
    int i = 0;

    list_print(&list);
    list_add(&list, 30);
    list_remove(&list, 20);

    list_init(&list);
    for (i =0; i < 10; i++)
	list_add(&list, a[i]);
    list_print(&list);

    list_remove(&list, 30);
    list_remove(&list, 13);
    list_print(&list);
    list_remove(&list, 100);
    list_print(&list);
    list_remove(&list, 322);

    list_remove(&list, 48);
    list_remove(&list, 39);
    list_remove(&list, 228);
    list_remove(&list, 78);
    list_remove(&list, 5);
    list_print(&list);
    list_remove(&list, 55);
    list_print(&list);
    list_remove(&list, 1);
    list_print(&list);

    list_free(&list);

    return 0;
}