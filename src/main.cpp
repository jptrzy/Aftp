#include "node.h"

#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));

  Node root = Node::generate_node_tree(4, 4);

  root.print();

  return 0;
}
