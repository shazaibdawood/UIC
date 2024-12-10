#include "heap.h"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void MinHeap::insert(TrainStation val) {
  // TODO BY STUDENT.
  data.push_back(val);
  _siftup(data.size() - 1);
}

TrainStation MinHeap::remove() {
  // TODO BY STUDENT
  TrainStation min = data.at(0);
  data.at(0) = data.back();
  data.pop_back();
  if(!data.empty()){
    _siftdown(0);
  }
  return min;
}

TrainStation MinHeap::peek() {
  // TODO BY STUDENT
  return data.at(0);
}

void MinHeap::_siftup(int index) {
  // TODO BY STUDENT.

  if(index == 0){
    return;
  }

  int parentIndex = _parent(index);

  if(data.at(index).ridership < data.at(parentIndex).ridership){
    TrainStation temp = data.at(parentIndex);
    data.at(parentIndex) = data.at(index);
    data.at(index) = temp;
    _siftup(parentIndex);
  }
}

void MinHeap::_siftdown(int index) {
  // TODO BY STUDENT.

  

  // if(right < data.size() && data.at(index).ridership > data.at(right).ridership){
  //   TrainStation temp;

  //   if (left < data.size() && data.at(index).ridership > data.at(left).ridership)
  //   {
  //     temp = data.at(left);
  //     data.at(left) = data.at(index);
  //     data.at(index) = temp;
  //     _siftdown(left);
  //   }
  //   else{
  //     temp = data.at(right);
  //     data.at(right) = data.at(index);
  //     data.at(index) = temp;
  //     _siftdown(right);
  //   }
  // }
  int temp = index;
  do{
    int left = _left(index);
    int right = _right(index);
    TrainStation swap;
    if(left < data.size() && data.at(left).ridership < data.at(temp).ridership){
      temp = left;
    }
    if(right < data.size() && data.at(right).ridership < data.at(temp).ridership){
      temp = right;
    }
    
    if(temp != index){
      swap = data.at(temp);
      data.at(temp) = data.at(index);
      data.at(index) = swap;
      index = temp;
    }
    else{
      break;
    }
  }  while(index == temp);
}