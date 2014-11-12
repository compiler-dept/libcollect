#include "tree.h"

struct tree_iterator *tree_iterator_init(struct node *tree, enum iterator_type type)
{
    struct tree_iterator *iterator = malloc(sizeof(struct tree_iterator));
    iterator->type = type;
    iterator->current = node;
    iterator->stack = NULL;

    return iterator;
}

struct node *tree_iterator_next(struct node *tree)
{

}

void tree_free(struct node *tree)
{

}
