#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

struct avltree
{
    struct node *root;
    size_t size;
};

struct node
{
    struct node *parent;
    struct node *left;
    struct node *right;
    long value;
};

/**
 * Create a new node with the given value that has no parent or children.
 */
static struct node *new_node(long value);

/**
 * Replace node x with node y. Only node y may be null.
 */
static void replace_node(struct node *x, struct node *y);

AvlTree *avltree_new(void)
{
    AvlTree *tree = malloc(sizeof(*tree));

    if (tree != NULL)
    {
        tree->root = NULL;
        tree->size = 0;
    }

    return tree;
}

void avltree_delete(AvlTree *tree)
{
    struct node *curr = tree->root;

    while (curr != NULL)
    {
        if (curr->left != NULL)
            curr = curr->left;
        else if (curr->right != NULL)
            curr = curr->right;
        else
        {
            struct node *p = curr->parent;

            if (p != NULL)
            {
                if (curr == p->left)
                    p->left = NULL;
                else
                    p->right = NULL;
            }

            free(curr);
            curr = p;
        }
    }

    free(tree);
}

void avltree_add(AvlTree *tree, long elem)
{
    /*
    Find the node `x` which is to become the parent of the new node.

    The double pointer `dst` is used to keep track of which side of `x` to
    update. Conveniently, this also handles updating the root pointer of an
    empty tree.
    */

    struct node **dst = &tree->root, *x = tree->root;

    while (*dst != NULL)
    {
        x = *dst;

        // element is already present
        if (elem == x->value)
            return;

        dst = elem < x->value ? &x->left : &x->right;
    }

    (*dst = new_node(elem))->parent = x;

    tree->size++;
}

void avltree_remove(AvlTree *tree, long elem)
{
    // find node to delete
    struct node *x = tree->root;

    while (x != NULL)
    {
        if (elem == x->value)
            break;

        x = elem < x->value ? x->left : x->right;
    }

    // delete node, if exists
    if (x != NULL)
    {
        struct node *y = NULL;

        if (x->left != NULL)
        {
            y = x->left;

            while (y->right != NULL)
                y = y->right;

            if (y == x->left)
                x->left = y->left;
            else
                y->parent->right = y->left;

            if (y->left != NULL)
                y->left->parent = y->parent;
        }
        else if (x->right != NULL)
        {
            y = x->right;

            while (y->left != NULL)
                y = y->left;

            if (y == x->right)
                x->right = y->right;
            else
                y->parent->left = y->right;

            if (y->right != NULL)
                y->right->parent = y->parent;
        }

        replace_node(x, y);

        if (x->parent == NULL)
            tree->root = y;

        free(x);
        tree->size--;
    }
}

bool avltree_contains(AvlTree *tree, long elem)
{
    struct node *curr = tree->root;

    while (curr != NULL)
    {
        if (elem == curr->value)
            return true;

        curr = elem < curr->value ? curr->left : curr->right;
    }
    return false;
}

size_t avltree_size(AvlTree *tree)
{
    return tree->size;
}

static void debug_json(struct node *node)
{
    if (node != NULL)
    {
        printf("{\"value\":");
        printf("%li", node->value);
        printf(",\"left\":");
        debug_json(node->left);
        printf(",\"right\":");
        debug_json(node->right);
        printf("}");
    }
    else
        printf("null");
}

void avltree_debug(AvlTree *tree)
{
    debug_json(tree->root);
    putchar('\n');
}

struct node *new_node(long value)
{
    struct node *n = malloc(sizeof(*n));

    if (n != NULL)
    {
        n->parent = NULL;
        n->left = NULL;
        n->right = NULL;
        n->value = value;
    }

    return n;
}

void replace_node(struct node *x, struct node *y)
{
    struct node *p = x->parent,
                *l = x->left,
                *r = x->right;

    if (p != NULL)
        *(x == p->left ? &p->left : &p->right) = y;

    if (l != NULL)
        l->parent = y;

    if (r != NULL)
        r->parent = y;

    if (y != NULL)
    {
        y->parent = p;
        y->left = l;
        y->right = r;
    }
}
