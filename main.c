#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

int main(int argc, char const *argv[])
{
    AvlTree *tree;

    tree = avltree_new();

    for (int i = 1; i < argc; i++)
    {
        char const *s = argv[i];

        if (s[0] == '-')
            avltree_remove(tree, atol(&s[1]));
        else
            avltree_add(tree, atol(s));
    }

    avltree_debug(tree);
    avltree_delete(tree);

    return EXIT_SUCCESS;
}
