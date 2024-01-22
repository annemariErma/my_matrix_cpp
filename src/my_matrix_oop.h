#ifndef MATRIX_CPP_MY_MATRIX_OOP_H_
#define MATRIX_CPP_MY_MATRIX_OOP_H_

#include <exception>
#include <iostream>
#include <math.h>

#include <string_view>  // std::swap since C++17

#define PRECISION 1E-7

class MyMatrix {
 public:
  MyMatrix();                            // default constructor
  MyMatrix(int rows, int cols);          // parameterized constructor
  MyMatrix(const MyMatrix& other);      // copy cnstructor
  MyMatrix(MyMatrix&& other) noexcept;  // move cnstructor
  ~MyMatrix();                           // destructor

  // some operators overloads
  MyMatrix& operator=(const MyMatrix& other);
  MyMatrix& operator=(MyMatrix&& other) noexcept;
  bool operator==(const MyMatrix& other);
  MyMatrix& operator+=(const MyMatrix& other);
  MyMatrix& operator-=(const MyMatrix& other);
  MyMatrix& operator*=(const MyMatrix& other);
  MyMatrix& operator*=(const double num);
  MyMatrix operator+(const MyMatrix& other) const;
  MyMatrix operator-(const MyMatrix& other) const;
  MyMatrix operator*(const MyMatrix& other) const;
  MyMatrix operator*(const double num) const;
  friend MyMatrix operator*(const double num, const MyMatrix& other);
  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;

  // some public methods
  bool EqMatrix(const MyMatrix& other) noexcept;
  void SumMatrix(const MyMatrix& other);
  void SubMatrix(const MyMatrix& other);
  void MulNumber(const double num);
  void MulMatrix(const MyMatrix& other);
  MyMatrix Transpose();
  double Determinant();
  MyMatrix CalcComplements();
  MyMatrix InverseMatrix();
  int GetRows();
  int GetCols();
  MyMatrix SetRows(int rows);
  MyMatrix SetCols(int cols);

  // additional
  void MemoryAllocate();
  bool CheckMatrixParam() const;
  bool CheckEqMatrixSizes(const MyMatrix& other) const;
  MyMatrix TriangularView();
  MyMatrix SubMatrixFromMain(MyMatrix& other, int i_rows, int j_cols);
  void CopyElementsFromRange(const MyMatrix& other, int rows, int cols);

 private:
  // attributes
  int rows_, cols_;  // rows and columns attributes
  double** matrix_;  // pointer to the memory where the matrix will be allocated
};

#endif  // MATRIX_CPP_MY_MATRIX_OOP_H_
