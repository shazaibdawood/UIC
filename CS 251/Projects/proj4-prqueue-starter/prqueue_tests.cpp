// Why the angle brackets? Grader reasons.
// Don't change this or you will be sad :(
#include <prqueue.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace std;

TEST(PRQueueCore, testDefaultConstructor) {
  prqueue<int> pq;
  EXPECT_EQ(pq.getRoot(), nullptr);
  EXPECT_EQ(pq.size(), 0);
}

TEST(PRQueueCore, testSize) {
  prqueue<int> pq;
  EXPECT_EQ(pq.size(), 0);
}

TEST(PRQueueCore, testGetRoot) {
  prqueue<int> pq;
  EXPECT_EQ(pq.getRoot(), nullptr);

  pq.clear();
}

TEST(PRQueueCore, testEnqueue) {
  prqueue<int> pq;

  // Empty
  EXPECT_EQ(pq.getRoot(), nullptr);
  EXPECT_EQ(pq.size(), 0);

  pq.enqueue(10, 10);
  EXPECT_NE(pq.getRoot(), nullptr);
  EXPECT_EQ(pq.getRoot()->value, 10);
  EXPECT_EQ(pq.getRoot()->priority, 10);
  EXPECT_EQ(pq.getRoot()->parent, nullptr);
  EXPECT_EQ(pq.getRoot()->left, nullptr);
  EXPECT_EQ(pq.getRoot()->right, nullptr);
  EXPECT_EQ(pq.getRoot()->link, nullptr);
  EXPECT_EQ(pq.size(), 1);

  // Right Child
  pq.enqueue(20, 20);
  EXPECT_EQ(pq.getRoot()->left, nullptr);
  EXPECT_NE(pq.getRoot()->right, nullptr);

  EXPECT_EQ(pq.getRoot()->right->value, 20);
  EXPECT_EQ(pq.getRoot()->right->priority, 20);
  EXPECT_EQ(pq.getRoot()->right->left, nullptr);
  EXPECT_EQ(pq.getRoot()->right->right, nullptr);
  EXPECT_EQ(pq.getRoot()->right->link, nullptr);
  EXPECT_EQ(pq.getRoot()->right->parent, pq.getRoot());
  EXPECT_EQ(pq.size(), 2);

  // Left Child
  pq.enqueue(5, 5);
  EXPECT_NE(pq.getRoot()->left, nullptr);

  EXPECT_EQ(pq.getRoot()->left->value, 5);
  EXPECT_EQ(pq.getRoot()->left->priority, 5);
  EXPECT_EQ(pq.getRoot()->left->left, nullptr);
  EXPECT_EQ(pq.getRoot()->left->right, nullptr);
  EXPECT_EQ(pq.getRoot()->left->link, nullptr);
  EXPECT_EQ(pq.getRoot()->left->parent, pq.getRoot());
  EXPECT_EQ(pq.size(), 3);

  pq.clear();
}

TEST(PRQueueCore, testClear) {
  prqueue<int> pq;
  pq.enqueue(10, 10);
  pq.enqueue(5, 5);
  pq.enqueue(20, 20);

  EXPECT_EQ(pq.size(), 3);

  pq.clear();
  EXPECT_EQ(pq.size(), 0);
}

TEST(PRQueueCore, testDestructor) {
  prqueue<int> pq;
  pq.enqueue(10, 10);
  pq.enqueue(5, 5);
  pq.enqueue(20, 20);

  EXPECT_EQ(pq.size(), 3);

  pq.clear();
  EXPECT_EQ(pq.size(), 0);
}

TEST(PRQueueUsing, testPeak) {
  prqueue<int> pq;

  // Empty
  EXPECT_EQ(pq.peek(), {});

  // Root only
  pq.enqueue(10, 10);
  EXPECT_EQ(pq.peek(), 10);

  // Right Child
  pq.enqueue(20, 20);
  EXPECT_EQ(pq.peek(), 10);

  // Left Child
  pq.enqueue(5, 5);
  EXPECT_EQ(pq.peek(), 5);

  pq.clear();
}

TEST(PRQueueUsing, testDequeue) {
  prqueue<int> pq;
  pq.enqueue(10, 10);
  pq.enqueue(5, 5);
  pq.enqueue(20, 20);

  EXPECT_EQ(pq.size(), 3);
  string asString = "5 value: 5\n10 value: 10\n20 value: 20\n";
  EXPECT_EQ(pq.as_string(), asString);

  asString = "10 value: 10\n20 value: 20\n";
  EXPECT_EQ(pq.peek(), 5);
  EXPECT_EQ(pq.dequeue(), 5);
  EXPECT_EQ(pq.size(), 2);
  EXPECT_EQ(pq.getRoot()->left, nullptr);
  EXPECT_EQ(pq.getRoot()->right->value, 20);
  EXPECT_EQ(pq.getRoot()->value, 10);
  EXPECT_EQ(pq.as_string(), asString);

  asString = "20 value: 20\n";
  EXPECT_EQ(pq.peek(), 10);
  EXPECT_EQ(pq.dequeue(), 10);
  EXPECT_EQ(pq.size(), 1);
  EXPECT_EQ(pq.getRoot()->left, nullptr);
  EXPECT_EQ(pq.getRoot()->right, nullptr);
  EXPECT_EQ(pq.getRoot()->value, 20);
  EXPECT_EQ(pq.as_string(), asString);

  asString = "";
  EXPECT_EQ(pq.peek(), 20);
  EXPECT_EQ(pq.dequeue(), 20);
  EXPECT_EQ(pq.size(), 0);
  EXPECT_EQ(pq.getRoot(), nullptr);
  EXPECT_EQ(pq.as_string(), asString);

  EXPECT_EQ(pq.peek(), {});
  EXPECT_EQ(pq.dequeue(), {});
  pq.clear();

  pq.enqueue(5, 5);
  pq.enqueue(10, 10);
  pq.enqueue(3, 3);
  pq.enqueue(2, 2);
  pq.enqueue(7, 7);
  pq.enqueue(12, 12);

  string expectedBefore =
      "2 value: 2\n3 value: 3\n5 value: 5\n7 value: 7\n10 value: 10\n12 value: "
      "12\n";
  EXPECT_EQ(pq.as_string(), expectedBefore);
  pq.dequeue();
  string expectedAfter =
      "3 value: 3\n5 value: 5\n7 value: 7\n10 value: 10\n12 value: "
      "12\n";
  EXPECT_EQ(pq.as_string(), expectedAfter);
  pq.clear();

  pq.enqueue(1, 30);
  pq.enqueue(2, 20);
  pq.enqueue(3, 21);
  pq.enqueue(4, 15);
  pq.enqueue(5, 17);
  pq.enqueue(6, 16);
  expectedBefore =
      "15 value: 4\n16 value: 6\n17 value: 5\n20 value: 2\n21 value: 3\n30 "
      "value: 1\n";
  EXPECT_EQ(pq.as_string(), expectedBefore);
  pq.dequeue();
  expectedAfter =
      "16 value: 6\n17 value: 5\n20 value: 2\n21 value: 3\n30 value: 1\n";
  EXPECT_EQ(pq.as_string(), expectedAfter);
  pq.clear();
}

TEST(PRQueueUsing, testAs_String) {
  prqueue<string> names;
  names.enqueue("Gwen", 3);
  names.enqueue("Jen", 2);
  names.enqueue("Ben", 1);
  names.enqueue("Sven", 2);

  string asString =
      "1 value: Ben\n2 value: Jen\n2 value: Sven\n3 value: Gwen\n";

  EXPECT_EQ(names.as_string(), asString);
  names.clear();

  names.enqueue("Dolores", 5);
  names.enqueue("Bernard", 4);
  names.enqueue("Arnold", 8);
  names.enqueue("Ford", 2);
  names.enqueue("Jasmine", 6);
  names.enqueue("Carlos", 11);
  names.enqueue("William", 8);
  names.enqueue("Teddy", 8);

  asString =
      "2 value: Ford\n4 value: Bernard\n5 value: Dolores\n6 value: Jasmine\n8 "
      "value: Arnold\n8 value: William\n8 value: Teddy\n11 value: Carlos\n";
  EXPECT_EQ(names.as_string(), asString);
  names.clear();
}

TEST(PRQueueDuplicates, testEnqueue) {
  prqueue<int> pq;

  pq.enqueue(1, 10);
  pq.enqueue(2, 5);
  pq.enqueue(3, 20);
  pq.enqueue(4, 10);
  pq.enqueue(5, 5);
  pq.enqueue(6, 20);
  pq.enqueue(7, 10);
  pq.enqueue(8, 5);
  pq.enqueue(9, 20);

  EXPECT_EQ(pq.getRoot()->value, 1);
  EXPECT_EQ(pq.getRoot()->link->value, 4);
  EXPECT_EQ(pq.getRoot()->link->link->value, 7);
  EXPECT_EQ(pq.getRoot()->link->link->link, nullptr);

  EXPECT_EQ(pq.getRoot()->left->value, 2);
  EXPECT_EQ(pq.getRoot()->left->link->value, 5);
  EXPECT_EQ(pq.getRoot()->left->link->link->value, 8);
  EXPECT_EQ(pq.getRoot()->left->link->link->link, nullptr);

  EXPECT_EQ(pq.getRoot()->right->value, 3);
  EXPECT_EQ(pq.getRoot()->right->link->value, 6);
  EXPECT_EQ(pq.getRoot()->right->link->link->value, 9);
  EXPECT_EQ(pq.getRoot()->right->link->link->link, nullptr);

  pq.clear();
}

TEST(PRQueueDuplicates, testAs_String) {
  prqueue<string> names;
  names.enqueue("Gwen", 3);
  names.enqueue("Jen", 2);
  names.enqueue("Ben", 1);
  names.enqueue("Sven", 2);

  string asString =
      "1 value: Ben\n2 value: Jen\n2 value: Sven\n3 value: Gwen\n";

  EXPECT_EQ(names.as_string(), asString);
  names.clear();

  names.enqueue("Dolores", 5);
  names.enqueue("Bernard", 4);
  names.enqueue("Arnold", 8);
  names.enqueue("Ford", 2);
  names.enqueue("Jasmine", 6);
  names.enqueue("Carlos", 11);
  names.enqueue("William", 8);
  names.enqueue("Teddy", 8);

  asString =
      "2 value: Ford\n4 value: Bernard\n5 value: Dolores\n6 value: Jasmine\n8 "
      "value: Arnold\n8 value: William\n8 value: Teddy\n11 value: Carlos\n";
  EXPECT_EQ(names.as_string(), asString);
  names.clear();
}

TEST(PRQueueDuplicates, testDequeue) {
  prqueue<int> pq;

  pq.enqueue(1, 10);
  pq.enqueue(2, 5);
  pq.enqueue(3, 20);
  pq.enqueue(4, 10);
  pq.enqueue(5, 5);
  pq.enqueue(6, 20);
  pq.enqueue(7, 10);
  pq.enqueue(8, 5);
  pq.enqueue(9, 20);

  string expectedBefore =
      "5 value: 2\n5 value: 5\n5 value: 8\n10 value: 1\n10 value: 4\n10 value: "
      "7\n20 value: 3\n20 value: 6\n20 value: 9\n";
  string expectedAfter =
      "5 value: 5\n5 value: 8\n10 value: 1\n10 value: 4\n10 value: "
      "7\n20 value: 3\n20 value: 6\n20 value: 9\n";
  EXPECT_EQ(pq.as_string(), expectedBefore);
  EXPECT_EQ(pq.size(), 9);
  pq.dequeue();
  EXPECT_EQ(pq.as_string(), expectedAfter);
  EXPECT_EQ(pq.size(), 8);

  pq.dequeue();
  EXPECT_EQ(pq.size(), 7);
  pq.dequeue();
  EXPECT_EQ(pq.size(), 6);
  pq.dequeue();
  EXPECT_EQ(pq.size(), 5);
  pq.dequeue();
  EXPECT_EQ(pq.size(), 4);
  pq.dequeue();
  EXPECT_EQ(pq.size(), 3);
  pq.dequeue();
  EXPECT_EQ(pq.size(), 2);
  pq.dequeue();
  EXPECT_EQ(pq.size(), 1);
  pq.dequeue();
  EXPECT_EQ(pq.size(), 0);

  pq.clear();
}

TEST(PRQueueCopying, testCopyConstructor) {
  prqueue<int> pq;

  pq.enqueue(1, 10);
  pq.enqueue(2, 5);
  pq.enqueue(3, 20);
  pq.enqueue(4, 10);
  pq.enqueue(5, 5);
  pq.enqueue(6, 20);
  pq.enqueue(7, 10);
  pq.enqueue(8, 5);
  pq.enqueue(9, 20);
  pq.enqueue(7, 1);
  pq.enqueue(8, 1);
  pq.enqueue(15, 2);
  pq.enqueue(16, 2);
  pq.enqueue(6, 2);
  pq.enqueue(9, 2);
  pq.enqueue(17, 3);
  pq.enqueue(2, 3);
  pq.enqueue(1, 3);

  prqueue pCopy(pq);
  EXPECT_EQ(pCopy.size(), pq.size());
  EXPECT_EQ(pCopy.as_string(), pq.as_string());

  pq.clear();
  pCopy.clear();

  pq.enqueue(1, 10);
  pq.enqueue(2, 5);
  pq.enqueue(3, 20);
  pq.enqueue(4, 10);
  pq.enqueue(5, 5);
  pq.enqueue(6, 20);
  pq.enqueue(7, 10);
  pq.enqueue(8, 5);
  pq.enqueue(9, 20);

  prqueue pCopy2(pq);

  EXPECT_EQ(pCopy2.getRoot()->value, 1);
  EXPECT_EQ(pCopy2.getRoot()->link->value, 4);
  EXPECT_EQ(pCopy2.getRoot()->link->link->value, 7);
  EXPECT_EQ(pCopy2.getRoot()->link->link->link, nullptr);

  EXPECT_EQ(pCopy2.getRoot()->left->value, 2);
  EXPECT_EQ(pCopy2.getRoot()->left->link->value, 5);
  EXPECT_EQ(pCopy2.getRoot()->left->link->link->value, 8);
  EXPECT_EQ(pCopy2.getRoot()->left->link->link->link, nullptr);

  EXPECT_EQ(pCopy2.getRoot()->right->value, 3);
  EXPECT_EQ(pCopy2.getRoot()->right->link->value, 6);
  EXPECT_EQ(pCopy2.getRoot()->right->link->link->value, 9);
  EXPECT_EQ(pCopy2.getRoot()->right->link->link->link, nullptr);

  pq.clear();
  pCopy2.clear();
}

TEST(PRQueueCopying, testCopyAssignmentOperator) {
  prqueue<int> pq;
  prqueue<int> pCopy;

  EXPECT_EQ(pCopy.size(), pq.size());
  EXPECT_EQ(pCopy.as_string(), pq.as_string());

  pq.enqueue(1, 10);
  pq.enqueue(2, 5);
  pq.enqueue(3, 20);
  pq.enqueue(4, 10);
  pq.enqueue(5, 5);
  pq.enqueue(6, 20);
  pq.enqueue(7, 10);
  pq.enqueue(8, 5);
  pq.enqueue(9, 20);
  pq.enqueue(7, 1);
  pq.enqueue(8, 1);
  pq.enqueue(15, 2);
  pq.enqueue(16, 2);
  pq.enqueue(6, 2);
  pq.enqueue(9, 2);
  pq.enqueue(17, 3);
  pq.enqueue(2, 3);
  pq.enqueue(1, 3);

  pCopy = pq;

  EXPECT_EQ(pCopy.size(), pq.size());
  EXPECT_EQ(pCopy.as_string(), pq.as_string());

  pq.clear();
  pCopy.clear();

  pq.enqueue(1, 10);
  pq.enqueue(2, 5);
  pq.enqueue(3, 20);
  pq.enqueue(4, 10);
  pq.enqueue(5, 5);
  pq.enqueue(6, 20);
  pq.enqueue(7, 10);
  pq.enqueue(8, 5);
  pq.enqueue(9, 20);

  prqueue<int> pCopy2;
  pCopy2 = pq;

  EXPECT_EQ(pCopy2.getRoot()->value, 1);
  EXPECT_EQ(pCopy2.getRoot()->link->value, 4);
  EXPECT_EQ(pCopy2.getRoot()->link->link->value, 7);
  EXPECT_EQ(pCopy2.getRoot()->link->link->link, nullptr);

  EXPECT_EQ(pCopy2.getRoot()->left->value, 2);
  EXPECT_EQ(pCopy2.getRoot()->left->link->value, 5);
  EXPECT_EQ(pCopy2.getRoot()->left->link->link->value, 8);
  EXPECT_EQ(pCopy2.getRoot()->left->link->link->link, nullptr);

  EXPECT_EQ(pCopy2.getRoot()->right->value, 3);
  EXPECT_EQ(pCopy2.getRoot()->right->link->value, 6);
  EXPECT_EQ(pCopy2.getRoot()->right->link->link->value, 9);
  EXPECT_EQ(pCopy2.getRoot()->right->link->link->link, nullptr);

  pq.clear();
  pCopy2.clear();
}

TEST(PRQueueEquality, testComparisonOperator) {
  prqueue<string> a;
  a.enqueue("2", 2);
  a.enqueue("1", 1);
  a.enqueue("3", 3);

  prqueue<string> b;
  b.enqueue("2", 2);
  b.enqueue("3", 3);
  b.enqueue("1", 1);

  EXPECT_EQ(a == b, true);

  a.clear();

  a.enqueue("1", 1);
  a.enqueue("2", 2);
  a.enqueue("3", 3);

  EXPECT_EQ(a == b, false);

  a.clear();
  b.clear();
}

TEST(PRQueueIterator, testBeginAndNext) {
  prqueue<int> pq;
  int value, priority;

  pq.begin();
  EXPECT_EQ(pq.next(value, priority), false);

  pq.enqueue(1, 10);
  pq.enqueue(2, 5);
  pq.enqueue(3, 20);
  pq.enqueue(4, 10);

  pq.begin();
  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(priority, 5);
  EXPECT_EQ(value, 2);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(priority, 10);
  EXPECT_EQ(value, 1);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(priority, 10);
  EXPECT_EQ(value, 4);

  pq.begin();
  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(priority, 5);
  EXPECT_EQ(value, 2);

  pq.clear();

  prqueue<string> a;
  string svalue;

  a.enqueue("2", 2);
  a.enqueue("1", 1);
  a.enqueue("3", 3);

  a.begin();

  EXPECT_EQ(a.next(svalue, priority), true);
  EXPECT_EQ(priority, 1);
  EXPECT_EQ(svalue, "1");

  EXPECT_EQ(a.next(svalue, priority), true);
  EXPECT_EQ(priority, 2);
  EXPECT_EQ(svalue, "2");

  EXPECT_EQ(a.next(svalue, priority), true);
  EXPECT_EQ(priority, 3);
  EXPECT_EQ(svalue, "3");

  EXPECT_EQ(a.next(svalue, priority), false);

  a.clear();

  pq.enqueue(1, 10);
  pq.enqueue(2, 10);
  pq.enqueue(5, 1);
  pq.enqueue(10, 13);
  pq.enqueue(7, 3);
  pq.enqueue(8, 11);
  pq.enqueue(4, 10);
  pq.enqueue(9, 12);
  pq.enqueue(6, 2);
  pq.enqueue(3, 10);
  pq.enqueue(11, 0);

  pq.begin();
  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 11);
  EXPECT_EQ(priority, 0);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 5);
  EXPECT_EQ(priority, 1);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 6);
  EXPECT_EQ(priority, 2);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 7);
  EXPECT_EQ(priority, 3);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 1);
  EXPECT_EQ(priority, 10);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 2);
  EXPECT_EQ(priority, 10);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 4);
  EXPECT_EQ(priority, 10);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 3);
  EXPECT_EQ(priority, 10);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 8);
  EXPECT_EQ(priority, 11);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 9);
  EXPECT_EQ(priority, 12);

  EXPECT_EQ(pq.next(value, priority), true);
  EXPECT_EQ(value, 10);
  EXPECT_EQ(priority, 13);

  EXPECT_EQ(pq.next(value, priority), false);

  pq.clear();
}
