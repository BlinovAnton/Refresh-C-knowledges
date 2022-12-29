#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct listnode
{
    int val;
    struct listnode *next;
} listnode_;

typedef struct list
{
    listnode_ *head;

    /* Tail need to made 'list_add' faster */
    listnode_ *tail;
} list_;

__int8_t list_init(list_ **);
__int8_t list_add(list_ **, unsigned int);
listnode_ *list_lookup(list_ *, unsigned int);
__int8_t list_remove(list_ *, unsigned int);
__int8_t list_free(list_ **);
__int8_t list_print(list_ **);

#endif
