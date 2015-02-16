#include "clar.h"

#include "../tree.h"

void test_tree__iterator_preorder(void)
{
    int values[] = {0,1,2,3,4,5};

    // construct tree with preorder: 0,1,2,3,4,5

    // leaf nodes
    struct node *b = tree_create_node(values + 2, 0);
    struct node *d = tree_create_node(values + 4, 0);
    struct node *e = tree_create_node(values + 5, 0);

    // inner nodes
    struct node *a = tree_create_node(values + 1, 1, b);
    struct node *c = tree_create_node(values + 3, 2, d, e);

    // root node
    struct node *root = tree_create_node(values, 2, a, c);

    struct tree_iterator *it = tree_iterator_init(&root, PREORDER);

    struct node *temp = NULL;
    for (int i = 0; i < 6; i++){
        temp = tree_iterator_next(it);
        cl_assert(*((int*)temp->payload) == values[i]);
    }

    cl_assert(tree_iterator_next(it) == NULL);
    tree_iterator_free(it);
    tree_free(&root, NULL);
    cl_assert(root == NULL);
}

void test_tree__iterator_postorder(void)
{
    int values[] = {0,1,2,3,4,5};

    // construct tree with postorder: 0,1,2,3,4,5

    // leaf nodes
    struct node *b = tree_create_node(values, 0);
    struct node *d = tree_create_node(values + 2, 0);
    struct node *e = tree_create_node(values + 3, 0);

    // inner nodes
    struct node *a = tree_create_node(values + 1, 1, b);
    struct node *c = tree_create_node(values + 4, 2, d, e);

    // root node
    struct node *root = tree_create_node(values + 5, 2, a, c);

    struct tree_iterator *it = tree_iterator_init(&root, POSTORDER);

    struct node *temp = NULL;
    for (int i = 0; i < 6; i++){
        temp = tree_iterator_next(it);
        cl_assert(*((int*)temp->payload) == values[i]);
    }

    cl_assert(tree_iterator_next(it) == NULL);
    tree_iterator_free(it);
    tree_free(&root, NULL);
    cl_assert(root == NULL);
}

void test_tree__free(void)
{
    struct node *tree = NULL;

    tree = malloc(sizeof(struct node) + sizeof(struct node *) * 1);
    tree->childc = 1;
    tree->payload = malloc(sizeof(int));
    *(int *)(tree->payload) = 5;

    tree->childv[0] = malloc(sizeof(struct node));
    tree->childv[0]->payload = malloc(sizeof(int));
    *(int *)(tree->childv[0]->payload) = 10;
    tree->childv[0]->childc = 0;

    tree_free(&tree, free);

    cl_assert(tree == NULL);
}

void test_tree_create(void)
{
    int *payload1 = malloc(sizeof(int));
    *payload1 = 5;
    int *payload2 = malloc(sizeof(int));
    *payload2 = 10;
    int *payload3 = malloc(sizeof(int));
    *payload3 = 15;

    struct node *tree = tree_create_node(
        payload1,
        2,
        tree_create_node(payload2, 0),
        tree_create_node(payload3, 0)
    );

    tree_free(&tree, free);

    cl_assert(tree == NULL);
}
