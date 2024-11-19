#include <algorithm>
#include <iostream>
#include <limits>
#include "./sorting.hpp"
#include "./heap.hpp"
#include "./utils.hpp"

int linear_search(std::vector<int> A, int key) {
  for(int i = 0; i < (int)size(A); ++i) {
    if(A[i] == key)
      return i;
  }
  return -1;
}

int binary_search(std::vector<int> A, int key) {
  return callbinarySearch(A, key, 0, size(A) - 1);
}

int callbinarySearch(std::vector<int> &A, int key, int begin_index, int end_index) {
  //base case
  if(begin_index == end_index) {
    if(A[begin_index] == key)
      return begin_index;
    else
      return -1;
  }
  //iterative case
  else {
    int mid = begin_index + ((end_index - begin_index) / 2);
    if(key <= A[mid])
      return callbinarySearch(A, key, begin_index, mid);
    else
      return callbinarySearch(A, key, mid + 1, end_index);
  }
  std::cout << "\nThere were no errors till here\n";
}

void insertion_sort(std::vector<int> &A) {
  int j;
  for(j = 1; j < (int)size(A); ++j) {
    int key = A[j];
    int i = j - 1;

    while(i >= 0 and A[i] > key) {
      A[i+1] = A[i];
      i--;
    }
    A[i+1] = key;
  }
  displayVec(A);
}

void selection_sort(std::vector<int> &A) {
  for(int j = 0; j < (int)size(A); ++j) {
    int min = j;
    for(int i = j; i < (int)size(A); ++i) { //searches for the minimum element of this iteration
      if(A[min] > A[i])
        min = i;
    }
    std::cout << "The minimum value in this iteration is: " << A[min] << '\n';
    std::swap(A[j], A[min]);
  }
}

//Merge Sort
void merge_sort(std::vector<int> &A, int begin_index, int end_index) {
  if(begin_index < end_index) {
    int mid_index = (begin_index + end_index) / 2; //int automatically sets as floor int
    merge_sort(A, begin_index, mid_index);
    merge_sort(A, mid_index + 1, end_index);
    merge(A, begin_index, mid_index, end_index);
  }
  return;
}

//Merge procedure
void merge(std::vector<int> &A, int begin_index, int mid_index, int end_index) {
  int n1 = mid_index - begin_index + 1;
  int n2 = end_index - mid_index;

  std::vector<int> L(n1 + 1);
  std::vector<int> R(n2 + 1);

  for(int i = 0; i < n1; ++i) {
    L[i] = A[begin_index + i];
  }
  L[n1] = std::numeric_limits<int>::max(); //represents infinity, called a sentinel card

  for(int i = 0; i < n2; ++i) {
    R[i] = A[mid_index + 1 + i];
  }
  R[n2] = std::numeric_limits<int>::max(); //represents infinity, called a sentinel card

  /*we add the last entry as infinity so that if either
  of the arrays (Left or Right) reaches the end of all elements,
  there is still one infinite element left to compare the
  elements of the the other array with, which will result in
  a straightforward dumping of all the elements left in the other
  array into the merged array*/

  int i = 0;
  int j = 0;

  for(int k = begin_index; k < end_index + 1; ++k) {
    if(L[i] <= R[j]) {
      A[k] = L[i];
      i = i + 1;
    }
    else {
      A[k] = R[j];
      j = j + 1;
    }
  }
}

void bubble_sort(std::vector<int> &A) {
  int n = size(A);

  for(int i = 0; i < n - 1; i++) {
    for(int j = n - 1; j > i; j--) {
      if(A[j] < A[j - 1])
        std::swap(A[j], A[j - 1]);
    }
  }
}

void bubble_sort_v2(std::vector<int> &A) {
    bool swapped;

    do {
        swapped = false;
        for(int i = 0; i < (int)A.size() - 1; ++i) {
            if(A[i] > A[i + 1]) {
                swapped = true;
                int aux = A[i];
                A[i] = A[i + 1];
                A[i + 1] = aux;
            }
        }
    }while(swapped);
}

void heap_sort(std::vector<int> &A) {
  Heap h(A);
  for(int i = h.heap_size - 1; i > 0; --i) {
    std::swap(h.array[0], h.array[i]);
    h.heap_size--;
    h.max_heapify(0);
  }
  A = h.array;
}
