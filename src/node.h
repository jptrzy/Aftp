#ifndef NODE_HEADER
#define NODE_HEADER

#include <string>
#include <vector>
#include <memory>

class Node {
public:
  std::string name;
  std::vector<std::shared_ptr<Node>> childs;

  Node(std::string name);

  static Node generate_node_tree(int depth, int max_nodes);

  void print();

  Node* find_by_name(std::string name);
};

#endif
