/**
 * @file  stack.h
 * @brief Generic Stack
 */

#ifndef STACK_H
#define STACK_H

/**
 * @brief stack element struct
 */
struct stack {
    void *head;         ///< pointer to payload
    struct stack *tail; ///< next stack element
};

/**
 * @brief push an element onto the stack
 *
 * If *stack is NULL, a new stack is initialized.
 * \param stack pointer to the pointer of the stack struct
 * \param elem pointer to the payload
 */
void stack_push(struct stack **stack, void *elem);

/**
 * @brief peek at the first element of the stack
 *
 * This method does not alter the stack.
 * \param stack pointer to the stack struct
 */
void *stack_peek(struct stack *stack);

/**
 * @brief pop an element from the stack
 *
 * \param stack pointer to the pointer of the stack struct
 */
void *stack_pop(struct stack **stack);

/**
 * @brief free a stack
 *
 * \param stack pointer to the pointer of the stack struct
 */
void stack_free(struct stack **stack);

#endif /* STACK_H */
