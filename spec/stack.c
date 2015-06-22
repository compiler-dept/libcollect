#include "../speck.h"

#include "../stack.h"

void spec_push_pop_equality(void)
{
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    struct stack *stack = NULL;

    for (int i = 0; i < 10; i++) {
        stack_push(&stack, values + i);
    }

    sp_assert(stack != NULL);

    for (int i = 9; i > 2; i--) {
        int *val = (int *)stack_pop(&stack);
        sp_assert(val == values + i);
    }

    stack_free(&stack, NULL);
}

void spec_free_empty_stack(void)
{
    struct stack *stack = NULL;
    stack_free(&stack, NULL);

    sp_assert(stack == NULL);
}

void spec_pop_from_empty_stack(void)
{
    struct stack *stack = NULL;

    sp_assert(stack_pop(&stack) == NULL);
}

void spec_stack_remove_middle(void)
{
    struct stack *stack = NULL;
    int a = 1;
    int b = 2;
    int c = 3;

    stack_push(&stack, &a);
    stack_push(&stack, &b);
    stack_push(&stack, &c);

    sp_assert(*((int *)stack_remove(&stack, &b)) == 2);
    sp_assert(*((int *)stack_pop(&stack)) == 3);
    sp_assert(*((int *)stack_pop(&stack)) == 1);
}

void spec_stack_remove_first(void)
{
    struct stack *stack = NULL;
    int a = 1;
    int b = 2;
    int c = 3;

    stack_push(&stack, &a);
    stack_push(&stack, &b);
    stack_push(&stack, &c);

    sp_assert(*((int *)stack_remove(&stack, &a)) == 1);
    sp_assert(*((int *)stack_pop(&stack)) == 3);
    sp_assert(*((int *)stack_pop(&stack)) == 2);
}

void spec_stack_remove_last(void)
{
    struct stack *stack = NULL;
    int a = 1;
    int b = 2;
    int c = 3;

    stack_push(&stack, &a);
    stack_push(&stack, &b);
    stack_push(&stack, &c);

    sp_assert(*((int *)stack_remove(&stack, &c)) == 3);
    sp_assert(*((int *)stack_pop(&stack)) == 2);
    sp_assert(*((int *)stack_pop(&stack)) == 1);
}
