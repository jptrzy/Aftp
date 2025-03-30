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
 */

void _pretty_print(Node* node, char** prefix, bool root) {
  printf("%s", *prefix);

  if (!root) {
    if (node->sibling) {
      printf("├─");
    } else {
      printf("└─");
    }
  }

  printf ("%s\n", node->name);

  if (node->first_child) {
    int len = strlen(*prefix);

    if (!root) {
      strcat(*prefix, node->sibling ? "│ " : "  ");
    }
    _pretty_print(node->first_child, prefix, false);

    (*prefix)[len] = '\0';
  }

  if (node->sibling) {
    _pretty_print(node->sibling, prefix, false);
  }
}

void pretty_print(Node* root) {
  /*
   * If we expect the terminal to be 80 chars in width, then buffer is:
   * 256 bytes > 40 * 3 (amount of bytes for │ symbol in utf-8) + 40
   */
  char* buffer = (char*) malloc(sizeof(char) * 256);
  strcpy(buffer, "\0");

  _pretty_print(root, &buffer, true);

  free(buffer);
}
