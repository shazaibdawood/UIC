#include <iostream>

#include "prqueue.h"

using namespace std;

int main() {
  prqueue<int> pq;
  int value, priority;
  // Optional experimentation space
  pq.enqueue(7, 1);
  pq.enqueue(8, 1);
  pq.enqueue(15, 2);
  pq.enqueue(16, 2);
  pq.enqueue(6, 2);
  pq.enqueue(9, 2);
  pq.enqueue(17, 3);
  pq.enqueue(2, 3);
  pq.enqueue(1, 3);
  pq.enqueue(5, 0);
  pq.enqueue(3, 0);

  cout << pq.as_string() << endl;
  pq.begin();

  cout << pq.getRoot()->link->value << endl;

  if (pq.getRoot()->link->right == nullptr) {
    cout << "null" << endl;
  }
  if (pq.getRoot()->link->left == nullptr) {
    cout << "null" << endl;
  }

  // cout << pq.next(value, priority) << "\t" << value << "\t" << priority <<
  // endl; cout << pq.next(value, priority) << "\t" << value << "\t" << priority
  // << endl; cout << pq.next(value, priority) << "\t" << value << "\t" <<
  // priority << endl; cout << pq.next(value, priority) << "\t" << value << "\t"
  // << priority << endl; cout << pq.next(value, priority) << "\t" << value <<
  // "\t" << priority << endl; cout << pq.next(value, priority) << "\t" << value
  // << "\t" << priority << endl; cout << pq.next(value, priority) << "\t" <<
  // value << "\t" << priority << endl; cout << pq.next(value, priority) << "\t"
  // << value << "\t" << priority << endl; cout << pq.next(value, priority) <<
  // "\t" << value << "\t" << priority << endl; cout << pq.next(value, priority)
  // << "\t" << value << "\t" << priority << endl;
}
