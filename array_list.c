#include <stdlib.h>
#include <math.h>
#include "array_list.h"

/**
 * @file  array_list.c
 * @brief Generic Array List
 */

/**
 * @brief Calculate the actual chunk from a given index
 *
 * \param idx Index of the array list
 *
 * \return The actual chunk
 */
int chunk(int idx)
{
    if (idx < pow(2, ARRAY_LIST_INITIAL_CAPACITY_EXPONENT)) {
        return 0;
    } else {
        return floor(log2(idx)) + 1 - ARRAY_LIST_INITIAL_CAPACITY_EXPONENT;
    }
}

/**
 * @brief Calculate the number of elements before the actual chunk from a given
 * index.
 *
 * \param idx Index of the array list
 *
 * \return The offset in elements
 */
int offset(int idx)
{
    if (idx < pow(2, ARRAY_LIST_INITIAL_CAPACITY_EXPONENT)) {
        return 0;
    } else {
        return pow(2, floor(log2(idx)));
    }
}

/**
 * @brief Expands the array list to the needed size and finds the chunk
 * requested by the index
 *
 * \param al Pointer to the Pointer of the array list struct
 * \param idx Index of the array list
 *
 * \return Requested chunk
 */
struct array_list *expand_list(struct array_list **al, int idx)
{
    struct array_list *temp = *al;
    int arc = 0;
    int i = 0;

    do {
        if (temp == NULL) {
            arc = pow(2, ARRAY_LIST_INITIAL_CAPACITY_EXPONENT);
            temp = malloc(sizeof(struct array_list) + sizeof(void *) * arc);
            temp->next = NULL;
            temp->arc = arc;
            *al = temp;
        } else if (temp->next == NULL) {
            arc = pow(2, ARRAY_LIST_INITIAL_CAPACITY_EXPONENT + (i == 0 ? 0 : i));
            temp->next = malloc(sizeof(struct array_list) + sizeof(void *) * arc);
            temp->next->next = NULL;
            temp->next->arc = arc;
            temp = temp->next;
        } else {
            temp = temp->next;
        }
    } while(++i < chunk(idx));

    return temp;
}

void array_list_set(struct array_list **al, int idx, void *elem)
{
    struct array_list *temp = NULL;

    if (*al) {
        if (idx < pow(2, ARRAY_LIST_INITIAL_CAPACITY_EXPONENT)) {
            (*al)->arv[idx] = elem;
        } else {
            temp = expand_list(al, idx);
            temp->arv[idx - offset(idx)] = elem;
        }
    } else {
        temp = expand_list(al, idx);
        temp->arv[idx - offset(idx)] = elem;
    }
}

void *array_list_get(struct array_list **al, int idx)
{
    struct array_list *temp = *al;

    for (int i = 0; i < chunk(idx); i++) {
        if (temp && temp->next) {
            temp = temp->next;
        } else {
            return NULL;
        }
    }

    return temp->arv[idx - offset(idx)];
}
