#ifndef STACK_H
#define STACK_H

/**
 * @file  stack.h
 * @brief Generic Stack
 */

/**
 * @brief stack element structure
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
void *stack_peek(struct stack *const *stack);

/**
 * @brief pop an element from the stack
 *
 * \param stack pointer to the pointer of the stack struct
 */
void *stack_pop(struct stack **stack);

/**
 * @brief get number of elements on stack
 *
 * \param stack pointer to the stack struct
 */
int stack_size(struct stack *const *stack);

/**
 * @brief removes specific element from the stack
 *
 * \param stack pointer to the pointer of the stack struct
 * \param elem pointer the element that should be removed
 */
void *stack_remove(struct stack **stack, const void *elem);

/**
 * @brief free a stack
 *
 * \param stack pointer to the pointer of the stack struct
 * \param pointer to custom payload free function
 */
void stack_free(struct stack **stack, void (*payload_free)(void *));

#endif /* STACK_H */
