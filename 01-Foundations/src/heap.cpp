#include "heap.hpp"
#include <cmath>
#include <iostream>
#include <ostream>
#include <utility>

Heap::Heap(std::vector<int>& A) {
  this->array = A;
  this->array_size = A.size();
  this->heap_size = this->array_size;
  this->build_max_heap();
}

int Heap::left(int i) {
  return ((i << 1) + 1); // returns 2*i + 1
}
int Heap::right(int i) {
  return ((i + 1) << 1); // returns 2*(i + 1)
}
int Heap::parent(int i) {
  return ((i - 1) >> 1); // returns ceiling(i/2) - 1
}

void Heap::max_heapify(int index) {
  // std::cout << "\nrunning max heapify with index: " << index << " left child:
  // " << left(index) << " and right child: " << right(index) << '\n';
  int largest;

  int l = left(index);
  int r = right(index);
  if (l < this->heap_size and array[l] > array[index]) {
    largest = l;
  } else {
    largest = index;
  }
  if (r < this->heap_size and array[r] > array[largest]) {
    largest = r;
  }

  if (largest != index) {
    std::swap(array[index], array[largest]);
    max_heapify(largest);
  }
}

void Heap::build_max_heap() {
  this->heap_size = this->array_size;
  int midway = (this->array_size / 2) - 1;
  for (int i = midway; i >= 0; --i) {
    max_heapify(i);
  }
}

void drawHeapMinimal(Heap &heap) {

  newline;
  std::cout << "drawing heap...";
  newline;
  std::cout << "height: " << getNodeHeight(heap.heap_size - 1);
  newline;
  newline;

  int currentHeight = getNodeHeight(0);

  for (int i = 0; i < heap.heap_size; ++i) {
    if (currentHeight != getNodeHeight(i)) {
      newline;
      currentHeight = getNodeHeight(i);
      std::cout << heap.array[i] << '\t';
    } else {
      std::cout << heap.array[i] << '\t';
    }
  }
  std::cout << "the final height is: " << currentHeight << std::endl;
}

void drawHeapProper(Heap heap) {
  // first we intend to draw a box with the proper dimensions as we want
  std::cout << '\n';
  int height = getNodeHeight(heap.heap_size-1);
  int width = pow(2.0,static_cast<double>(getNodeHeight(heap.heap_size - 1)));
  width = width * 8 + 2;
  std::cout << "width should be: " << width << std::endl;
  height = height * 3 + 3;
  std::cout << "height should be: " << height << std::endl;

  int currentNode = 0;
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      if(i == 0 || j == 0 || i == height - 1  || j == width - 1 ) {
        std::cout << ' ';
      } else {
        if(currentNode < heap.heap_size) {
          if(handleRender(currentNode, width - 2).i_coord == i and handleRender(currentNode, width - 2).j_coord == j) {
            std::cout << heap.array[currentNode];
            currentNode++;
          }
          else {
            std::cout << ' ';
          }
        }
        else
          std::cout << ' ';
      }
    }
    std::cout << std::endl;
  }
}

tuple handleRender(int &currentNode, int width) {
  int level = getNodeHeight(currentNode);

  int pos = currentNode - (std::pow(2, level) - 1);//wow this is great! thanks chatgpt!

  //its i coordinate will be the level multiplied by the vertical spaces, which we chose to be 3
  int i_coord = 1 + 3 * level;

  int horizontal_spacing = width / (std::pow(2, level) + 1);
  int j_coord = (pos + 1) * horizontal_spacing;


  tuple coords = {
    i_coord,
    j_coord
  };

  return coords;
}

int getNodeHeight(int arrIndex) {
  double d_height = std::log2(arrIndex + 1);
  int height = std::floor(d_height);

  return height;
}
