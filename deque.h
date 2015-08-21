#ifndef DEQUE_H
#define DEQUE_H

/**
 * @file  deque.h
 * @brief Generic Double Ended Queue
 */

/**
 * @brief queue structure
 */
struct deque {
    struct deque_node *head;         ///< pointer to first node
	struct deque_node *tail;         ///< pointer to last node
};


/**
 * @brief queue node structure
 */
struct deque_node {
    struct deque_node *prev;         ///< pointer to previous node
	struct deque_node *next;         ///< pointer to next node
	void *elem;						 ///< pointer to element payload
};

/**
 * @brief push element to front of deque
 *
 * If *deque is NULL, a new deque is initialized.
 * \param deque pointer to the pointer of the deque struct
 * \param elem pointer to the payload
 */
void deque_push_first(struct deque **deque, void *elem);

/**
 * @brief push element to back of the deque
 *
 * If *deque is NULL, a new deque is initialized.
 * \param deque pointer to the pointer of the deque struct
 * \param elem pointer to the payload
 */
void deque_push_last(struct deque **deque, void *elem);


/**
 * @brief pop an element from the front of the deque
 *
 * \param deque pointer to the pointer of the deque struct
 */
void *deque_pop_first(struct deque **deque);


/**
 * @brief pop an element from the back of the deque
 *
 * \param deque pointer to the pointer of the deque struct
 */
void *deque_pop_last(struct deque **deque);

/**
 * @brief free a deque
 *
 * \param deque pointer to the pointer of the deque struct
 * \param pointer to custom payload free function
 */
void deque_free(struct deque **deque, void (*payload_free) (void *));

#endif
