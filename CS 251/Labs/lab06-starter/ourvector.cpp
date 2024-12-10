#include <iostream>

using namespace std;

class ourvector {
 private:
  int* data;
  int capacity;
  int numElements;

  void resize(int newCapacity) {
    if (newCapacity > capacity) {
      int* newData = new int[newCapacity];

      for (int i = 0; i < numElements; ++i) {
        newData[i] = data[i];
      }

      delete[] data;
      data = newData;
      capacity = newCapacity;
    }
  }

 public:
  ourvector() {
    capacity = 2;
    numElements = 0;
    data = new int[capacity];
  }

  ourvector(const ourvector& origObject) {
    data = new int[origObject.capacity];
    capacity = origObject.capacity;
    numElements = origObject.numElements;

    for (int i = 0; i < numElements; ++i) {
      data[i] = origObject.data[i];
    }
  }

  void push_back(int value) {
    if (numElements == capacity) {
      resize(capacity + 1);
    }

    data[numElements] = value;
    numElements++;
  }

  int size() {
    return numElements;
  }

  int at(int index) {
    if (index < numElements) {
      return data[index];
    }
    return 0;
  }

  ~ourvector() {
    delete[] data;
  }
};

int sumvec(ourvector v) {
  int sum = 0;
  for (int j = 0; j < v.size(); j++) {
    sum += v.at(j);
  }
  return sum;
}

int main() {
  ourvector vec;
  int i = 0;
  while (i <= 10) {
    vec.push_back(i++);
  }
  cout << "summation = " << sumvec(vec) << endl;
}