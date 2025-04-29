#include "node.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <thread>
#include <future>

void find_in_thread(Node& root, std::string target, std::promise<Node*> prom) {
    Node* result = root.find_by_name(target);
    prom.set_value(result);
}

/* EXAMPLE */
int main() {
  //srand(time(NULL));
  
  // Set to specific value so there would be no randomness for this example
  // This helps, so the value to find_by could be specified beforehand
  srand(0);

  Node root_a = Node::generate_node_tree(4, 4);
  Node root_b = Node::generate_node_tree(4, 4);

  std::promise<Node*> root_a_prom;
  std::promise<Node*> root_b_prom;

  std::future<Node*> root_a_fut = root_a_prom.get_future();
  std::future<Node*> root_b_fut = root_b_prom.get_future();

  std::thread root_a_t(find_in_thread, std::ref(root_a), "AQ", std::move(root_a_prom));
  std::thread root_b_t(find_in_thread, std::ref(root_b), "AQ", std::move(root_b_prom));

  root_a_t.join();
  root_b_t.join();

  Node* root_a_r = root_a_fut.get();
  Node* root_b_r = root_b_fut.get();

  if (root_a_r) {
      std::cout << "Found node: " << root_a_r->name << std::endl;
  } else {
      std::cout << "Node not found." << std::endl;
  }

  if (root_b_r) {
      std::cout << "Found node: " << root_b_r->name << std::endl;
  } else {
      std::cout << "Node not found." << std::endl;
  }

  return 0;
}
