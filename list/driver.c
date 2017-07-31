#include <stdio.h>

#include "list.h"

void printlist(LIST *list)
{
    Node_t *ptr = list->head;
    printf("+ list :");
    while(ptr)
    {
        printf("%d ", *(int *)ptr->value);
        ptr = ptr->next;
    }
    printf("  curr->%d\n", *(int *)list->curr->value);
}


void printlist1(LIST *list)
{
    Node_t *ptr = list->head;
    printf("- list :");
    while(ptr->next)
    {
        ptr = ptr->next;
    }
    while(ptr)
    {
        printf("%d ", *(int *)ptr->value);
        ptr = ptr->prev;
    }
    printf("  curr->%d\n", *(int *)list->curr->value);
}

void ll(LIST *list)
{
    printlist(list);
    //printlist1(list);
}


struct Test
{
    int *ptr;
};

void *freeTest(void  *t)
{
    
    ((struct Test *)t)->ptr = NULL;

    return NULL;
}
int *compare(void *p1, void *p2)
{
    int a = *(int *)p1, b  = *(int *)p2;
    if(a == b)
        return (int *)1;
    return 0;
}

int main(int argc, char **argv)
{
    LIST *list = ListCreate();
    LIST *list1 = ListCreate();

    int array[6] = {1,2,3,4,5,10};
    int array1[3] = {64,72,51};
    int i;
    //FUN funs[] = {ListFirst,ListLast,ListNext,ListPrev,ListCurr};
    /*FUN funs[] = {ListLast,ListNext,ListPrev,ListCurr};*/

    /*OPTEAR operator[] = {ListAdd,ListInsert,ListAppend,ListPrepend};*/

    for(i = 0; i < 5; i++ )
    {
        //ListFirst(list);
        ListAdd(list, &array[i]); 
    }
    for ( i = 0; i <3; i++)
    {
        ListAdd(list1, &array1[i]);
    }
    ll(list);
    printf("list 1 :");
    ll(list1);
    ListConcat(list,list1);
    ll(list);

    /*测试free*/
    struct Test t1;
    t1.ptr = NULL;
    LIST *list2 = ListCreate();
    ListAdd(list2, &t1);
    ListFree(list2, freeTest);

    /*测试searche*/

    printf("Will search %d\n", array1[1]);

    int *pp = ListSearch(list, compare, &array1[1]);

    if(pp)
        printf("Search is :%d\n", *pp);

    return 0;
}
