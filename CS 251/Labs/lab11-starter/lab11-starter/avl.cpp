#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_set>

#include "avl.h"

using namespace std;

void AVLTree::_insert(Node*& curr, int value) {
  // Find place to insert in BST, which preserves the BST property.
  if (curr == nullptr) {
    curr = new Node;
    curr->data = value;
    curr->left = nullptr;
    curr->right = nullptr;
    this->size++;
  } else if (curr->data > value) {
    _insert(curr->left, value);
  } else {
    _insert(curr->right, value);
  }

  // Update the height of the node.
  curr->height = _max(_getHeight(curr->left), _getHeight(curr->right)) + 1;

  // Check if the current node breaks the AVL property.
  // If it does, then do the proper rotations.
  int balance = _getBalance(curr);

  // Right Rotation Case: Uncomment for task 1.4 
  if (balance > 1 && value < curr->left->data) {
    _rightRotate(curr);
  }

  // Left Rotation Case: Uncomment for task 2.4
  else if (balance < -1 && value > curr->right->data) {
    _leftRotate(curr);
  }

  // Right Left Rotation Case: Uncomment for task 3
  else if (balance < -1 && value < curr->right->data) {
    _rightRotate(curr->right);
    _leftRotate(curr);
  }

  // Left Right Rotation Case: Uncomment for task 4
  else if (balance > 1 && value > curr->left->data) {
    _leftRotate(curr->left);
    _rightRotate(curr);
  }
}

void AVLTree::insert(int value) {
    _insert(root, value);
}

void AVLTree::_rightRotate(Node*& N) {
  // N is the node on which we are rotating to the right.
  
  // 1. Assign nodes L and B
  // TODO BY STUDENT
  Node* L = N->left;
  Node* B = L->right;

  // 2. Perform Rotation.
  // TODO BY STUDENT
  N->left = B;
  L->right = N;


  // 3. Update the heights.
  // TODO BY STUDENT
  N->height = _max(_getHeight(N->left), _getHeight(N->right)) + 1;
  L->height = _max(_getHeight(L->left), _getHeight(L->right)) + 1;

  // 4. Update N's former parent to point to L.
  N = L;
}

void AVLTree::_leftRotate(Node*& N) {
  // N is the node on which we are rotating to the left.

  // 1. Assign nodes R and B.
  // TODO BY STUDENT
  Node* R = N->right;
  Node* B = R->left;

  // 2. Perform Rotation.
  // TODO BY STUDENT
  N->right = B;
  R->left = N;

  // 3. Update the heights.
  // TODO BY STUDENT
  N->height = _max(_getHeight(N->left), _getHeight(N->right)) + 1;
  R->height = _max(_getHeight(R->left), _getHeight(R->right)) + 1;

  // 4. Update N's former parent to point to R.
  N = R;
}

int main() {
    AVLTree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10); // triggers Right Rotation

    //Uncomment for part 2
    tree.insert(40);
    tree.insert(50); // triggers Left Rotation*/

    //Uncomment for part 3
    tree.insert(25); // triggers RL

    // Uncomment for part 4
    tree.insert(5);
    tree.insert(22);
    tree.insert(23); // triggers LR*/

    cout << tree.toString() << endl;
}