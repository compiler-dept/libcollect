#include <speck.h>
#include "../deque.h"

void spec_push_pop_equality1(void)
{
    int values1[] = {4, 3, 2, 1, 0};
    int values2[] = {5, 6, 7, 8, 9};
    struct deque *deque = NULL;

    for (int i = 0; i < 5; i++) {
        deque_push_first(&deque, values1 + i);
    }

    for (int i = 0; i < 5; i++) {
        deque_push_last(&deque, values2 + i);
    }

    sp_assert(deque != NULL);

    for (int i = 0; i < 10; i++) {
        int *val = (int *) deque_pop_first(&deque);
        sp_assert(*val == i);
    }

    sp_assert(deque == NULL);
}

void spec_push_pop_equality2(void)
{
    int values1[] = {4, 3, 2, 1, 0};
    int values2[] = {5, 6, 7, 8, 9};
    struct deque *deque = NULL;

    for (int i = 0; i < 5; i++) {
        deque_push_last(&deque, values2 + i);
    }

    for (int i = 0; i < 5; i++) {
        deque_push_first(&deque, values1 + i);
    }

    sp_assert(deque != NULL);

    for (int i = 0; i < 10; i++) {
        int *val = (int *) deque_pop_last(&deque);
        sp_assert(*val == 9 - i);
    }

    sp_assert(deque == NULL);
}

void spec_deque_free(void)
{
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    struct deque *deque = NULL;

    for (int i = 0; i < 10; i++) {
        deque_push_last(&deque, values + i);
    }

    sp_assert(deque != NULL);

    deque_free(&deque, NULL);

    sp_assert(deque == NULL);
}

void spec_deque_iterator(void)
{
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    struct deque *deque = NULL;

    for (int i = 0; i < 10; i++) {
        deque_push_last(&deque, values + i);
    }

    int counter = 0;
    struct deque_iterator *itarator = deque_iterator_init(&deque);

    int *temp;
    while ((temp = deque_iterator_next(itarator)) != NULL) {
        sp_assert(values[counter] == *temp);
        counter++;
    }

    deque_iterator_free(itarator);

    deque_free(&deque, NULL);
}
