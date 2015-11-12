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

int stack_size(struct stack *stack)
{
    if (!stack) {
        return 0;
    }

    return 1 + stack_size(stack->tail);
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

void *stack_remove(struct stack **stack, const void *elem)
{
    void *ret = NULL;

    if (*stack) {
        struct stack *temp = NULL;
        struct stack *prev = NULL;
        for (temp = *stack; temp != NULL; temp = temp->tail) {
            if (temp->head == elem) {
                if (prev) {
                    prev->tail = temp->tail;
                } else {
                    *stack = temp->tail;
                }
                ret = temp->head;
                free(temp);
                break;
            }

            prev = temp;
        }
    }

    return ret;
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
