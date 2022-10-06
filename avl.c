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
    struct node *new_node;

    // find where to insert new node
    struct node *prev = NULL, *curr = tree->root;

    while (curr != NULL)
    {
        // element is already present
        if (elem == curr->value)
            return;

        prev = curr;
        curr = elem < curr->value ? curr->left : curr->right;
    }

    new_node = malloc(sizeof(*new_node));
    new_node->parent = prev;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->value = elem;

    if (prev != NULL)
    {
        if (elem < prev->value)
            prev->left = new_node;
        else
            prev->right = new_node;
    }
    else
    {
        // new_node is the only node in the tree
        tree->root = new_node;
    }

    tree->size++;
}

void avltree_remove(AvlTree *tree, long elem)
{
    // find node to delete
    struct node *rm = tree->root;

    while (rm != NULL)
    {
        if (elem == rm->value)
            break;

        rm = elem < rm->value ? rm->left : rm->right;
    }

    // delete node, if exists
    if (rm != NULL)
    {
        struct node *replace;

        // find replacement
        if (rm->left != NULL)
        {
            replace = rm->left;

            while (replace->right != NULL)
                replace = replace->right;
        }
        else
        {
            replace = rm->right;
        }

        // make replacement
        if (replace != NULL)
            replace->parent = rm->parent;

        if (rm->parent != NULL)
        {
            if (rm == rm->parent->left)
                rm->parent->left = replace;
            else
                rm->parent->right = replace;
        }
        else
        {
            tree->root = replace;
        }

        free(rm);
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
