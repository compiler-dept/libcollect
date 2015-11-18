#include <stdlib.h>
#include "deque.h"

void deque_push_first(struct deque **deque, void *elem)
{
    if (elem) {
        struct deque_node *temp = malloc(sizeof(struct deque_node));
        temp->elem = elem;
        temp->prev = NULL;

        if (*deque == NULL) {
            *deque = malloc(sizeof(struct deque));

            temp->next = NULL;
            (*deque)->head = temp;
            (*deque)->tail = temp;
        } else {

            temp->next = (*deque)->head;
            (*deque)->head->prev = temp;
            (*deque)->head = temp;
        }
    }
}


void deque_push_last(struct deque **deque, void *elem)
{
    if (elem) {
        struct deque_node *temp = malloc(sizeof(struct deque_node));
        temp->elem = elem;
        temp->next = NULL;

        if (*deque == NULL) {
            *deque = malloc(sizeof(struct deque));

            temp->prev = NULL;
            (*deque)->head = temp;
            (*deque)->tail = temp;
        } else {

            temp->prev = (*deque)->tail;
            (*deque)->tail->next = temp;
            (*deque)->tail = temp;
        }
    }
}


void *deque_pop_first(struct deque **deque)
{
    void *elem = NULL;

    if (*deque) {
        struct deque_node *old_head = (*deque)->head;
        elem = old_head->elem;
        (*deque)->head = old_head->next;
        if ((*deque)->head) {
            (*deque)->head->prev = NULL;
        }
        free(old_head);
        if ((*deque)->head == NULL) {
            free(*deque);
            *deque = NULL;
        }
    }

    return elem;
}


void *deque_pop_last(struct deque **deque)
{
    void *elem = NULL;

    if (*deque) {
        struct deque_node *old_tail = (*deque)->tail;
        elem = old_tail->elem;
        (*deque)->tail = old_tail->prev;
        if ((*deque)->tail) {
            (*deque)->tail->next = NULL;
        }
        free(old_tail);
        if ((*deque)->tail == NULL) {
            free(*deque);
            *deque = NULL;
        }
    }

    return elem;
}

void deque_free(struct deque **deque, void (*payload_free) (void *))
{
    void *temp;
    while ((temp = deque_pop_first(deque)) != NULL) {
        if (payload_free) {
            payload_free(temp);
        }
    }
}

struct deque_iterator *deque_iterator_init(struct deque *const *deque)
{
    struct deque *temp = *deque;
    struct deque_iterator *iterator = malloc(sizeof(struct deque_iterator));
    iterator->current = temp->head;

    return iterator;
}

void *deque_iterator_next(struct deque_iterator *iterator)
{
    if (iterator->current == NULL) {
        return NULL;
    }

    void *elem = iterator->current->elem;

    iterator->current = iterator->current->next;

    return elem;
}

void deque_iterator_free(struct deque_iterator *iterator)
{
    free(iterator);
}
