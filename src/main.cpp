#include "node.h"
#include "print.h"

#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  Node* root = generate_node_tree(4, 4);

  pretty_print(root);

  free_node(root);

  return 0;
}
