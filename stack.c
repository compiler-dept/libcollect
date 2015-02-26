#include <stdlib.h>
#include "stack.h"

void stack_push(struct stack **stack, void *elem)
{
    if (elem) {
        struct stack *newhead = malloc(sizeof(struct stack));
        newhead->head = elem;
        newhead->tail = *stack;
        *stack = newhead;
    }
}

void *stack_peek(struct stack *stack)
{
    if (stack) {
        return stack->head;
    } else {
        return NULL;
    }
}

void *stack_pop(struct stack **stack)
{
    if (*stack) {
        void *elem = (*stack)->head;
        struct stack *temp = *stack;
        *stack = (*stack)->tail;
        free(temp);
        return elem;
    } else {
        return NULL;
    }
}

void stack_free(struct stack **stack, void (*payload_free) (void *))
{
    if (*stack) {
        if ((*stack)->tail) {
            stack_free(&((*stack)->tail), payload_free);
        }

        if (payload_free) {
            payload_free((*stack)->head);
        }
        free(*stack);
        *stack = NULL;
    }
}
