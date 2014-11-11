#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

/**
 * @file  array_list.h
 * @brief Generic Array List
 */

#ifndef ARRAY_LIST_INITIAL_CAPACITY
#define ARRAY_LIST_INITIAL_CAPACITY_EXPONENT 5 ///< default array list init capacity (2^5 = 32)
#endif

struct array_list {
    struct array_list *next;
    int arc;
    void *arv[];
};

void array_list_set(struct array_list **al, int idx, void *elem);

void *array_list_get(struct array_list **al, int idx);

#endif
