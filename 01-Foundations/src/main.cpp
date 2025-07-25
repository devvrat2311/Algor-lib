#include "sorting.hpp"
#include "utils.hpp"
#include "heap.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int main() {

    // std::vector<int> A = {1, 3, 5, 23, 11, 22, 33};


    std::vector<int> A = {2, 34, 1, 76, 909, 5, 7};

    // displayVec(A);
    // merge_sort(A, 0, A.size() - 1);
    // displayVec(A);
    Heap heap_A(A);
    drawHeapProper(heap_A);

    heap_sort(A);
    drawHeapProper(heap_A);
    // std::cout << "\n\n";

    // std::reverse(A.begin(), A.end());
    // displayVec(A);
    // Heap heap_rev_A(A);
    // drawHeapProper(heap_rev_A);

    // bubble_sort_v2(B);
    // bubble_sort_v2(B);
    // displayVec(B);
}
