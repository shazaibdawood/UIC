#include "canvaslist.h"

#include <iostream>

using namespace std;

/**
 * Default constructor. Creates an empty `CanvasList`.
 */
CanvasList::CanvasList() {
  list_size = 0;
  list_front = nullptr;
}
/**
 * Copy constructor. Creates a deep copy of the given `CanvasList`, where
 * each `Shape` is copied as well.
 *
 * Must run in O(N) time.
 */
CanvasList::CanvasList(const CanvasList& copyList) {
  if (copyList.list_front == nullptr) {
    list_size = 0;
    list_front = nullptr;
    return;
  }

  list_front = new ShapeNode();
  list_front->value = copyList.list_front->value->copy();
  list_size = copyList.list_size;

  ShapeNode* temp = copyList.list_front->next;
  ShapeNode* modifiedList = list_front;

  while (temp != nullptr) {
    modifiedList->next = new ShapeNode();
    modifiedList = modifiedList->next;
    modifiedList->value = temp->value->copy();

    temp = temp->next;
  }

  modifiedList->next = nullptr;
}

/**
 * Assignment operator. Sets the current `CanvasList` to a deep copy of the
 * given `CanvasList`.
 *
 * Must run in O(N) time.
 */
CanvasList& CanvasList::operator=(const CanvasList& copyList) {
  if (this == &copyList) {
    return *this;
  }

  clear();

  if (copyList.list_front == nullptr) {
    list_size = 0;
    list_front = nullptr;
    return *this;
  }

  list_front = new ShapeNode();
  list_front->value = copyList.list_front->value->copy();
  list_size = copyList.list_size;

  ShapeNode* temp = copyList.list_front->next;
  ShapeNode* modifiedList = list_front;

  while (temp != nullptr) {
    modifiedList->next = new ShapeNode();
    modifiedList = modifiedList->next;
    modifiedList->value = temp->value->copy();

    temp = temp->next;
  }

  modifiedList->next = nullptr;
  return *this;
}

/**
 * Destructor. Clears all allocated memory.
 */
CanvasList::~CanvasList() {
  clear();
}

/**
 * Empties the `CanvasList`, releasing all allocated memory (both
 * `ShapeNode` and `Shape`), and resetting member variables
 * appropriately.
 */
void CanvasList::clear() {
  while (!empty()) {
    delete pop_front();
  }
}

/**
 * Inserts the given `Shape*` as a new element in the `CanvasList` after
 * the given index. If the index is invalid, does nothing.
 *
 * Takes ownership of the given `Shape*`. If the index is invalid, the
 * caller retains ownership and must delete it.
 */
void CanvasList::insert_after(int index, Shape* shape) {
  if (index < 0 || index >= list_size) {
    return;
  } else {
    ShapeNode* temp = list_front;

    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }

    ShapeNode* newNode = new ShapeNode();
    newNode->value = shape;
    newNode->next = temp->next;
    temp->next = newNode;
    list_size++;
  }
}

/**
 * Adds the given `Shape*` to the front of the `CanvasList`.
 *
 * Takes ownership of the given `Shape*`.
 */
void CanvasList::push_front(Shape* shape) {
  ShapeNode* newNode = new ShapeNode();
  newNode->value = shape;
  newNode->next = list_front;
  list_front = newNode;
  list_size++;
}

/**
 * Adds the given `Shape*` to the back of the `CanvasList`.
 *
 * Takes ownership of the given `Shape*`.
 */
void CanvasList::push_back(Shape* shape) {
  ShapeNode* newNode = new ShapeNode();
  newNode->value = shape;
  newNode->next = nullptr;

  if (list_front == nullptr) {
    list_front = newNode;
  } else {
    ShapeNode* temp = list_front;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
  list_size++;
}

/**
 * Remove and destroys the element at the specified index in this list.
 *
 * If the index is invalid, does nothing.
 */
void CanvasList::remove_at(int index) {
  if (index < 0 || index >= list_size) {
    return;
  } else if (index == 0) {
    delete pop_front();
  } else {
    ShapeNode* temp = list_front;
    for (int i = 0; i < index - 1; i++) {
      temp = temp->next;
    }

    ShapeNode* deleteThis = temp->next;
    temp->next = deleteThis->next;
    delete deleteThis->value;
    delete deleteThis;
    list_size--;
  }
}

/**
 * Remove and destroys every other element (alternating) from the
 * `CanvasList`, starting at index 1.
 *
 * For example, if a list was `[0, 1, 2, 3, 4]`, removing every other element
 * would change the list to `[0, 2, 4]`. The removed elements are destroyed.
 */
void CanvasList::remove_every_other() {
  if (list_size < 2) {
    return;
  } else {
    ShapeNode* next = list_front;
    ShapeNode* temp = nullptr;

    while (next != nullptr && next->next != nullptr) {
      temp = next;
      next = next->next;
      temp->next = next->next;

      delete next->value;
      delete next;

      list_size--;
      next = temp->next;
    }
  }
}

/**
 * Removes the element at the front of the `CanvasList`.
 *
 * The `CanvasList` gives up ownership of the returned `Shape*`, and does
 * not free it. If the `CanvasList` is empty, returns `nullptr`.
 */
Shape* CanvasList::pop_front() {
  if (empty()) {
    return nullptr;
  } else {
    Shape* shape = list_front->value;
    ShapeNode* oldFront = list_front;
    list_front = list_front->next;
    delete oldFront;

    list_size--;
    return shape;
  }
}

/**
 * Removes the element at the back of the `CanvasList`.
 *
 * The `CanvasList` gives up ownership of the returned `Shape*`, and the
 * caller must free it. If the `CanvasList` is empty, returns `nullptr`.
 */
Shape* CanvasList::pop_back() {
  if (empty()) {
    return nullptr;
  } else if (list_size == 1) {
    return pop_front();
  } else {
    ShapeNode* temp = list_front;
    while (temp->next->next != nullptr) {
      temp = temp->next;
    }

    Shape* shape = temp->next->value;
    delete temp->next;
    temp->next = nullptr;
    list_size--;

    return shape;
  }
}

/**
 * Returns a pointer to the node at the front of the `CanvasList`.
 *
 * The caller must not delete the returned pointer (the `CanvasList` keeps
 * ownership)
 */
ShapeNode* CanvasList::front() const {
  return list_front;
}

/**
 * Returns whether the `CanvasList` is empty (i.e. whether its
 * size is 0).
 */
bool CanvasList::empty() const {
  if (list_size == 0) {
    return true;
  } else {
    return false;
  }
}

/**
 * Returns the number of elements in the `CanvasList`.
 */
int CanvasList::size() const {
  return list_size;
}

/**
 * Searches the `CanvasList` for the first `Shape` with the given `x`, `y`
 * coordinate values, and returns its index. If no matching `Shape` is
 * found, returns -1.
 */
int CanvasList::find(int x, int y) const {
  int index = 0;
  ShapeNode* temp = list_front;

  while (temp != nullptr) {
    if (temp->value->getX() == x && temp->value->getY() == y) {
      return index;
    }

    temp = temp->next;
    index++;
  }

  return -1;
}

/**
 * Returns the `Shape*` at the given index in the `CanvasList`.
 * The `CanvasList` retains ownership of the `Shape*`; the caller must
 * not delete it.
 *
 * If the index is invalid, returns `nullptr`.
 */
Shape* CanvasList::shape_at(int index) const {
  if (index < 0 || index >= list_size) {
    return nullptr;
  } else {
    ShapeNode* temp = list_front;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }

    return temp->value;
  }
}

/**
 * For each `Shape` in the `CanvasList`, outputs its `as_string`, with one
 * `Shape` on each line.
 */
void CanvasList::draw() const {
  ShapeNode* temp = list_front;
  while (temp != nullptr) {
    cout << temp->value->as_string() << endl;
    temp = temp->next;
  }
}

/**
 * For each node in the `CanvasList`, prints the node's address, and the
 * node's shape's addresss. Each node is on one line.
 *
 * Example output:
 *
 * ```text
 * Node Address: 0x562ac60e82a0	Shape Address: 0x562ac60e8280
 * Node Address: 0x562ac60e81d0	Shape Address: 0x562ac60e81b0
 * Node Address: 0x562ac60e8260	Shape Address: 0x562ac60e8240
 * Node Address: 0x562ac60e8150	Shape Address: 0x562ac60e8130
 * Node Address: 0x562ac60e80e0	Shape Address: 0x562ac60e80c0
 * Node Address: 0x562ac60e8190	Shape Address: 0x562ac60e8170
 * ```
 *
 * The character between the node's address and "Shape" on each line is a
 * tab character, '\t'.
 */
void CanvasList::print_addresses() const {
  ShapeNode* temp = list_front;
  while (temp != nullptr) {
    cout << "Node Address: " << temp << "\tShape Address: " << temp->value
         << endl;
    temp = temp->next;
  }
}
