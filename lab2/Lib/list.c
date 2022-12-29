#include <list.h>

__int8_t list_init(list_ **list)
{
#if 1
    printf("!list_init: addr %p val %p -> %p -> smth\n", &list, list, *list);
#endif
    *list = (list_ *)malloc(sizeof(list_));
    if (!*list)
	return EXIT_FAILURE;

    (*list)->head = NULL;
    (*list)->tail = NULL;

#if 1
    printf("!list_init: addr %p val %p -> %p -> smth\n", &list, list, *list);
#endif
    return EXIT_SUCCESS;
}

__int8_t list_add(list_ **list, __uint32_t val)
{
    if (!*list)
	return EXIT_FAILURE;

    /* Init node */
    listnode_ *node = NULL;
    node = (listnode_ *)malloc(sizeof(listnode_));
    if (!node)
	return EXIT_FAILURE;
    node->val = val;
    node->next = NULL;

    /* Connect pointers (adding) */
    if (!(*list)->head)
    {
	(*list)->head = node;
	(*list)->tail = node;
    }
    else
    {
	(*list)->tail->next = node;
	(*list)->tail = node;
    }

    return EXIT_SUCCESS;
}

listnode_ *list_lookup(list_ *list, __uint32_t val)
{
    if (!list)
	return NULL;

    listnode_ *node = NULL;
    for (node = list->head; node != NULL; node = node->next)
    {
	if (node->val == val)
	    return node;
    }
    return NULL;
}

__int8_t list_remove(list_ *list, __uint32_t val)
{
    /*if (!list)
	return 0;

    listnode_ *node = NULL;
    node = list_lookup(list, val);
    if (node)
    {
	if (node == list->head)
	{

	}
	if (
    }*/

    return 0;
}

__int8_t list_free(list_ **list)
{
    if (!*list)
	return 0;

    listnode_ *node = NULL;
    listnode_ *free_node = NULL;
    node = (*list)->head;
    while (node)
    {
	/* If i make 'free(node)', i will lose node->next pointer */
	free_node = node;
	node = node->next;
	free(free_node);
    }

    free(*list);

    return 0;
}

__int8_t list_print(list_ **list)
{
#if 1
    printf("!list_print: addr %p val %p -> %p -> smth\n", &list, list, *list);
#endif
    listnode_ *node = NULL;
    if (!*list)
    {
	printf("List not initialized\n");
	return 0;
    }

    if (!(*list)->head)
    {
	printf("List is empty\n");
	return 0;
    }

    printf("List:");
    for (node = (*list)->head; node->next != NULL; node = node->next)
    {
	printf(" %u", node->val);
    }
    printf("\n");

    return 0;
}
