#pragma once

#include <vector>

#define newline std::cout << '\n'

struct tuple {
  int i_coord;
  int j_coord;
};

class Heap { // max heap
public:
  int heap_size;
  int array_size;
  std::vector<int> array;

  Heap(std::vector<int>&);

  int left(int);
  int right(int);
  int parent(int);

  void max_heapify(int);
  void build_max_heap();
};

void drawHeapMinimal(Heap heap);
void drawHeapProper(Heap heap);
tuple handleRender(int &currentNode, int width);

int getNodeHeight(int arrIndex);
