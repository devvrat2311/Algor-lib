#include "./matrix.hpp"
#include <cmath>
#include <initializer_list>
#include <iostream>

Matrix::Matrix(int n) {
  this->n = n;
  m.resize(n, std::vector<int>(n));
}

Matrix::Matrix() {
  this->n = 1;
  m.resize(n, std::vector<int>(n));
}

Matrix::Matrix(std::initializer_list<int> values) {
  n = static_cast<int>(std::sqrt(values.size()));
  m.resize(n, std::vector<int>(n));

  int index = 0;
  for (auto val : values) {
    int row = index / n;
    int col = index % n;
    m[row][col] = val;
    ++index;
  }
}

/*
with the quadrant function, what we want is, given the
options 11, 12, 21, 22 we should be able to get the
appropriate sub-matrix from A. Should this submatrix
in cpp be another instance of the class matrix? I think
yes, because when objects of this class will be used in
a recursive manner, I want each submatrix to be able to
divide into further sub-matrices. So I will design this
member function to return the appropriate submatrix.
*/
void Matrix::display() {
  for (int i = 0; i < this->n; ++i) {
    for (int j = 0; j < this->n; ++j) {
      std::cout << m[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}
Matrix Matrix::QuadrantDivision(int r, int c) {
  if (n == 1) {
    return m[0][0];
  }
  int row_index;
  int col_index;

  if (r == 1 and c == 1) {
    row_index = 0;
    col_index = 0;
  } else if (r == 1 and c == 2) {
    row_index = 0;
    col_index = n / 2;
  } else if (r == 2 and c == 1) {
    row_index = n / 2;
    col_index = 0;
  } else {
    row_index = n / 2;
    col_index = n / 2;
  }
  // std::cout << "row_index: " << row_index << " col_index: " << col_index <<
  // std::endl;
  int nn = n / 2;
  Matrix subMatrix(nn);
  for (int i = 0, roww = row_index; i < n / 2; i++, roww++) {
    for (int j = 0, coll = col_index; j < n / 2; j++, coll++) {
      subMatrix.putVal(i, j, m[roww][coll]);
    }
  }
  return subMatrix;
}

Matrix QuadrantJoin(Matrix &A11, Matrix &A12, Matrix &A21, Matrix &A22) {
  int nByTwo = A11.size();
  Matrix final(2 * nByTwo);
  int qSubRow = 1;
  int qSubCol = 1;

  while (qSubRow != 3) {
    qSubCol = 1;
    while (qSubCol != 3) {
      for (int i = 0; i < nByTwo; i++) {
        for (int j = 0; j < nByTwo; j++) {
          if (qSubRow == 1) {   // case1-
            if (qSubCol == 1) { // case 11
              final.putVal(i, j, A11.getVal(i, j));
            } else { // case 12
              final.putVal(i, j + nByTwo, A12.getVal(i, j));
            }
          } else { // case 2-
            if (qSubCol == 1) {
              final.putVal(i + nByTwo, j, A21.getVal(i, j));
            } else {
              final.putVal(i + nByTwo, j + nByTwo, A22.getVal(i, j));
            }
          }
        }
      }
      qSubCol++;
    }
    qSubRow++;
  }
  return final;
}

Matrix squareMatrixMultiplyRecursive(Matrix A, Matrix B) {
  int n = A.size();

  Matrix C(n);

  if (n == 1) {
    C.putVal(0, 0, A.getVal(0, 0) * B.getVal(0, 0));
    // C.display();
    return C;
  }

  else {
    Matrix c11 = squareMatrixMultiplyRecursive(A.QuadrantDivision(1, 1),
                                               B.QuadrantDivision(1, 1)) +
                 squareMatrixMultiplyRecursive(A.QuadrantDivision(1, 2),
                                               B.QuadrantDivision(2, 1));

    Matrix c12 = squareMatrixMultiplyRecursive(A.QuadrantDivision(1, 1),
                                               B.QuadrantDivision(1, 2)) +
                 squareMatrixMultiplyRecursive(A.QuadrantDivision(1, 2),
                                               B.QuadrantDivision(2, 2));

    Matrix c21 = squareMatrixMultiplyRecursive(A.QuadrantDivision(2, 1),
                                               B.QuadrantDivision(1, 1)) +
                 squareMatrixMultiplyRecursive(A.QuadrantDivision(2, 2),
                                               B.QuadrantDivision(2, 1));

    Matrix c22 = squareMatrixMultiplyRecursive(A.QuadrantDivision(2, 1),
                                               B.QuadrantDivision(1, 2)) +
                 squareMatrixMultiplyRecursive(A.QuadrantDivision(2, 2),
                                               B.QuadrantDivision(2, 2));

    C = QuadrantJoin(c11, c12, c21, c22);
  }

  // C.display();

  return C;
}

int Matrix::size() { return this->n; }

int Matrix::getVal(int row, int col) { return m[row][col]; }

void Matrix::putVal(int row, int col, int val) { m[row][col] = val; }

Matrix Matrix::operator+(const Matrix &addend) const {
  Matrix result(n);
  // int x = addend.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result.m[i][j] = m[i][j] + addend.m[i][j];
    }
  }
  return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
  Matrix result(n);
  result = squareMatrixMultiplyRecursive(*this, other);

  return result;
}
