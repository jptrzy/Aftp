#include "node.h"
#include <cstddef>
#include <stdlib.h>

void free_node(Node* node) {
  if (!node) return;

  free_node(node->first_child);

  free_node(node->sibling);

  free(node->name);
  free(node);
}

void generate_name(char* buffer, int max_length) {
  int length = rand() % (max_length - 1) + 1;

  for (int i = 0; i < length; i++) {
    buffer[i] = (rand() % 26) + 'A';
  }

  buffer[length] = '\0';
}

void generate_children(Node* parent, int depth, int max_nodes) {
  int amount = rand() % max_nodes;
  Node* last_child = NULL;

  for (int i=0; i <= amount; i++) {
    Node* child = (Node*)malloc(sizeof(Node));

    child->name = (char*)malloc(8);
    generate_name(child->name, 8);
    child->first_child = NULL;
    child->sibling = last_child;

    if (depth > 0) {
      generate_children(child, depth-1, max_nodes);
    }

    last_child = child;
  }
  
  parent->first_child = last_child;
}

Node* generate_node_tree(int depth, int max_nodes) {
  Node* root = (Node*)malloc(sizeof(Node));
  root->name = (char*)malloc(8);
  generate_name(root->name, 8);
  root->first_child = NULL;
  root->sibling = NULL;

  generate_children(root, depth-1, max_nodes);

  return root;
}
