#pragma once 

#include <vector>

struct tuple { //data type which agrees with return format of maxCrossingSubarray findMaxSubarray
  int lowIndex;
  int highIndex;
  int subsum;
};

tuple maxCrossingSubarray(std::vector<int> &A, int low, int mid, int high);
tuple findMaxSubarray(std::vector<int> &A, int low, int high);


std::vector<int> binary_addition(std::vector<int> &a, std::vector<int> &b);//done
std::vector<int> binary_addition_2(std::vector<int> &a, std::vector<int> &b);//done


std::vector<int> getVector(void);
void printVector(std::vector<int> &A);

void implement(); //main replacement