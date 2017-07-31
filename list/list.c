#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static LIST preparep[256];
static int count = 0;


LIST *ListCreate()
{
    //LIST *list = malloc(1 * sizeof(LIST));
    LIST *list = preparep + count;
    count++;

    if(list)
    {
        int i;
        list->curr = NULL;
        list->head = NULL;
        list->count = 0;
        list->remove = 0;
        for(i =0; i < MAXLEN; i++)
        {
           list->nodes[i].value = NULL; 
           list->nodes[i].next = NULL; 
           list->nodes[i].prev = NULL; 
        }
        return list;
    }

    return NULL;
}
int ListCount(LIST *list)
{
    return list->count - list->remove;
}
void *ListFirst(LIST *list)
{
    if(ListCount(list) == 0)
    {
        return NULL;
    }

    list->curr = (list->head);

    return list->curr->value;;
}
void *ListLast(LIST *list)
{
    if(ListCount(list) == 0)
        return NULL;
    list->curr = list->head;

    while(list->curr->next)
        list->curr = list->curr->next;


    return list->curr->value;


}
void *ListNext(LIST *list)
{
    if(list->curr == NULL)
        return NULL;
    else if(list->curr->next == NULL)
        return NULL;
    else
    {
        list->curr = list->curr->next;
    }

    return list->curr->value;
}
void *ListPrev(LIST *list)
{
    if(list->curr == NULL) 
        return NULL;
    else if(list->curr->prev == NULL)
        return NULL;
    else
    {
        list->curr = list->curr->prev;
    }

    return list->curr->value;
}
void *ListCurr(LIST *list)
{
    if(list->curr)
        return list->curr->value;

    return NULL;

}
int ListAdd(LIST * list, void *item)
{
    if( ListCount(list) == 0)
    {
        list->head = &(list->nodes[list->count++]);
        list->curr = list->head;
        list->curr->value = item;
        return 0;
    }
    else if(list->count == MAXLEN)
    {
        return -1;
    }
    else
    {
        Node_t *newNode = &(list->nodes[list->count++]);
        if(list->curr->next != NULL) 
        {
            newNode->prev = list->curr;
            newNode->next = list->curr->next;
            list->curr->next->prev = newNode;
            list->curr->next = newNode;

        }
        else
        {
            newNode->prev = list->curr;
            list->curr->next = newNode;
        }
        list->curr = newNode;
        list->curr->value = item;
        return 0;
    }
    return 0;
}
int ListInsert(LIST * list, void *item)
{
    if(list->curr == NULL)
    {
        list->head = &(list->nodes[list->count++]);
        list->curr = list->head;
        list->curr->value = item;
        return 0;
    }
    else if(list->count == MAXLEN)
    {
        return -1;
    }
    else
    {
        Node_t *newNode = &(list->nodes[list->count++]);
        if(list->curr->prev != NULL) 
        {
            newNode->prev = list->curr->prev;
            newNode->next = list->curr;
            list->curr->prev->next = newNode;
            list->curr->prev = newNode;

        }
        else
        {
            newNode->next = list->curr;
            list->curr->prev = newNode;
            list->head = newNode;
        }
        list->curr = newNode;
        list->curr->value = item;
        return 0;
    }
    return 0;

}
int ListAppend(LIST * list, void *item)
{
    if(list->count == MAXLEN)
        return -1;
    /*Node_t *tmp = list->curr;*/
    ListLast(list);
    ListAdd(list,item);

    return 0;

}
int ListPrepend(LIST * list, void *item)
{
    if(list->count == MAXLEN)
        return -1;
    /*Node_t *tmp = list->curr;*/
    ListFirst(list);
    ListInsert(list,item);
    /*list->curr = tmp;*/

    return 0;
}
void *ListRemove(LIST *list)
{
    Node_t *node = list->curr;

    if(ListCount(list) == 0)
    {
        return NULL;
    }
    else
    {
        if(node->prev == NULL)
        {
            /*list->curr = node->next;*/
            list->head = list->head->next;
            if(list->head)
                list->head->prev = NULL;
            list->curr = list->head;
            /*if(list->curr)*/
                /*list->curr->prev = NULL;*/
        }
        else if(node->next == NULL)
        {
            list->curr = node->prev;
            if(list->curr)
                list->curr->next = NULL;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            list->curr = node->next;
        }
        list->remove++;
    }

    return node->value;

}
void ListConcat(LIST * list1, LIST *list2)
{
    Node_t *tmp = list1->curr;

    while(list2->head)
    {
        ListAppend(list1 , list2->head->value);
        list2->head = list2->head->next;
    }

    list1->curr = tmp;
    list2->count = 0;
    list2->remove = 0;
    list2->curr = NULL;
}
void ListFree(LIST * list, void *itemFree(void *))
{
    Node_t *tmp;
    while(list->head)
    {
        tmp = list->head;
        list->head = list->head->next;

        (*itemFree)(tmp->value);
        tmp->prev = tmp->next = NULL;
        tmp->value = NULL;
    }

    list->curr = list->head = NULL;
    list->count = 0;
    list->remove = 0;

}
void *ListTrim(LIST *list)
{
    Node_t *tmp = list->curr;


    ListLast(list);
    void *ptr = ListRemove(list);

    list->curr = tmp;

    return ptr;
}
void *ListSearch(LIST* list, int *comparator(void*, void*), void* comparisonArg)
{
    Node_t *tmp = NULL;
    tmp = list->curr;
    while(list->curr)
    {
        int *res = (*comparator)(list->curr->value, comparisonArg);
        if(res == (int *)1)
        {
            break;
        }
        list->curr= list->curr->next;
    }

    if(list->curr == NULL)
    {
        list->curr = tmp;
        return NULL;
    }
    else
    {
        void *ptr = list->curr->value;
        if(tmp)
            list->curr = tmp;
        return ptr;
    }

    return NULL;



}
