#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

/**
 * @file  array_list.h
 * @brief Generic Array List
 */

#ifndef ARRAY_LIST_INITIAL_CAPACITY
#define ARRAY_LIST_INITIAL_CAPACITY_EXPONENT 5 ///< default array list init capacity (2^5 = 32)
#endif

/**
 * @brief Array list chunk struct
 */
struct array_list {
    struct array_list *next; ///< Pointer to the next chunk
    int arc;                 ///< Length of the chunks array
    void *arv[];             ///< The chunks array
};

/**
 * @brief Insert value into array list.
 *
 * If *al is NULL, allocate new array list and expand it to the right size.
 * The size of the array list grows while beeing used in
 * 2^n (1, 1, 2, 4, 8, ...).
 *
 * \param al Pointer to the pointer of the array list struct
 * \param idx Index of the array, at which the element is inserted
 * \param elem Pointer to payload/value
 *
 * \return Nothing
 */
void array_list_set(struct array_list **al, int idx, void *elem);

/**
 * @brief Get value from array list.
 *
 * \param al Pointer to the pointer of the array list struct
 * \param idx Index of the array, at which the element is inserted
 *
 * \return Pointer to the payload/value
 */
void *array_list_get(struct array_list **al, int idx);

#endif
