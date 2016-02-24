#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
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

struct node *tree_create_node(void *payload, int childc, ...)
{
    va_list ap;

    struct node *temp =
        malloc(sizeof(struct node) + sizeof(struct node *) * childc);
    temp->payload = payload;
    temp->parent = NULL;
    temp->childc = childc;

    va_start(ap, childc);

    for (int i = 0; i < childc; i++) {
        temp->childv[i] = va_arg(ap, struct node *);
        temp->childv[i]->parent = temp;
    }

    va_end(ap);

    return temp;
}

struct node *tree_append_node(struct node **node, struct node *child)
{
    (*node)->childc += 1;

    struct node *temp_node = realloc((*node), sizeof(struct node) +
                                     ((*node)->childc * sizeof(struct node *)));

    child->parent = temp_node;
    temp_node->childv[temp_node->childc - 1] = child;

    if (temp_node != (*node)) {
        for (int i = 0; i < temp_node->childc - 1; i++) {
            temp_node->childv[i]->parent = temp_node;
        }
    }

    return temp_node;
}

struct tree_iterator *tree_iterator_init(struct node *const *tree,
        enum iterator_type type)
{
    struct tree_iterator *iterator = malloc(sizeof(struct tree_iterator));
    iterator->type = type;
    iterator->current = *tree;
    iterator->stack = NULL;

    return iterator;
}

struct node *tree_iterator_next_preorder(struct tree_iterator *iterator)
{
    struct node *next = iterator->current;

    if (iterator->current) {
        if (iterator->current->childc > 0) {
            for (int i = 1; i < iterator->current->childc; i++) {
                stack_push(&iterator->stack,
                           iterator->current->childv[i]);
            }
            iterator->current = iterator->current->childv[0];
        } else {
            iterator->current = stack_pop(&iterator->stack);
        }
    }

    return next;
}

struct node *tree_iterator_next_postorder(struct tree_iterator *iterator)
{
    struct node *next = NULL;

    if (iterator->current) {
        while (iterator->current->childc > 0) {
            stack_push(&iterator->stack, iterator->current);
            iterator->current = iterator->current->childv[0];
        }

        next = iterator->current;

        iterator->current =
            node_next_sibling(next, stack_peek(&(iterator->stack)));

    } else {
        next = (struct node *)stack_pop(&iterator->stack);
        iterator->current =
            node_next_sibling(next, stack_peek(&(iterator->stack)));
    }

    return next;
}

struct node *tree_iterator_next(struct tree_iterator *const *iterator)
{
    switch ((*iterator)->type) {
        case PREORDER:
            return tree_iterator_next_preorder((*iterator));
        case POSTORDER:
            return tree_iterator_next_postorder((*iterator));
        default:
            return NULL;
    }
}

void tree_iterator_free(struct tree_iterator **iterator)
{
    stack_free(&((*iterator)->stack), NULL);
    free(*iterator);
    *iterator = NULL;
}

void tree_free(struct node **tree, void (*payload_free) (void *))
{
    if (!tree) {
        return;
    }

    struct tree_iterator *it = tree_iterator_init(tree, POSTORDER);
    struct node *temp = NULL;

    while ((temp = tree_iterator_next(&it))) {
        if (payload_free) {
            payload_free(temp->payload);
        }

        free(temp);
    }

    *tree = NULL;
    tree_iterator_free(&it);
}
