#include "chaining.h"

#include <iostream>
#include <stdexcept>

using namespace std;

// Fancy syntax to call the other constructor that takes an int argument
ChainingHashMap::ChainingHashMap() : ChainingHashMap(10) {
}

ChainingHashMap::ChainingHashMap(int capacity) {
  this->size = 0;
  this->capacity = capacity;
  this->buckets = new Entry*[capacity];
  for (int i = 0; i < capacity; i++) {
    this->buckets[i] = nullptr;
  }
}

ChainingHashMap::~ChainingHashMap() {
  // TODO_STUDENT


}

void ChainingHashMap::insert(int key, int value) {
  // Resize if we're inserting into an overfull map
  maybe_resize();

  int bucket_idx = get_bucket(key);

  Entry* prev = nullptr;
  Entry* curr = this->buckets[bucket_idx];

  while (curr != nullptr) {
    // If we find the key, set the value
    if (curr->k == key) {
      curr->v = value;
      return;
    }
    // Otherwise, advance down the list
    prev = curr;
    curr = curr->next;
  }

  // Not found, need to create a new entry
  size++;
  Entry* new_entry = new Entry;
  new_entry->k = key;
  new_entry->v = value;
  new_entry->next = nullptr;

  // Inserting into an empty list
  if (prev == nullptr) {
    this->buckets[bucket_idx] = new_entry;
  }
  // Insert at the back of a list with contents
  // Note that we could insert at the front!
  else {
    prev->next = new_entry;
  }
}

int ChainingHashMap::at(int key) {
  int bucket_idx = get_bucket(key);
  Entry* curr = this->buckets[bucket_idx];

  while (curr != nullptr) {
    // If we find the key, set the value
    if (curr->k == key) {
      return curr->v;
    }
    // Otherwise, advance down the list
    curr = curr->next;
  }
  throw runtime_error("key not found in map");
}

int ChainingHashMap::get_bucket(int key) {
  // Implemented to safely handle negative numbers, see guide for details
  return ((key % this->capacity) + this->capacity) % this->capacity;
}

void ChainingHashMap::maybe_resize() {
  if (size < capacity) {
    return;
  }

  int newCapacity = capacity * 2;
  Entry** newBuckets = new Entry*[newCapacity];

  for (int i = 0; i < newCapacity; i++) {
    newBuckets[i] = nullptr;
  }

  for (int i = 0; i < capacity; i++) {
    Entry* curr = buckets[i];
    while (curr != nullptr) {
      Entry* next = curr->next;
      int newBucketIdx = ((curr->k % newCapacity) + newCapacity) % newCapacity;

      curr->next = newBuckets[newBucketIdx];
      newBuckets[newBucketIdx] = curr;

      curr = next;
    }
  }
  delete[] buckets;
  buckets = newBuckets;
  capacity = newCapacity;
}

