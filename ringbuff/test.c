#include <stdio.h>

#include "ring_buffer.h"

typedef struct __test_ring
{
    int rsize;
    int bsize;
    int wp;
    int rp;
    char buff[0];
}tring_t;

typedef struct __hash_table
{
    int key;
    int value;
}hash_table;

int main(int argc , char ** argv)
{
    tring_t *mytable = NULL;

    rb_create(100, sizeof(hash_table), mytable);

    if(mytable == NULL)
    {
        printf("ring buffer is create failed!\n");
        return 0;
    }

    if(rb_canRead(mytable))
        printf("Ring buff can read\n");
    else
        return 0;

    int i;
    for(i = 0; i < 100; i ++)
    {
        hash_table *ptr = NULL;
        rb_readOutValue(mytable, hash_table * , ptr);
        if(ptr == NULL)
            break;
        ptr->key = i;
        ptr->value = i+100;
        rb_writeInValue(mytable, hash_table *, ptr);
    }
    return 0;
}
