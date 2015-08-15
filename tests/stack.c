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

void test_stack__stack_size(void)
{
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    struct stack *stack = NULL;

    for (int i = 0; i < 10; i++) {
        stack_push(&stack, values + i);
    }

    cl_assert(stack_size(stack) == 10);

    stack_free(&stack, NULL);
}
