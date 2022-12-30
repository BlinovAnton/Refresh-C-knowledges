#ifndef __MENU_H__
#define __MENU_H__

#include <list.h>
#include <stdio.h>
#include <sys/types.h>

enum main_menu_stages
{
    MENU_LIST = 1,
    MENU_TREE,
    MENU_MYDS,
    MENU_EXIT
};

enum list_menu_sages
{
    MENU_LIST_ADD = 1,
    MENU_LIST_FILL,
    MENU_LIST_REMOVE,
    MENU_LIST_PRINT,
    MENU_LIST_EXIT
};

__uint8_t glob_menu();
__uint8_t list_menu(list_ **);

#endif
