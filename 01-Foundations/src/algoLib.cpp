#include "./algoLib.hpp"
#include <iostream>
#include <limits>

std::vector<int> getVector(void);
tuple maxCrossingSubarray(std::vector<int> &A, int low, int mid, int high);
tuple findMaxSubarray(std::vector<int> &, int, int);

void implement() {
  // std::vector<int> A = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5,
  // -22, 15, -4, 7};
  std::vector<int> A = getVector();
  tuple T = findMaxSubarray(A, 0, size(A) - 1);
  std::cout << "the subarray A[ " << T.lowIndex + 1 << ". . ."
            << T.highIndex + 1
            << " ] seems to be the maximum subarray, with the sum: "
            << T.subsum;
}

std::vector<int> getVector(void) {
  int n;
  std::cout << "Enter number of elements in the array: ";
  std::cin >> n;
  std::vector<int> A(n);
  std::cout << "\nEnter the " << n << " elements separated by space\n";
  for (int i = 0; i < n; i++) {
    std::cin >> A[i];
  }

  return A;
}

tuple findMaxSubarray(std::vector<int> &A, int low, int high) {
  if (high == low)
    return {low, high, A[low]};
  else {
    int mid = (low + high) / 2;
    tuple leftSum = findMaxSubarray(A, low, mid);

    tuple rightSum = findMaxSubarray(A, mid + 1, high);

    tuple crossSum = maxCrossingSubarray(A, low, mid, high);

    if (leftSum.subsum >= rightSum.subsum and leftSum.subsum >= crossSum.subsum)
      return leftSum;
    else if (rightSum.subsum >= leftSum.subsum and
             rightSum.subsum >= crossSum.subsum)
      return rightSum;
    else
      return crossSum;
  }
}

tuple maxCrossingSubarray(std::vector<int> &A, int low, int mid, int high) {
  int leftSum = std::numeric_limits<int>::min();
  int sum = 0;
  int maxRight;
  int maxLeft;

  for (int i = mid; i > low - 1; i--) {
    sum += A[i];

    if (sum > leftSum) {
      leftSum = sum;
      maxLeft = i;
    }
  }
  int rightSum = std::numeric_limits<int>::min();
  sum = 0;
  for (int j = mid + 1; j < high + 1; j++) {
    sum += A[j];
    if (sum > rightSum) {
      rightSum = sum;
      maxRight = j;
    }
  }

  return {maxLeft, maxRight, leftSum + rightSum};
}

std::vector<int> binary_addition(std::vector<int> &a, std::vector<int> &b) {
  std::vector<int> c(a.size() + 1);
  int carry = 0;
  for (int i = a.size() - 1; i >= 0; --i) {
    int sum = a[i] + b[i] + carry;
    c[i + 1] = sum % 2;
    carry = sum / 2;
  }

  c[0] = carry;

  return c;
}

std::vector<int> binary_addition_2(std::vector<int> &a, std::vector<int> &b) {
  std::vector<int> c(a.size() + 1);
  std::vector<int> rem(c.size());

  for (int i = 0; i < c.size(); i++) {
    if (i > 0) {
      c[c.size() - 1 - i] =
          a[a.size() - 1 - i] + b[b.size() - 1 - i] + rem[rem.size() - i];
    } else {
      c[c.size() - 1 - i] = a[a.size() - 1 - i] + b[b.size() - 1 - i];
    }
    // c[c.size() - i] = c[c.size() - i] % 2;
    rem[rem.size() - 1 - i] = c[c.size() - 1 - i] / 2;
  }

  for (int i = 0; i < c.size(); i++) {
    c[i] = c[i] % 2;
  }

  return c;
}
