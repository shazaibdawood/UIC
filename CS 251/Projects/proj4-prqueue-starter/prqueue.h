#pragma once

#include <iostream>  // For debugging
#include <sstream>   // For as_string

using namespace std;

template <typename T>
class prqueue {
 public:
  struct NODE {
    int priority;
    T value;
    NODE* parent;
    NODE* left;
    NODE* right;
    NODE* link;  // Link to duplicates -- Part 2 only
  };

 private:
  NODE* root;
  size_t sz;

  // Utility pointers for begin and next.
  NODE* curr;
  NODE* temp;  // Optional

  // TODO_STUDENT: add private helper function definitions here
  void createNode(NODE* newNode, T value, int priority) {
    newNode->priority = priority;
    newNode->value = value;
    newNode->parent = nullptr;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->link = nullptr;
  }

  void newRoot() {
    if (root == nullptr || root->left != nullptr || root->right == nullptr) {
      return;
    }

    NODE* newRoot = root->right;
    while (newRoot->left != nullptr) {
      newRoot = newRoot->left;
    }

    T tempValue;
    int tempPriority;
    bool addNode = false;
    if (newRoot->right != nullptr) {
      tempValue = newRoot->right->value;
      tempPriority = newRoot->priority;
      addNode = true;
      delete (newRoot->right);
      sz--;
    }

    NODE* tempParent = newRoot->parent;
    tempParent->left = nullptr;

    newRoot->left = root->left;
    newRoot->right = root->right;
    newRoot->parent = root->parent;
    delete (root);
    sz--;
    root = newRoot;

    if (addNode) {
      enqueue(tempValue, tempPriority);
    }
  }

 public:
  /// Creates an empty `prqueue`.
  ///
  /// Runs in O(1).
  prqueue() {
    // TODO_STUDENT
    root = nullptr;
    sz = 0;
    curr = nullptr;
    temp = nullptr;
  }

  /// Returns the number of elements in the `prqueue`.
  ///
  /// Runs in O(1).
  size_t size() const {
    // TODO_STUDENT
    return sz;
  }

  /// Returns a pointer to the root node of the BST.
  ///
  /// Used for testing the internal structure of the BST. Do not edit or
  /// change.
  ///
  /// Runs in O(1).
  NODE* getRoot() const {
    // TODO_STUDEN

    return root;
  }

  /// Adds `value` to the `prqueue` with the given `priority`.
  ///
  /// Uses the priority to determine the location in the underlying tree.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.
  void enqueue(T value, int priority) {
    // TODO_STUDENT
    NODE* newNode = new NODE;
    createNode(newNode, value, priority);

    // cout << "Inserting " << value << "\t" << priority << endl;

    if (root == nullptr) {
      // cout << "root" << endl;
      root = newNode;
      sz++;
      return;
    }

    // NODE* older = root;
    // NODE* younger = nullptr;
    // if (priority < older->priority) {
    //   younger = root->left;
    // } else {
    //   younger = root->right;
    // }

    // while (younger != nullptr) {
    //   older = younger;
    //   if (priority < older->priority) {
    //     younger = younger->left;
    //   } else {
    //     younger = younger->right;
    //   }
    // }

    // newNode->parent = older;
    // if (priority < older->priority) {
    //   older->left = newNode;
    // } else {
    //   older->right = newNode;
    // }

    NODE* insertNode = root;
    NODE* parent = nullptr;
    while ((insertNode != nullptr)) {
      parent = insertNode;

      if (priority > insertNode->priority) {
        // cout << "right child" << endl;
        insertNode = insertNode->right;
      } else if (priority < insertNode->priority) {
        // cout << "left child" << endl;
        insertNode = insertNode->left;
      } else {
        // duplicate
        while (insertNode->link != nullptr) {
          insertNode = insertNode->link;
        }
        // cout << "duplicate child" << endl;
        newNode->left = parent->left;
        newNode->right = parent->right;
        newNode->parent = parent->parent;
        insertNode->link = newNode;
        sz++;
        return;
      }
    }

    newNode->parent = parent;
    if (priority > parent->priority) {
      parent->right = newNode;
    } else {
      parent->left = newNode;
    }

    sz++;
  }

  /// Returns the value with the smallest priority in the `prqueue`, but does
  /// not modify the `prqueue`.
  ///
  /// If the `prqueue` is empty, returns the default value for `T`.
  ///
  /// Runs in O(H + M), where H is the height of the tree, and M is
  /// the number of duplicate priorities.
  T peek() const {
    // TODO_STUDENT
    if (size() == 0) {
      return T{};
    }

    NODE* youngest = root;
    while (youngest->left != nullptr) {
      youngest = youngest->left;
    }

    return youngest->value;
  }

  // / Returns the value with the smallest priority in the `prqueue` and
  // / removes it from the `prqueue`.
  // /
  // / If the `prqueue` is empty, returns the default value for `T`.
  // /
  // / Runs in O(H + M), where H is the height of the tree, and M is
  // / the number of duplicate priorities.
  T dequeue() {
    // TODO_STUDENT

    // Empty
    // Only root
    // Root with only right child
    // left leaf
    // left parent
    if (size() == 0) {  // Empty
      return T{};
    }

    NODE* youngest = root;
    while (youngest->left != nullptr) {
      youngest = youngest->left;
    }

    NODE* tempParent = youngest->parent;
    T smallest = youngest->value;

    if (youngest->link != nullptr) {
      NODE* temp = youngest->link;
      temp->left = youngest->left;
      temp->right = youngest->right;

      if (temp->right != nullptr) {
        temp->right->parent = temp;
      }

      if (tempParent != nullptr) {
        tempParent->left = temp;
      } else {
        root = temp;
      }
      temp->parent = tempParent;

    } else {
      if (root == youngest && sz == 1) {  // only root
        root = nullptr;
        delete (youngest);
        sz--;
        return smallest;
      }
      if (root == youngest && youngest->right != nullptr) {
        root = youngest->right;
        root->parent = nullptr;
        delete (youngest);
        sz--;
        return smallest;
      }
      if (youngest->right != nullptr) {
        tempParent->left = youngest->right;
        youngest->right->parent = tempParent;
      } else {
        tempParent->left = nullptr;
      }
    }

    delete (youngest);
    sz--;
    return smallest;
  }

  void stringInorderTraversal(NODE* current,
                              stringstream& inorderString) const {
    if (current == nullptr) {
      return;
    }

    stringInorderTraversal(current->left, inorderString);

    NODE* temp = current;
    while (temp != nullptr) {
      inorderString << temp->priority << " value: " << temp->value << "\n";
      temp = temp->link;
    }

    stringInorderTraversal(current->right, inorderString);
  }

  /// Converts the `prqueue` to a string representation, with the values
  /// in-order by priority.
  ///
  /// Example:
  ///
  /// ```c++
  /// prqueue<string> names;
  /// names.enqueue("Gwen", 3);
  /// names.enqueue("Jen", 2);
  /// names.enqueue("Ben", 1);
  /// names.enqueue("Sven", 2);
  /// ```
  ///
  /// Calling `names.as_string()` would return the following multi-line
  /// string:
  ///
  /// ```text
  /// 1 value: Ben
  /// 2 value: Jen
  /// 2 value: Sven
  /// 3 value: Gwen
  /// ```
  ///
  /// Runs in O(N), where N is the number of values.
  string as_string() const {
    // TODO_STUDENT

    stringstream inorderString;
    stringInorderTraversal(root, inorderString);

    return inorderString.str();
  }

  void clearPostOrderTraversal(NODE* current) {
    if (current == nullptr) {
      return;
    }
    clearPostOrderTraversal(current->left);
    clearPostOrderTraversal(current->right);
    while (current->link != nullptr) {
      NODE* temp = current->link;
      delete (current);
      current = temp;
      // NODE* temp = current->link;
      // NODE* temp2 = temp->link;
      // delete (temp);
      // temp = temp2;
    }

    delete (current);
  }

  /// Empties the `prqueue`, freeing all memory it controls.
  ///
  /// Runs in O(N), where N is the number of values.
  void clear() {
    // TODO_STUDENT
    clearPostOrderTraversal(root);
    root = nullptr;
    sz = 0;
    curr = nullptr;
    temp = nullptr;
  }

  /// Destructor, cleans up all memory associated with `prqueue`.
  ///
  /// Runs in O(N), where N is the number of values.
  ~prqueue() {
    // TODO_STUDENT
    clear();
  }

  void copyPreOrderTraversal(NODE* copyCurrent) {
    if (copyCurrent == nullptr) {
      return;
    }

    enqueue(copyCurrent->value, copyCurrent->priority);

    NODE* copyTemp = copyCurrent->link;
    while (copyTemp != nullptr) {
      enqueue(copyTemp->value, copyTemp->priority);
      copyTemp = copyTemp->link;
    }

    copyPreOrderTraversal(copyCurrent->left);
    copyPreOrderTraversal(copyCurrent->right);
  }

  /// Copy constructor.
  ///
  /// Copies the value-priority pairs from the provided `prqueue`.
  /// The internal tree structure must be copied exactly.
  ///
  /// Runs in O(N), where N is the number of values in `other`.
  prqueue(const prqueue& other) {
    // TODO_STUDENT

    root = nullptr;
    sz = 0;
    curr = nullptr;
    temp = nullptr;

    // cout << "reached" << endl;
    if (other.getRoot() == nullptr) {
      sz = 0;
      root = nullptr;
      return;
    }

    copyPreOrderTraversal(other.getRoot());
  }

  /// Assignment operator; `operator=`.
  ///
  /// Clears `this` tree, and copies the value-priority pairs from the
  /// provided `prqueue`. The internal tree structure must be copied exactly.
  ///
  /// Runs in O(N + O), where N is the number of values in `this`, and O is
  /// the number of values in `other`.
  prqueue& operator=(const prqueue& other) {
    // TODO_STUDENT

    if (this == &other) {
      return *this;
    }

    clear();
    if (other.getRoot() == nullptr) {
      return *this;
    }

    copyPreOrderTraversal(other.getRoot());

    return *this;
  }

  bool comparePreorderTraversal(NODE* current1, NODE* current2) const {
    if (current1 == nullptr && current2 == nullptr) {
      return true;
    }

    if (current1 == nullptr || current2 == nullptr) {
      return false;
    }

    if (current1->value != current2->value ||
        current1->priority != current2->priority) {
      return false;
    }

    NODE* temp1 = current1->link;
    NODE* temp2 = current2->link;
    while (temp1 != nullptr && temp2 != nullptr) {
      if (temp1->value != temp2->value || temp1->priority != temp2->priority) {
        return false;
      }
      temp1 = temp1->link;
      temp2 = temp2->link;
    }

    if (temp1 != nullptr || temp2 != nullptr) {
      return false;
    }

    return (comparePreorderTraversal(current1->left, current2->left) &&
            comparePreorderTraversal(current1->right, current2->right));
  }

  /// Checks if the contents of `this` and `other` are equivalent.
  ///
  /// Two `prqueues` are equivalent if they have the same priorities and
  /// values, as well as the same internal tree structure.
  ///
  /// These two `prqueue`s would be considered equivalent, because
  /// they have the same internal tree structure:
  ///
  /// ```c++
  /// prqueue<string> a;
  /// a.enqueue("2", 2);
  /// a.enqueue("1", 1);
  /// a.enqueue("3", 3);
  /// ```
  ///
  /// and
  ///
  /// ```c++
  /// prqueue<string> b;
  /// a.enqueue("2", 2);
  /// a.enqueue("3", 3);
  /// a.enqueue("1", 1);
  /// ```
  ///
  /// While this `prqueue`, despite containing the same priority-value pairs,
  /// would not be considered equivalent, because the internal tree structure
  /// is different.
  ///
  /// ```c++
  /// prqueue<string> c;
  /// a.enqueue("1", 1);
  /// a.enqueue("2", 2);
  /// a.enqueue("3", 3);
  /// ```
  ///
  /// Runs in O(N) time, where N is the maximum number of nodes in
  /// either `prqueue`.
  ///
  bool operator==(const prqueue& other) const {
    // TODO_STUDENT
    if (sz == other.size()) {
      return comparePreorderTraversal(root, other.getRoot());
    } else {
      return false;
    }
  }

  // NODE* testCurr() const {
  //   // TODO_STUDEN

  //   return curr;
  // }

  /// Resets internal state for an iterative inorder traversal.
  ///
  /// See `next` for usage details.
  ///
  /// O(H), where H is the maximum height of the tree.
  void begin() {
    // TODO_STUDENT
    if (sz == 0) {
      curr = nullptr;
      return;
    }
    curr = root;
    while (curr->left != nullptr) {
      curr = curr->left;
    }
  }

  /// Uses the internal state to return the next in-order value and priority
  /// by reference, and advances the internal state. Returns true if the
  /// reference parameters were set, and false otherwise.
  ///
  /// Example usage:
  ///
  /// ```c++
  /// pq.begin();
  /// T value;
  /// int priority;
  /// while (pq.next(value, priority)) {
  ///   cout << priority << " value: " << value << endl;
  /// }
  /// ```
  ///
  /// Runs in worst-case O(H + M) or O(H), depending on implementation, where
  /// H is the height of the tree, and M is the number of duplicate
  /// priorities.
  bool next(T& value, int& priority) {
    // TODO_STUDENT
    if (curr == nullptr) {
      return false;
    }

    value = curr->value;
    priority = curr->priority;

    if (temp == nullptr) {
      temp = curr;
    }

    if (curr->link != nullptr) {
      curr->link->left = curr->left;
      curr->link->right = curr->right;
      curr->link->parent = curr->parent;

      curr = curr->link;
      return true;
    }

    curr = temp;
    temp = nullptr;

    if (curr->right != nullptr) {
      curr = curr->right;
      while (curr->left != nullptr) {
        curr = curr->left;
      }
      // return true;
    } else {
      while (curr->parent != nullptr && curr->parent->right == curr) {
        curr = curr->parent;
      }

      curr = curr->parent;
    }
    return true;
  }
};
