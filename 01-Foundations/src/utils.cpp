#include <iostream>
#include "utils.hpp"

void displayVec(std::vector<int> a) {
  for(int element : a) {
    std::cout << element << '\t';
  }
  std::cout << '\n';
  return;
}