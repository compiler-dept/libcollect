#include <stdlib.h>
#include <math.h>
#include "array_list.h"

int chunk(int idx)
{
    if (idx < pow(2, ARRAY_LIST_INITIAL_CAPACITY_EXPONENT)) {
        return 0;
    } else {
        return floor(log2(idx)) + 1 - ARRAY_LIST_INITIAL_CAPACITY_EXPONENT;
    }
}

int offset(int idx)
{
    if (idx < pow(2, ARRAY_LIST_INITIAL_CAPACITY_EXPONENT)) {
        return 0;
    } else {
        return pow(2, floor(log2(idx)));
    }
}

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
