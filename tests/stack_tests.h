#include "../stack.h"

void test_push_pop_equality(void)
{
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    struct stack *stack = NULL;

    for (int i = 0; i < 10; i++) {
        stack_push(&stack, values + i);
    }

    CU_ASSERT(stack != NULL);

    for (int i = 9; i > 2; i--) {
        int *val = (int *)stack_pop(&stack);
        CU_ASSERT(val == values + i);
    }

    stack_free(&stack);
}

void test_free_empty_stack(void)
{
    struct stack *stack = NULL;
    stack_free(&stack);

    CU_ASSERT(stack == NULL);
}

void test_pop_from_empty_stack(void)
{
    struct stack *stack = NULL;

    CU_ASSERT(stack_pop(&stack) == NULL);
}
