#pragma once

#include <initializer_list> //this is used for Matrix(std::initializer_list<int> values) constructor function
#include <vector>

class Matrix {
private:
  int n;
  std::vector<std::vector<int>> m;

public:
  // constructors :-
  Matrix(int); // constructor with side n, will construct an n x n square matrix

  Matrix();    // default constructor, will construct a 1 x 1 square matrix

  Matrix(std::initializer_list<int> values);           // Construct a matrix with initializer list

  int size(); // side size

  int getVal(int row, int col); // gets value at m[row][col] where m is the base // matrix -> a private entity

  void putVal(int row, int col, int val); // puts value at m[row][col] where m is the base matrix // -> a private entity

  void display();       // displays matrix by running two for loops (nested)

  Matrix operator+(const Matrix &addend) const; // Basic matrix addition operator 


  Matrix operator*(const Matrix &other) const;

  // Indexing the A matrix as (1,1), (1,2), (2,1), (2,2)
  Matrix QuadrantDivision(int, int); // Divides the matrix into 4 quadrants, refer to // CLRS chapter 01 part 04 divide and conquer.  Matrix operator*(const Matrix &other) const;
};

Matrix QuadrantJoin(Matrix &, Matrix &, Matrix &, Matrix &); // Rejoins the 4 divided matrices from before
Matrix squareMatrixMultiplyRecursive(Matrix A, Matrix B); // Multiplies two matrices recursively.