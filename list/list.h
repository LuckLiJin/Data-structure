#ifndef __LIST_H_

#define __LIST_H_

#define MAXLEN 1024

typedef struct __node_t
{
    void *value;
    struct __node_t *prev;
    struct __node_t *next;
}Node_t;

typedef struct __list_t
{
   Node_t nodes[MAXLEN]; 
   Node_t *curr;
   Node_t *head;
   int count;
   int remove;
}LIST;


LIST *ListCreate();
int ListCount(LIST *list);
void *ListFirst(LIST *list);
void *ListLast(LIST *list);
void *ListNext(LIST *list);
void *ListPrev(LIST *list);
void *ListCurr(LIST *list);
int ListAdd(LIST * list, void *item);
int ListInsert(LIST * list, void *item);
int ListAppend(LIST * list, void *item);
int ListPrepend(LIST * list, void *item);
void *ListRemove(LIST *list);
void ListConcat(LIST * list1, LIST *list2);
void ListFree(LIST * list, void *itemFree(void*));
void *ListTrim(LIST *list);
void *ListSearch(LIST* list, int *comparator(void *, void*), void *comparisonArg);
#endif
