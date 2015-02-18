#include "clar.h"

#include <stdio.h>

#include "../hashmap.h"

void test_hashmap__put_get_equality(void)
{
    struct hashmap *table = NULL;

    int values[512];
    for (int i = 0; i < 512; i++){
        values[i] = i;
    }

    for (int i = 0; i < 512; i++) {
        char key[10];
        sprintf(key, "key%i", i);
        hashmap_put(&table, key, values + i);
    }

    int errors = 0;
    for (int i = 0; i < 512; i++) {
        char key[10];
        sprintf(key, "key%i", i);
        if (*((int*)hashmap_get(table, key)) != values[i]) {
            errors++;
        }
    }
    hashmap_free(table, NULL);

    cl_assert(errors == 0);
}

void test_hashmap__put_reassign(void)
{
    struct hashmap *table = NULL;
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    for (int i = 0; i < 10; i++) {
        char key[10];
        sprintf(key, "key%i", i%2);
        hashmap_put(&table, key, values + i);
    }

    int capacity = table->capacity;
    int size = table->size;
    hashmap_free(table, NULL);

    cl_assert(capacity == HASHMAP_INITIAL_CAPACITY);
    cl_assert(size == 2);
}

void test_hashmap__free_values(void)
{
    struct hashmap *table = NULL;
    int *values[2];

    values[0] = malloc(sizeof(int));
    *(values[0]) = 42;
    values[1] = malloc(sizeof(int));
    *(values[1]) = 23;

    for (int i = 0; i < 2; i++) {
        char key[10];
        sprintf(key, "key%i", i);
        hashmap_put(&table, key, values[i]);
    }

    int capacity = table->capacity;
    int size = table->size;

    hashmap_free(table, free);

    cl_assert(capacity == HASHMAP_INITIAL_CAPACITY);
    cl_assert(size == 2);
}
