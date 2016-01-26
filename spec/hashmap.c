#include <speck.h>
#include <stdio.h>
#include "../hashmap.h"

void spec_put_get_equality(void)
{
    struct hashmap *table = NULL;

    int values[512];
    for (int i = 0; i < 512; i++) {
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
        if (*((int *)hashmap_get(table, key)) != values[i]) {
            errors++;
        }
    }
    hashmap_free(&table, NULL);

    sp_assert(errors == 0);
}

void spec_put_reassign(void)
{
    struct hashmap *table = NULL;
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 10; i++) {
        char key[10];
        sprintf(key, "key%i", i % 2);
        hashmap_put(&table, key, values + i);
    }

    int capacity = table->capacity;
    int size = table->size;
    hashmap_free(&table, NULL);

    sp_assert(capacity == HASHMAP_INITIAL_CAPACITY);
    sp_assert(size == 2);
}

void spec_free_values(void)
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

    hashmap_free(&table, free);

    sp_assert(capacity == HASHMAP_INITIAL_CAPACITY);
    sp_assert(size == 2);
}

void spec_key_null(void)
{
    struct hashmap *hashmap = NULL;

    int i = 42;
    void *ret = hashmap_put(&hashmap, NULL, &i);

    sp_assert(ret == NULL);

    hashmap_free(&hashmap, NULL);
}

void spec_free_empty_hashmap(void)
{
    struct hashmap *hashmap = NULL;

    hashmap_free(&hashmap, NULL);
}

void spec_hashmap_update(void)
{
    struct hashmap *table_a = NULL;
    struct hashmap *table_b = NULL;

    int a = 23;
    int b = 42;
    int c = 39;

    int *ret = NULL;

    /* insert 23 into table_a */
    ret = hashmap_put(&table_a, "a", &a);
    sp_assert_equal_i(*ret, 23);

    /* insert 42 into table_b */
    ret = hashmap_put(&table_b, "b", &b);
    sp_assert_equal_i(*ret, 42);

    /* update table_a with table_b */
    hashmap_update(&table_a, table_b);

    /* check if 42 from table_b is now in table_a */
    ret = hashmap_get(table_a, "b");
    sp_assert_equal_i(*ret, 42);

    /* insert 39 into table_b as "a" */
    ret = hashmap_put(&table_b, "a", &c);
    sp_assert_equal_i(*ret, 39);

    /* update table_a from table_b again */
    hashmap_update(&table_a, table_b);

    /* check if value of key "a" has been updated to 39 from table_b */
    ret = hashmap_get(table_a, "a");
    sp_assert_equal_i(*ret, 39);

    /* free hashmaps */
    hashmap_free(&table_a, NULL);
    hashmap_free(&table_b, NULL);
}
