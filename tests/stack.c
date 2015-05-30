#include "clar.h"

#include "../stack.h"

void test_stack__push_pop_equality(void)
{
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    struct stack *stack = NULL;

    for (int i = 0; i < 10; i++) {
        stack_push(&stack, values + i);
    }

    cl_assert(stack != NULL);

    for (int i = 9; i > 2; i--) {
        int *val = (int *)stack_pop(&stack);
        cl_assert(val == values + i);
    }

    stack_free(&stack, NULL);
}

void test_stack__free_empty_stack(void)
{
    struct stack *stack = NULL;
    stack_free(&stack, NULL);

    cl_assert(stack == NULL);
}

void test_stack__pop_from_empty_stack(void)
{
    struct stack *stack = NULL;

    cl_assert(stack_pop(&stack) == NULL);
}

void test_stack__stack_remove_middle(void)
{
    struct stack *stack = NULL;
    int a = 1;
    int b = 2;
    int c = 3;

    stack_push(&stack, &a);
    stack_push(&stack, &b);
    stack_push(&stack, &c);

    cl_assert(*((int *)stack_remove(&stack, &b)) == 2);
    cl_assert(*((int *)stack_pop(&stack)) == 3);
    cl_assert(*((int *)stack_pop(&stack)) == 1);
}

void test_stack__stack_remove_first(void)
{
    struct stack *stack = NULL;
    int a = 1;
    int b = 2;
    int c = 3;

    stack_push(&stack, &a);
    stack_push(&stack, &b);
    stack_push(&stack, &c);

    cl_assert(*((int *)stack_remove(&stack, &a)) == 1);
    cl_assert(*((int *)stack_pop(&stack)) == 3);
    cl_assert(*((int *)stack_pop(&stack)) == 2);
}

void test_stack__stack_remove_last(void)
{
    struct stack *stack = NULL;
    int a = 1;
    int b = 2;
    int c = 3;

    stack_push(&stack, &a);
    stack_push(&stack, &b);
    stack_push(&stack, &c);

    cl_assert(*((int *)stack_remove(&stack, &c)) == 3);
    cl_assert(*((int *)stack_pop(&stack)) == 2);
    cl_assert(*((int *)stack_pop(&stack)) == 1);
}
