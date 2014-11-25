#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../array_list.h"

void test_array_list_in_out(void)
{
    struct array_list *al = NULL;
    int i = 5;
    array_list_set(&al, 0, &i);
    array_list_set(&al, 31, &i);
    array_list_set(&al, 32, &i);
    array_list_set(&al, 63, &i);
    array_list_set(&al, 64, &i);
    array_list_set(&al, 127, &i);
    array_list_set(&al, 128, &i);

    CU_ASSERT( *((int *)array_list_get(&al, 0)) == 5 );
    CU_ASSERT( *((int *)array_list_get(&al, 31)) == 5 );
    CU_ASSERT( *((int *)array_list_get(&al, 32)) == 5 );
    CU_ASSERT( *((int *)array_list_get(&al, 63)) == 5 );
    CU_ASSERT( *((int *)array_list_get(&al, 64)) == 5 );
    CU_ASSERT( *((int *)array_list_get(&al, 127)) == 5 );
    CU_ASSERT( *((int *)array_list_get(&al, 128)) == 5 );
}

void test_array_list_iterator_test(void)
{
    struct array_list *al = NULL;
    char buf[8];
    for (int i = 0; i < 100; i++){
        sprintf(buf, "val%i", i);
        array_list_set(&al, i, strdup(buf));
    }

    struct array_list_iterator *it = array_list_iterator_init(&al);

    char *temp = NULL;
    for (int i = 0; i < 100; i++){
        sprintf(buf, "val%i", i);
        temp = array_list_iterator_next(it);
        CU_ASSERT(strcmp(buf, temp) == 0);
    }

    array_list_free(&al, free);
    CU_ASSERT(al == NULL);
}
