#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct listnode
{
    int val;
    struct listnode *next;

    /* 'prev' need to make 'list_remove' O(n) */
    //listnode_ *prev; // without 'prev' function 'list_remove' is O(n^2)
} listnode_;

typedef struct list
{
    listnode_ *head;

    /* 'tail' need to make 'list_add' O(1) */
    listnode_ *tail;
} list_;

__int8_t list_init(list_ **);
__int8_t list_add(list_ **, unsigned int);
listnode_ *list_lookup(list_ *, unsigned int);
__int8_t list_remove(list_ **, unsigned int);
__int8_t list_free(list_ **);
__int8_t list_print(list_ **);

#endif
