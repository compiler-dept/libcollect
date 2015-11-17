#include <speck.h>
#include "../tree.h"

void spec_iterator_preorder(void)
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
        sp_assert(*((int*)temp->payload) == values[i]);
    }

    sp_assert(tree_iterator_next(it) == NULL);
    tree_iterator_free(it);
    tree_free(&root, NULL);
    sp_assert(root == NULL);
}

void spec_iterator_postorder(void)
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
        sp_assert(*((int*)temp->payload) == values[i]);
    }

    sp_assert(tree_iterator_next(it) == NULL);
    tree_iterator_free(it);
    tree_free(&root, NULL);
    sp_assert(root == NULL);
}

void spec_free(void)
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

    sp_assert(tree == NULL);
}

void spec_tree_create(void)
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

    sp_assert(tree == NULL);
}

void spec_append_node(void)
{
    int *payload1 = malloc(sizeof(int));
    *payload1 = 5;
    int *payload2 = malloc(sizeof(int));
    *payload2 = 10;
    int *payload3 = malloc(sizeof(int));
    *payload3 = 15;
    int *payload4 = malloc(sizeof(int));
    *payload4 = 20;

    struct node *tree = tree_create_node(
        payload1,
        2,
        tree_create_node(payload2, 0),
        tree_create_node(payload3, 0)
    );

    tree = tree_append_node(tree, tree_create_node(payload4, 0));

    sp_assert(tree->childc == 3);

    tree_free(&tree, free);

    sp_assert(tree == NULL);
}


void spec_iterator_parent_pointers(void)
{
    int values[] = {0,1,2,3,4,5};
    int parent_values_b[] = {2,1,0};
    int parent_values_d[] = {4,3,0};
    int parent_values_e[] = {5,3,0};

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

    // test parents for b
    struct node *temp = b;
    for (int i = 0; i<3; i++){
        sp_assert(*((int*)temp->payload) == parent_values_b[i]);
        temp = temp->parent;
    }
    sp_assert(temp == NULL);

    // test parents for d
    temp = d;
    for (int i = 0; i<3; i++){
        sp_assert(*((int*)temp->payload) == parent_values_d[i]);
        temp = temp->parent;
    }
    sp_assert(temp == NULL);

    // test parents for e
    temp = e;
    for (int i = 0; i<3; i++){
        sp_assert(*((int*)temp->payload) == parent_values_e[i]);
        temp = temp->parent;
    }
    sp_assert(temp == NULL);

    tree_free(&root, NULL);
    sp_assert(root == NULL);
}

void spec_append_node_parent_ptr(void)
{
    struct node *child_a = tree_create_node(NULL, 0);
    struct node *child_b = tree_create_node(NULL, 0);
    struct node *parent = tree_create_node(NULL, 1, child_a);
    struct node *super_parent = tree_create_node(NULL, 1, parent);

    parent = tree_append_node(parent, child_b);

    sp_assert(super_parent == parent->parent);

    free(child_a);
    free(child_b);
    free(parent);
    free(super_parent);
}
