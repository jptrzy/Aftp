#include "node.h"
#include "print.h"

#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  Node* root = generate_node_tree(2, 4);

  simple_print(root);

  free_node(root);

  return 0;
}
