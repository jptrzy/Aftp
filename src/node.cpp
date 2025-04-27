#include "node.h"
#include <iostream>
#include <queue>

std::string generate_name(int max_length) {
  std::string name = ""; 

  int length = rand() % (max_length - 1) + 1;

  while (length-- >= 0) {
    name += (rand() % 26) + 'A';
  }

  return name;
}

Node::Node(std::string name) {
  this->name = name;
}

void generate_children(Node* parent, int depth, int max_nodes) {
  int amount = rand() % max_nodes;

  for (int i=0; i <= amount; i++) {
    Node child = Node(generate_name(3)); 

    if (depth > 0) {
      generate_children(&child, depth-1, max_nodes);
    }

    parent->childs.push_back(child);
  }
}

Node Node::generate_node_tree(int depth, int max_nodes) {
  Node root = Node(generate_name(3));

  generate_children(&root, depth-1, max_nodes);

  std::cout << root.childs.size() << '\n';

  return root;
}

void _print(Node* node, std::string prefix, bool root=false, bool last=false) {
  std::string new_prefix;

  std::cout << prefix;

  if (!root) {
    std::cout << (last ? "└─" : "├─");

    new_prefix = prefix + (last ? "  " : "│ ");
  }

  std::cout << node->name << std::endl;

  for(auto& child : node->childs) {
    _print(&child, new_prefix, false, &child == &node->childs.back());
  }
}

void Node::print() {
  _print(this, "", true);
}


Node* Node::find_by_name(std::string name) {
  std::queue<Node*> que;
  que.push(this);

  while (!que.empty()) {
    Node* node = que.front();

    std::cout << node->name << std::endl;

    if (node->name == name) return node;

    for (auto& child : node->childs) {
      que.push(&child);
    }

    que.pop();
  }

  return NULL;
}
