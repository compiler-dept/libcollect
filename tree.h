#ifndef TREE_H
#define TREE_H

/**
 * @file  tree.h
 * @brief Generic Tree
 */

#include "stack.h"

/**
 * @brief Tree node structure
 */
struct node {
    void *payload;         ///< pointer to payload
    struct node *parent;   ///< pointer to parent node
    int childc;            ///< number of child nodes
    struct node *childv[]; ///< array of pointers to child nodes
};

/**
 * @brief Iterator types
 */
enum iterator_type {
    PREORDER = 1, ///< preorder iterator
    POSTORDER     ///< postorder iterator
};

/**
 * @brief Tree iterator structure
 */
struct tree_iterator {
    enum iterator_type type; ///< iterator type
    struct stack *stack;     ///< pointer to a stack
    struct node *current;    ///< current node
};

/**
 * @brief Creates a new node with childc pointers to child nodes and payload
 *
 * \param payload pointer to payload
 * \param childc number of child node pointers
 * \param ... as many as childc comma separated pointers to nodes
 *
 * \return new tree node
 */
struct node *tree_create_node(void *payload, int childc, ...);

/**
 * @brief Appends a new node as child to a given node
 *
 * In order to append the child node, a new node is created and all child
 * pointers are copied over to the new node. The old node is automatically free.
 *
 * \param node old node to which the child is appended
 * \param child the child node which is appended
 *
 * \return new tree node with appended child
 */
struct node *tree_append_node(struct node **node, struct node *child);

/**
 * @brief Initializes a new tree iterator.
 *
 * \param tree pointer to the tree
 * \param type type of iterator. Either PREORDER or POSTORDER
 *
 * \return new iterator
 */
struct tree_iterator *tree_iterator_init(struct node *const *tree,
        enum iterator_type type);

/**
 * @brief Next node from tree iterator
 *
 * \param iterator pointer to iterator
 *
 * \return next node from tree, depends on type of iterator
 */
struct node *tree_iterator_next(struct tree_iterator *const *iterator);

/**
 * @brief Free iterator
 *
 * \param iterator pointer to iterator
 *
 */
void tree_iterator_free(struct tree_iterator **iterator);

/**
 * @brief Frees a tree
 *
 * \param tree pointer to the pointer of the tree
 * \param payload_free pointer to a function that frees the payload
 *
 * \return Nothing
 */
void tree_free(struct node **tree, void (*payload_free)(void *));

#endif
