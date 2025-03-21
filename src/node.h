#ifndef NODE_HEADER
#define NODE_HEADER


/*
 *
 * We store children in (abstracted) linked list.
 *
 * This comes with multiple drawbacks, mostly in terms of flexibility,
 * but for such a simple issue (of printing a tree) it should be perfect.
 *
 * Explained in more detail at:
 * https://www.geeksforgeeks.org/generic-treesn-array-trees/
 *
 */


typedef struct Node {
  char* name;

  Node* first_child;
  Node* sibling;
} Node;

Node* generate_node_tree(int depth, int max_nodes);

void free_node(Node* node);

#endif
