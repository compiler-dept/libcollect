#include "hashmap.h"

/**
 * @brief Dan Bernsteins DJB2 Hash Function
 * @detail http://www.cse.yorku.ca/~oz/hash.html
 * String must be terminated with a null-byte.
 */
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

/**
 * @brief Allocate new hash table.
 * @detail Uses malloc. Free with hashmap_free.
 */
struct hashmap *hashmap_alloc(int capacity)
{
    struct hashmap *new_table = malloc(sizeof(struct hashmap));
    new_table->capacity = capacity;
    new_table->size = 0;
    new_table->values = malloc(capacity * sizeof(struct hashmap_entry));
    for (int i = 0; i < new_table->capacity; i++) {
        new_table->values[i].key = NULL;
    }
    return new_table;
}

void hashmap_free(struct hashmap **table, void (*value_free) (void *ptr))
{
    if (!table) {
        return;
    }
    for (int i = 0; i < (*table)->capacity; i++) {
        if ((*table)->values[i].key) {
            free((*table)->values[i].key);

            if (value_free) {
                value_free((*table)->values[i].value);
            }
        }
    }
    free((*table)->values);
    free(*table);
    *table = NULL;
}

struct hashmap *clone_and_double(struct hashmap *table)
{
    struct hashmap *new_table;
    new_table = hashmap_alloc(2 * table->capacity);
    struct hashmap_entry *entry;
    for (int i = 0; i < table->capacity; i++) {
        entry = table->values + i;
        if (entry->key) {
            hashmap_put(&new_table, entry->key, entry->value);
        }
    }
    return new_table;
}

void *hashmap_put(struct hashmap **table, const char *key, void *value)
{
    if (*table == NULL) {
        *table = hashmap_alloc(HASHMAP_INITIAL_CAPACITY);
    } else if ((*table)->size > 0.7 * (*table)->capacity) {
        struct hashmap *doubled_table = clone_and_double(*table);
        hashmap_free(table, NULL);
        *table = doubled_table;
    }

    unsigned long hashval = hash((char *)key);
    unsigned long position;
    unsigned char reassign = 0;
    int i = 1;
    do {
        // Quadratic probing
        position = hashval + ((int)(0.5 * i)) + ((int)(0.5 * i * i));
        position %= (*table)->capacity;
        i++;
    } while ((*table)->values[position].key
             && !(reassign =
                      strcmp((*table)->values[position].key, key) == 0));

    void *ret = NULL;

    if (!reassign) {
        (*table)->size++;
        (*table)->values[position].key = malloc(strlen(key) + 1);
        strcpy((*table)->values[position].key, key);
    } else {
        ret = (*table)->values[position].value;
    }

    (*table)->values[position].value = value;
    return ret;
}

void *hashmap_get(struct hashmap *table, const char *key)
{
    void *value = NULL;
    if (table) {
        unsigned long hashval = hash((char *)key);
        unsigned long position;
        int i = 1;
        do {
            // Quadratic probing
            position =
                hashval + ((int)(0.5 * i)) + ((int)(0.5 * i * i));
            position %= table->capacity;
            i++;
        } while (table->values[position].key &&
                 strcmp(table->values[position].key, key) != 0);
        if (table->values[position].key) {
            value = table->values[position].value;
        }
    }
    return value;
}
