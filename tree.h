#ifndef TREE_H
#define TREE_H

#include "stack.h"

struct node {
    void *payload;
    int childc;
    struct node *childv[];
};

enum iterator_type {
    PREORDER = 1,
    POSTORDER
};

struct tree_iterator {
    enum iterator_type type;
    struct stack *stack;
    struct node *current;
};

struct tree_iterator *tree_iterator_init(struct node * const *tree, enum iterator_type type);

struct node *tree_iterator_next(struct tree_iterator *iterator);

void tree_free(struct node **tree, void (*payload_free)(void *));

#endif
