#ifndef HASHMAP_H
#define HASHMAP_H

#ifndef HASHMAP_INITIAL_CAPACITY
#define HASHMAP_INITIAL_CAPACITY 32 ///< default hashmap init capacity
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file  hashmap.h
 * @brief Generic Hashmap
 */

/**
 * @brief hashmap entry structure
 */
struct hashmap_entry {
    char *key;   ///< entry search key
    void *value; ///< entry value
};

/**
 * @brief main hashmap structure
 */
struct hashmap {
    int capacity;                 ///< actual max capacity of hashmap
    int size;                     ///< actual fill of hashmap
    struct hashmap_entry *values; ///< array of entries
};

/**
 * @brief Free hash table.
 *
 * Uses free.
 * \param table pointer to hashmap struct
 */
void hashmap_free(struct hashmap **table, void (*value_free) (void *ptr));

/**
 * @brief Insert value into hash table. If *table is NULL, allocate new hashmap.
 *
 * Insert using quadratic probing as collision strategy.
 * Double capacity when size > (0.7 * capacity).
 * \param table pointer to the pointer of the hashmap struct
 * \param key key string
 * \param value pointer to payload/value
 */
void *hashmap_put(struct hashmap **table, const char *key, void *value);

/**
 * @brief Get value from hash table.
 *
 * If table is NULL, NULL is returned for any key.
 * \param table pointer to hashmap struct
 * \param key key string
 */
void *hashmap_get(struct hashmap *table, const char *key);

#endif /* HASHTABLE_H */
