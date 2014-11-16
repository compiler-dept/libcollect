#include <stdlib.h>
#include <math.h>
#include "array_list.h"

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
        return floor(log2(idx)) + 1 -
               ARRAY_LIST_INITIAL_CAPACITY_EXPONENT;
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
            temp =
                malloc(sizeof(struct array_list) +
                       sizeof(void *) * arc);
            temp->next = NULL;
            temp->arc = arc;

            for (int j = 0; j < temp->arc; j++) {
                temp->arv[j] = NULL;
            }

            *al = temp;
        } else if (temp->next == NULL) {
            arc =
                pow(2,
                    ARRAY_LIST_INITIAL_CAPACITY_EXPONENT + (i ==
                            0 ? 0 :
                            i));
            temp->next =
                malloc(sizeof(struct array_list) +
                       sizeof(void *) * arc);
            temp->next->next = NULL;
            temp->next->arc = arc;

            for (int j = 0; j < temp->next->arc; j++) {
                temp->next->arv[j] = NULL;
            }

            temp = temp->next;
        } else {
            temp = temp->next;
        }
    } while (++i < chunk(idx));

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

void *array_list_get(struct array_list *const *al, int idx)
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

struct array_list_iterator *array_list_iterator_init(struct array_list *const
        *al)
{
    struct array_list_iterator *it =
        malloc(sizeof(struct array_list_iterator));
    it->current_chunk = *al;
    it->current = 0;
    return it;
}

void *array_list_iterator_next(struct array_list_iterator *it)
{
    void *elem = NULL;

    if (it->current_chunk) {
        elem = it->current_chunk->arv[it->current];
    }

    if (it->current < it->current_chunk->arc - 1) {
        it->current++;
    } else {
        it->current = 0;
        it->current_chunk = it->current_chunk->next;
    }

    return elem;
}

void array_list_free(struct array_list **al, void (*elem_free)(void *))
{
    struct array_list *next = NULL;
    for (struct array_list * temp = *al; temp; temp = next) {
        for (int i = 0; i<temp->arc; i++) {
            if (elem_free && temp->arv[i]) {
                elem_free(temp->arv[i]);
            }
        }
        next = temp->next;
        free(temp);
    }

    *al = NULL;
}
