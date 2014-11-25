#include <stdlib.h>
#include <stdio.h>
#include "../tree.h"

void test_tree_iteration(void)
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

    CU_ASSERT(tree == NULL);
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

    CU_ASSERT(tree == NULL);
}
