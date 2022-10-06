#ifndef AVL_H_
#define AVL_H_

#include <stdbool.h>
#include <stddef.h>

/**
 * An AVL tree is a self-balancing binary search tree.
 */
typedef struct avltree AvlTree;

/**
 * Create a new AvlTree object.
 */
extern AvlTree *avltree_new(void);

/**
 * Delete an AvlTree object.
 */
extern void avltree_delete(AvlTree *tree);

/**
 * Add an element to the tree.
 *
 * This has no effect if the element is already present.
 */
extern void avltree_add(AvlTree *tree, long elem);

/**
 * Remove an element from the tree.
 *
 * This has no effect if the element is not present.
 */
extern void avltree_remove(AvlTree *tree, long elem);

/**
 * Return true if the tree contains the given element.
 */
extern bool avltree_contains(AvlTree *tree, long elem);

/**
 * Return the number of elements in the tree.
 */
extern size_t avltree_size(AvlTree *tree);

/**
 * Print debug information about tree.
 */
extern void avltree_debug(AvlTree *tree);

#endif
