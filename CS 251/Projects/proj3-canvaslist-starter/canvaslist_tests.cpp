#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "canvaslist.h"
#include "include/shape.h"

using namespace std;
using namespace testing;

TEST(CanvasListCore, Constructor) {
  CanvasList list;
  EXPECT_THAT(list.size(), Eq(0));
  EXPECT_THAT(list.empty(), Eq(true));
  EXPECT_THAT(list.front(), IsNull());
}

TEST(CanvasListCore, PushFront) {
  CanvasList list;
  Shape* shape = new Shape();
  list.push_front(shape);
  EXPECT_THAT(list.empty(), Eq(false));
  EXPECT_THAT(list.size(), Eq(1));
  EXPECT_THAT(list.front(), NotNull());
}

TEST(CanvasListCore, Clear) {
  CanvasList list;
  Shape* shape = new Shape();
  list.push_front(shape);
  list.clear();
  EXPECT_THAT(list.size(), Eq(0));
  EXPECT_THAT(list.front(), IsNull());
}

TEST(CanvasListCore, DestructorTest) {
  CanvasList* list = new CanvasList();
  Shape* shape = new Shape();
  list->push_front(shape);
  delete list;
  EXPECT_THAT(true, Eq(true));  // Destructor tested in ASan
}

TEST(CanvasListIterating, PushBack) {
  CanvasList list;
  Shape* rect = new Rect(9, 4, 6, 7);
  list.push_back(rect);
  EXPECT_THAT(list.size(), Eq(1));
  EXPECT_THAT(list.shape_at(0), Eq(rect));
}

TEST(CanvasListIterating, ShapeAt) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  list.push_back(rect1);
  list.push_back(rect2);
  EXPECT_THAT(list.shape_at(0), Eq(rect1));
  EXPECT_THAT(list.shape_at(1), Eq(rect2));
  EXPECT_THAT(list.shape_at(2), IsNull());
}

TEST(CanvasListIterating, FindShapeByCoordinates) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  list.push_back(rect1);
  list.push_back(rect2);
  EXPECT_THAT(list.find(9, 4), Eq(0));
  EXPECT_THAT(list.find(5, 2), Eq(1));
  EXPECT_THAT(list.find(100, 100), Eq(-1));
}

TEST(CanvasListIterating, CopyUsesShapeCopy) {
  Shape* rect = new Rect(9, 4, 6, 7);
  CanvasList list;
  list.push_back(rect);

  CanvasList copy(list);
  EXPECT_THAT(copy.shape_at(0)->as_string(), Eq(rect->as_string()));
}

TEST(CanvasListIterating, CheckDeepCopy) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  list.push_back(rect1);

  CanvasList copy(list);
  rect1->setX(100);

  EXPECT_THAT(copy.shape_at(0)->getX(), Eq(9));
}

TEST(CanvasListIterating, CopyNotEmpty) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  list.push_back(rect1);

  CanvasList copy(list);
  EXPECT_THAT(copy.size(), Eq(1));
}

TEST(CanvasListIterating, ShapeAtWrongIndex) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  list.push_back(rect1);
  list.push_back(rect2);

  EXPECT_THAT(list.shape_at(0), Eq(rect1));
  EXPECT_THAT(list.shape_at(1), Eq(rect2));
  EXPECT_THAT(list.shape_at(2), IsNull());
}

TEST(CanvasListIterating, FindChecksLastNode) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  list.push_back(rect1);
  list.push_back(rect2);

  EXPECT_THAT(list.find(5, 2), Eq(1));
}

TEST(CanvasListIterating, FindReturnsCorrectIndex) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(9, 4, 3, 4);
  list.push_back(rect1);
  list.push_back(rect2);

  EXPECT_THAT(list.find(9, 4), Eq(0));
}

TEST(CanvasListModifying, PopFront) {
  CanvasList list;
  Shape* rect = new Rect(9, 4, 6, 7);
  list.push_back(rect);
  Shape* popped = list.pop_front();
  EXPECT_THAT(list.size(), Eq(0));
  EXPECT_THAT(popped, Eq(rect));
  delete popped;
}

TEST(CanvasListModifying, AssignSelf) {
  CanvasList list;
  Shape* shape = new Shape();
  list.push_back(shape);
  CanvasList& listRef = list;
  list = listRef;
  EXPECT_THAT(list.size(), Eq(1));
  EXPECT_THAT(list.shape_at(0), Eq(shape));
}

TEST(CanvasListModifying, AssignToEmpty) {
  CanvasList list1;
  Shape* shape = new Shape();
  list1.push_back(shape);

  CanvasList list2;
  list1 = list2;

  EXPECT_THAT(list1.size(), Eq(0));
  EXPECT_THAT(list1.front(), IsNull());
}

TEST(CanvasListModifying, AssignUsesShapeCopy) {
  CanvasList list1;
  Shape* rect = new Rect(5, 2, 3, 4);
  list1.push_back(rect);

  CanvasList list2;
  list2 = list1;

  EXPECT_THAT(list2.shape_at(0)->as_string(), Eq(rect->as_string()));
  rect->setX(100);
  EXPECT_THAT(list2.shape_at(0)->getX(), Eq(5));
}

TEST(CanvasListModifying, AssignClearCheck) {
  CanvasList list1;
  Shape* shape = new Shape();
  list1.push_back(shape);

  CanvasList list2;
  list1 = list2;

  EXPECT_THAT(list1.size(), Eq(0));
  EXPECT_THAT(list1.front(), IsNull());
}

TEST(CanvasListModifying, PopFrontSameSize) {
  CanvasList list;
  Shape* shape = new Shape();
  list.push_back(shape);

  Shape* popped = list.pop_front();
  EXPECT_THAT(list.size(), Eq(0));

  delete popped;
}

TEST(CanvasListModifying, PopFrontEmpty) {
  CanvasList list;
  Shape* popped = list.pop_front();

  EXPECT_THAT(popped, IsNull());
  EXPECT_THAT(list.size(), Eq(0));
}

TEST(CanvasListModifying, PopBackSameSize) {
  CanvasList list;
  Shape* rect1 = new Rect(5, 2, 3, 4);
  Shape* rect2 = new Rect(2, 5, 4, 3);
  list.push_back(rect1);
  list.push_back(rect2);

  Shape* popped = list.pop_back();
  EXPECT_THAT(list.size(), Eq(1));

  delete popped;
}

TEST(CanvasListModifying, PopBackEmpty) {
  CanvasList list;
  Shape* popped = list.pop_back();

  EXPECT_THAT(popped, IsNull());
  EXPECT_THAT(list.size(), Eq(0));
}

TEST(CanvasListModifying, RemoveAtCutoff) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  Shape* rect3 = new Rect(7, 3, 5, 6);
  list.push_back(rect1);
  list.push_back(rect2);
  list.push_back(rect3);

  list.remove_at(1);

  EXPECT_THAT(list.size(), Eq(2));
  EXPECT_THAT(list.shape_at(1), Eq(rect3));
}

TEST(CanvasListModifying, RemoveAtSameSize) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  list.push_back(rect1);

  list.remove_at(0);

  EXPECT_THAT(list.size(), Eq(0));
}

TEST(CanvasListModifying, RemoveAtEmpty) {
  CanvasList list;
  list.remove_at(0);

  EXPECT_THAT(list.size(), Eq(0));
  EXPECT_THAT(list.front(), IsNull());
}

TEST(CanvasListModifying, RemoveAtOutOfBounds) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  list.push_back(rect1);

  list.remove_at(5);

  EXPECT_THAT(list.size(), Eq(1));
  EXPECT_THAT(list.shape_at(0), Eq(rect1));
}

TEST(CanvasListModifying, PopBack) {
  CanvasList list;
  Shape* rect = new Rect(9, 4, 6, 7);
  list.push_back(rect);
  Shape* popped = list.pop_back();
  EXPECT_THAT(list.size(), Eq(0));
  EXPECT_THAT(popped, Eq(rect));
  delete popped;
}

TEST(CanvasListModifying, RemoveAt) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  list.push_back(rect1);
  list.push_back(rect2);
  list.remove_at(0);
  EXPECT_THAT(list.size(), Eq(1));
  EXPECT_THAT(list.shape_at(0), Eq(rect2));
}

TEST(CanvasListModifying, RemoveEveryOther) {
  CanvasList list1;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  Shape* rect3 = new Rect(7, 3, 5, 6);
  Shape* rect4 = new Rect(3, 3, 5, 6);
  list1.push_back(rect1);
  list1.push_back(rect2);
  list1.push_back(rect3);
  list1.push_back(rect4);
  list1.remove_every_other();
  EXPECT_THAT(list1.size(), Eq(2));
  EXPECT_THAT(list1.shape_at(0), Eq(rect1));
  EXPECT_THAT(list1.shape_at(1), Eq(rect3));
}

TEST(CanvasListExtras, RemoveEveryOtherOneElement) {
  CanvasList list2;
  Shape* rect = new Rect(9, 4, 6, 7);
  list2.push_back(rect);
  list2.remove_every_other();
  EXPECT_THAT(list2.size(), Eq(1));
  EXPECT_THAT(list2.shape_at(0), Eq(rect));
}

TEST(CanvasListModifying, RemoveEveryOtherEmptyList) {
  CanvasList list3;
  list3.remove_every_other();
  EXPECT_THAT(list3.size(), Eq(0));
  EXPECT_THAT(list3.shape_at(0), IsNull());
}

TEST(CanvasListExtras, InsertAfter) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  list.push_back(rect1);
  list.insert_after(0, rect2);
  EXPECT_THAT(list.size(), Eq(2));
  EXPECT_THAT(list.shape_at(1), Eq(rect2));
}

TEST(CanvasListExtras, CopyConstructorAndShapeIntegrity) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  list.push_front(rect1);
  list.push_front(rect2);

  CanvasList copy(list);
  EXPECT_THAT(copy.size(), Eq(2));
  EXPECT_THAT(copy.shape_at(0)->as_string(), Eq(rect2->as_string()));
  EXPECT_THAT(copy.shape_at(1)->as_string(), Eq(rect1->as_string()));

  rect1->setX(100);
  rect2->setY(200);
  EXPECT_THAT(copy.shape_at(0)->getX(), Eq(5));
  EXPECT_THAT(copy.shape_at(1)->getY(), Eq(4));
}

TEST(CanvasListExtras, InsertFindAndPop) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  list.push_back(rect1);
  list.insert_after(0, rect2);

  EXPECT_THAT(list.size(), Eq(2));
  EXPECT_THAT(list.find(9, 4), Eq(0));
  EXPECT_THAT(list.find(5, 2), Eq(1));

  Shape* popped = list.pop_front();
  EXPECT_THAT(list.size(), Eq(1));
  EXPECT_THAT(popped, Eq(rect1));
  delete popped;
}

TEST(CanvasListExtras, PopAndRemoveAt) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  Shape* rect3 = new Rect(7, 3, 5, 6);

  list.push_back(rect1);
  list.push_back(rect2);
  list.push_back(rect3);

  Shape* popped = list.pop_back();
  EXPECT_THAT(list.size(), Eq(2));
  EXPECT_THAT(popped, Eq(rect3));
  delete popped;

  list.remove_at(0);
  EXPECT_THAT(list.size(), Eq(1));
  EXPECT_THAT(list.shape_at(0), Eq(rect2));
}

TEST(CanvasListExtras, PushPopRemoveEveryOther) {
  CanvasList list;
  Shape* rect1 = new Rect(9, 4, 6, 7);
  Shape* rect2 = new Rect(5, 2, 3, 4);
  Shape* rect3 = new Rect(7, 3, 5, 6);
  list.push_back(rect1);
  list.push_back(rect2);
  list.push_back(rect3);

  Shape* popped = list.pop_front();
  EXPECT_THAT(list.size(), Eq(2));
  delete popped;

  list.remove_every_other();
  EXPECT_THAT(list.size(), Eq(1));
  EXPECT_THAT(list.shape_at(0), Eq(rect2));
}