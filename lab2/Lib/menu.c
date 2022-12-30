#include <menu.h>

static __uint32_t joke_cnt = 0;

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
	printf("%d. List\n",                         MENU_LIST);
	printf("%d. Tree\n",                         MENU_TREE);
	printf("%d. The fastest data structure"\
	       " in the world by me\n",              MENU_MYDS);
	printf("%d. Exit this excellent programm\n", MENU_EXIT);

	/* Bug with symbols, mb 'getc' or smth can fix it */
	scanf("%u", &menu);
	switch(menu)
        {
	    case MENU_LIST:
		list_menu(&list);
		joke_cnt = 0;
		break;
	    case MENU_TREE:
		printf("Functional doesn't released yet\n");
		joke_cnt = 0;
		break;
	    case MENU_MYDS:
		printf("Functional doesn't released yet\n");
		joke_cnt = 0;
		break;
	    case MENU_EXIT:
		list_free(&list);
		printf("%s\n", joke_cnt >= 2 ? "Fuck off mate" : "Bye ;)");
		break;
	    default:
		if (joke_cnt == 0)
		    printf("Are You SHCHEWPID mate? Press 1,2,3 "\
		           "or smth like that, dunkey!\n");
		if (joke_cnt == 1)
		    printf("Listen mate, if you continue press shit," \
		           "i will punch you in you fUck'in face\n");
		if (joke_cnt == 2)
		    printf("Alright mate, i'm coming for you stright outta London\n");
		if (joke_cnt > 2)
		    printf("BRUV...\n");
		joke_cnt++;
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

#if DEBUG
    printf("list_menu(s): addr %p val %p -> %p -> %s\n",
           &list, list, *list, *list ? "smth" : "0x0");
#endif

    while (menu != MENU_LIST_EXIT)
    {
	printf("\n\nList menu:\n");
	printf("%d. Add value\n",           MENU_LIST_ADD);
	printf("%d. Fill list from file\n", MENU_LIST_FILL);
	printf("%d. Remove value\n",        MENU_LIST_REMOVE);
	printf("%d. Print list\n",          MENU_LIST_PRINT);
	printf("%d. Return to main menu\n", MENU_LIST_EXIT);

	/* Bug with symbols, mb 'getc' or smth can fix it */
	scanf("%u", &menu);
	switch(menu)
	{
	    case MENU_LIST_ADD:
		printf("Input val to add: ");
		scanf("%u", &val);
		if (!*list)
		    list_init(list);
		list_add(list, val);
		joke_cnt = 0;
		break;
	    case MENU_LIST_FILL:
		printf("Functional doesn't released yet\n");
#if 0
		printf("Input path to file: ");
		scanf("%s", &path);
		
#endif
		joke_cnt = 0;
		break;
	    case MENU_LIST_REMOVE:
		printf("Input val to remove: ");
		scanf("%u", &val);
		list_remove(list, val);
		joke_cnt = 0;
		break;
	    case MENU_LIST_PRINT:
		list_print(list);
		joke_cnt = 0;
		break;
	    case MENU_LIST_EXIT:
		joke_cnt = 0;
		break;
	    default:
		if (joke_cnt == 0)
		    printf("Are You SHCHEWPID mate? Press 1,2,3 "\
		           "or smth like that, dunkey!\n");
		if (joke_cnt == 1)
		    printf("Listen mate, if you continue press shit," \
		           "i will punch you in you fUck'in face\n");
		if (joke_cnt == 2)
		    printf("Alright mate, i'm coming for you stright outta London\n");
		if (joke_cnt > 2)
		    printf("BRUV...\n");
		joke_cnt++;
		break;
	}
    }

    return 0;
}
