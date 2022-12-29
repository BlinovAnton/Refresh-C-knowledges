#include <menu.h>

__uint8_t glob_menu()
{
    __uint32_t menu = 0;
    list_ *list = NULL;
#if DEBUG
    printf("glob_menu(s): addr %p val %p -> 0x0\n", &list, list);
#endif

    while (menu != MENU_EXIT)
    {
	printf("Main menu:\n");
	printf("%d. List\n", MENU_LIST);
	printf("%d. Tree\n", MENU_TREE);
	printf("%d. Exit this excellent programm\n", MENU_EXIT);
	scanf("%u", &menu);
	switch(menu)
        {
	    case MENU_LIST:
		list_menu(&list);
		break;
	    case MENU_TREE:
		printf("Functional doesn't released yet\n");
		break;
	    case MENU_EXIT:
		list_free(&list);
		printf("Bye! :)\n");
		break;
	    default:
		printf("Are You SHCHEWPID mate? Press 1,2,3 or smth like that, dunkey!\n");
		break;
	}
	printf("\n\n");
    }

    return 0;
}

__uint8_t list_menu(list_ **list)
{
    __uint32_t menu = 0;
    __uint32_t val = 0;
    __int32_t temp = 10;

#if DEBUG
    printf("list_menu(s): addr %p val %p -> %p -> %s\n",
           &list, list, *list, *list ? "smth" : "0x0");
#endif
    while (menu != MENU_LIST_EXIT)
    {
	printf("List menu:\n");
	printf("%d. Add value\n", MENU_LIST_ADD);
	printf("%d. Fill list from file\n", MENU_LIST_FILL);
	printf("%d. Remove value\n", MENU_LIST_REMOVE);
	printf("%d. Print list\n", MENU_LIST_PRINT);
	printf("%d. Return to main menu\n", MENU_LIST_EXIT);
	scanf("%u", &menu);
	switch(menu)
	{
	    case MENU_LIST_ADD:
		printf("Input val to add: ");
		scanf("%u", &val);
		if (!*list)
		    temp = list_init(list);
		printf("[%p]temp = %d, \n", *list, temp);
		list_add(list, val);
		break;
	    case MENU_LIST_FILL:
		printf("Functional doesn't released yet\n");
#if 0
		printf("Input path to file: ");
		scanf("%s", &path);
		
#endif
		break;
	    case MENU_LIST_REMOVE:
		printf("Functional doesn't released yet\n");
#if 0
		printf("Input val to remove: ");
		scanf("%u", &val);
		list_remove(list, val);
#endif
		break;
	    case MENU_LIST_PRINT:
		list_print(list);
		break;
	    case MENU_LIST_EXIT:
		break;
	    default:
		printf("Listen mate, if you continue press shit," \
		       "i will puch you in you fUck'in face\n");
		break;
	}
    }

    return 0;
}
