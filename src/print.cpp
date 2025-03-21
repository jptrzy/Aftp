#include "node.h"
#include <iostream>

void _simple_print(Node* node, int depth) {

  for (int i = 0; i < depth; i++) std::cout << "  ";
  std::cout << node->name << "\n";

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
