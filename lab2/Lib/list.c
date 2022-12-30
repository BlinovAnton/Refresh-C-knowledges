#include <list.h>

__int8_t list_init(list_ **list)
{
#if DEBUG
    printf("list_init(s): addr %p val %p -> list:%p -> 0x0\n", &list, list, *list);
#endif

    *list = (list_ *)malloc(sizeof(list_));
    if (!*list)
	return EXIT_FAILURE;

    (*list)->head = NULL;
    (*list)->tail = NULL;

#if DEBUG
    printf("list_init(f): addr %p val %p -> list:%p -> 0x0\n", &list, list, *list);
#endif

    return EXIT_SUCCESS;
}

__int8_t list_add(list_ **list, __uint32_t val)
{
#if DEBUG
    printf("list_add(s): addr %p val %p -> list:%p -> head=%d, tail=%d\n",
           &list, list, *list, *list && (*list)->head ? (*list)->head->val : 0,
           *list && (*list)->tail ? (*list)->tail->val : 0);
#endif

    if (!*list)
	return EXIT_FAILURE;

    listnode_ **node = NULL;
    if (!(*list)->head)
    {
#if DEBUG
	printf("list_add: Try add %d in empty list\n", val);
#endif

	node = &((*list)->head);
    }
    else
    {
#if DEBUG
	printf("list_add: Try add %d in non-empty list\n", val);
#endif

	node = &((*list)->tail->next);
    }

    *node = (listnode_ *)malloc(sizeof(listnode_));
    (*node)->val = val;
    (*node)->next = NULL;
    (*list)->tail = *node;

#if DEBUG
    printf("list_add(f): addr %p val %p -> list:%p -> head=%d, tail=%d\n",
           &list, list, *list, (*list)->head ? (*list)->head->val : 0,
           (*list)->tail ? (*list)->tail->val : 0);
#endif

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


/************************************************************************/
/*      Case#1:                                                         */
/*          list->head->n1->n2->....->tail->NULL                        */
/*                 |                                                    */
/*             remove it, so head will be 'n1'                          */
/*      Case#2:                                                         */
/*          list->head->n1->n2->...->n*->tail->NULL                     */
/*                                        |                             */
/*                                    remove it                         */
/*          So the new 'tail' will be n*, and n*->NULL                  */
/*      Case #3:                                                        */
/*          List->head->n1->...->n(k-1)->nk->n(k+1)->...->tail->NULL    */
/*                                       |                              */
/*                                   remove it                          */
/*          So we need made n(k-1)->n(k+1) and only then free(nk)       */
/************************************************************************/
__int8_t list_remove(list_ **list, __uint32_t val)
{
    if (!*list)
    {
#if DEBUG
	printf("list_remove: List not initialized\n");
#endif

	return 0;
    }

    listnode_ *node = NULL;
    listnode_ *temp_node = NULL;
    node = list_lookup(*list, val);

#if DEBUG
    printf("list_remove: %d %sfound\n", val, node ? "is " : "not ");
#endif

    if (node)
    {
	if (node == (*list)->head)
	{
	    (*list)->head = (*list)->head->next;
	    free(node);
	}
	else if (node == (*list)->tail)
	{

	    for (temp_node = (*list)->head;
	         temp_node->next != node;
	         temp_node = temp_node->next)
#if DEBUG
	    {
		printf("list_remove(2): %p->%d\n", temp_node, temp_node ? temp_node->val : 0);
	    }
#else
	    ;
#endif

	    (*list)->tail = temp_node;
	    free(node);
	    temp_node->next = NULL;
	}
	else
	{
	    for (temp_node = (*list)->head;
	         temp_node->next != node;
	         temp_node = temp_node->next);
	    temp_node->next = node->next;
	    free(node);
	}
    }

    return 0;
}

__int8_t list_free(list_ **list)
{
    if (!*list)
{
#if DEBUG
	printf("list_free: List not initialized\n");
#endif

	return 0;
}

    listnode_ *node = NULL;
    listnode_ *free_node = NULL;
    node = (*list)->head;
    while (node)
    {
	/* If we'll made 'free(node)', we'll lose 'node->next' pointer */
	free_node = node;
	node = node->next;
	free(free_node);
    }

    free(*list);
    return 0;
}

__int8_t list_print(list_ **list)
{
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
    for (node = (*list)->head; node != NULL; node = node->next)
    {
	printf(" %u", node->val);
    }
    printf("\n");

    return 0;
}
