#include "node.h"
#include <iostream>
#include <string.h>

void _simple_print(Node* node, int depth) {

  for (int i = 0; i < depth; i++) printf("  ");
  printf("%s\n", node->name);

  if (node->first_child) {
    _simple_print(node->first_child, depth+1);
  }

  if (node->sibling) {
    _simple_print(node->sibling, depth);
  }
}

void simple_print(Node* root) {
  _simple_print(root, 0);
}


/*
 *
 * Over complication caused by usage of sibling tree storing method.
 *
 * TODO Could be made more efficient, if only one string is used for prefix
 *
 */

void _pretty_print(Node* node, bool root, const char* prefix) {
  printf("%s", prefix);

  if (!root) {
    if (node->sibling) {
      printf("├─");
    } else {
      printf("└─");
    }
  }

  printf ("%s\n", node->name);

  if (node->first_child) {
    char new_prefix[512];
    strcpy(new_prefix, prefix);
    if (!root) {
      strcat(new_prefix, node->sibling ? "│ " : "  ");
    }
    _pretty_print(node->first_child, false, new_prefix);
  }

  if (node->sibling) {
    _pretty_print(node->sibling, false, prefix);
  }
}

void pretty_print(Node* root) {
  _pretty_print(root, true, "");
}
