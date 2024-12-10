#include "string_tree.h"

#include <fstream>
#include <string>

using namespace std;

StringTree::StringTree(istream& input) {
  // TODO_STUDENT
  // Must be one line long that calls a recursive helper
  root = deserializer(input);
}

void StringTree::serialize(ostream& output) {
  // TODO_STUDENT
  // Must be one line long that calls a recursive helper
  serializer(root, output);
}

StringTree::~StringTree() {
  // TODO_STUDENT
  // Must be one line long that calls a recursive helper
  deletetree(root);
}

StringTreeNode* StringTree::deserializer(istream& input) {
  string line;
  if (!getline(input, line)) {
    return nullptr;
  }

  char type = line[0];
  string data = line.substr(3);

  StringTreeNode* node = new StringTreeNode(data);

  if (type == 'I') {
    node->left = deserializer(input);
    node->right = deserializer(input);
  }

  return node;
}

void StringTree::serializer(StringTreeNode* node, ostream& output) {
  if (node == nullptr) {
    return;
  }

  if (node->left == nullptr && node->right == nullptr) {
    output << "L: " << node->data << "\n";
  } else {
    output << "I: " << node->data << "\n";
  }

  serializer(node->left, output);
  serializer(node->right, output);
}

void StringTree::deletetree(StringTreeNode* node) {
  if (node == nullptr) {
    return;
  }
  deletetree(node->left);
  deletetree(node->right);
  delete node;
}