#include <stdlib.h>
#include "tree.h"

struct node *node_next_sibling(struct node *node, struct node *parent)
{
    if (node && parent) {
        for (int i = parent->childc - 1; i > 0; i--) {
            if (parent->childv[i - 1] == node) {
                return parent->childv[i];
            }
        }
    }

    return NULL;
}

struct tree_iterator *tree_iterator_init(struct node * const *tree, enum iterator_type type)
{
    struct tree_iterator *iterator = malloc(sizeof(struct tree_iterator));
    iterator->type = type;
    iterator->current = *tree;
    iterator->stack = NULL;

    return iterator;
}

struct node *tree_iterator_next(struct tree_iterator *iterator)
{
    struct node *next = NULL;

    if (iterator->current) {
        while (iterator->current->childc > 0) {
            stack_push(&iterator->stack, iterator->current);
            iterator->current = iterator->current->childv[0];
        }

        next = iterator->current;

        iterator->current =
            node_next_sibling(next, stack_peek(iterator->stack));

    } else {
        next = (struct node *)stack_pop(&iterator->stack);
        iterator->current =
            node_next_sibling(next, stack_peek(iterator->stack));
    }

    return next;
}

void tree_free(struct node **tree, void (*payload_free)(void *))
{
    if (!tree) {
        return;
    }

    struct tree_iterator *it = tree_iterator_init(tree, POSTORDER);
    struct node *temp = NULL;

    while ((temp = tree_iterator_next(it))) {
        if (payload_free) {
            payload_free(temp->payload);
        }

        free(temp);
    }

    *tree = NULL;
    free(it);
}
