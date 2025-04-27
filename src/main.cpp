#include "node.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

/* EXAMPLE */
int main() {
  //srand(time(NULL));
  srand(0);

  Node root_a = Node::generate_node_tree(4, 4);
  Node root_b = Node::generate_node_tree(4, 4);

  root_a.print();
  //root_b.print();

  Node* x = root_a.find_by_name("AQ");

  if (x) {
    x->print();
  } else {
    std::cout << "Not found" << std::endl;
  }

  return 0;
}
