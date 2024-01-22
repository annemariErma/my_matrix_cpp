#include <gtest/gtest.h>

#include "my_matrix_oop.h"

using namespace std;

TEST(Constructor, Default_1) {
  MyMatrix A;
  EXPECT_TRUE(0 == A.GetRows() && 0 == A.GetCols());
}

TEST(Constructor, ParamConstructor_SUCCESS) {
  MyMatrix A(3, 4);
  EXPECT_TRUE(3 == A.GetRows() && 4 == A.GetCols());
}

TEST(Constructor, ParamConstructor_throw_1) {
  try {
    MyMatrix A(0, 4);
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Incorrect number of rows or columns.", error.what());
  }
}

TEST(Constructor, ParamConstructor_throw_2) {
  try {
    MyMatrix A(4, -5);
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Incorrect number of rows or columns.", error.what());
  }
}

TEST(Constructor, CopyConstructor_SUCCESS_1) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(A);
  EXPECT_TRUE(A.GetRows() == B.GetRows() && A.GetCols() == B.GetCols() &&
              B(1, 2) == A(1, 2));
}

TEST(Constructor, CopyConstructor_SUCCESS_2) {
  MyMatrix A;
  MyMatrix B(A);
  EXPECT_TRUE(A.GetRows() == B.GetRows() && A.GetCols() == B.GetCols());
}

TEST(Constructor, MoveConstructor_SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(move(A));
  EXPECT_TRUE(A.GetRows() == 0 && A.GetCols() == 0 && B.GetRows() == 3 &&
              B.GetCols() == 4 && B(1, 2) == 3);
}

TEST(EqMatrix, TRUE) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(A);
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(EqMatrix, FALSE_1) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B;
  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(EqMatrix, FALSE_2) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = i + j + 0.0000001;
    }
  }
  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(SumMatrix, SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = 1;
    }
  }
  A.SumMatrix(B);
  MyMatrix C(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      C(i, j) = i + j + 1;
    }
  }
  EXPECT_TRUE(A.EqMatrix(C));
}

TEST(SumMatrix, DifferentSizes_throw) {
  try {
    MyMatrix A(3, 4);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j;
      }
    }
    MyMatrix B;
    A.SumMatrix(B);
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Matrices have different sizes.", error.what());
  }
}

TEST(SubMatrix, SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = 1;
    }
  }
  A.SubMatrix(B);
  MyMatrix C(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      C(i, j) = i + j - 1;
    }
  }
  EXPECT_EQ(A.EqMatrix(C), true);
}

TEST(SubMatrix, DifferentSizes_throw) {
  try {
    MyMatrix A(3, 4);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j;
      }
    }
    MyMatrix B;
    A.SubMatrix(B);
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Matrices have different sizes.", error.what());
  }
}

TEST(MulMatrix, ColsNotEqualRows_throw) {
  try {
    MyMatrix A(3, 4);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j;
      }
    }
    MyMatrix B;
    A.MulMatrix(B);
  } catch (const runtime_error& error) {
    EXPECT_STREQ(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.",
        error.what());
  }
}

TEST(MulMatrix, SUCCESS) {
  MyMatrix D(4, 3);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      D(i, j) = i + j;
    }
  }
  MyMatrix E(3, 5);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      E(i, j) = 1;
    }
  }
  D.MulMatrix(E);
  MyMatrix result(4, 5);
  for (int j = 0; j < 5; j++) {
    result(0, j) = 3;
  }
  for (int j = 0; j < 5; j++) {
    result(1, j) = 6;
  }
  for (int j = 0; j < 5; j++) {
    result(2, j) = 9;
  }
  for (int j = 0; j < 5; j++) {
    result(3, j) = 12;
  }
  EXPECT_TRUE(D.EqMatrix(result));
}

TEST(MulNumber, SUCCESS) {
  MyMatrix D(4, 3);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      D(i, j) = i + j;
    }
  }
  double num = -2;
  D.MulNumber(num);

  MyMatrix E(4, 3);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      E(i, j) = (i + j) * num;
    }
  }

  EXPECT_TRUE(D.EqMatrix(E));
}

TEST(Transpose, SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  A.Transpose();
  MyMatrix A_inv(4, 3);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      A_inv(i, j) = i + j;
    }
  }
  EXPECT_TRUE(A.EqMatrix(A_inv));
}

TEST(Determinant, SUCCESS) {
  MyMatrix A(4, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j + 1;
    }
  }
  A(1, 0) = -3;
  A(0, 1) = 19;
  A(1, 1) = 9;
  A(2, 2) = 16;
  A(2, 1) = 11;
  EXPECT_EQ(A.Determinant(), 6763);
}

TEST(Determinant, OneElement) {
  MyMatrix A(1, 1);
  A(0, 0) = 19;
  EXPECT_EQ(A.Determinant(), 19);
}

TEST(Determinant, TwoTwoElements) {
  MyMatrix A(2, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A(i, j) = i + j + 1;
    }
  }
  EXPECT_EQ(A.Determinant(), -1);
}

TEST(Determinant, DontQadroMatrix_throw) {
  MyMatrix A(2, 3);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      A(i, j) = i + j + 1;
    }
  }
  EXPECT_THROW(A.Determinant(), runtime_error);
}

TEST(CalcComplements, SUCCESS) {
  MyMatrix A(4, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j + 1;
    }
  }
  A(1, 0) = -3;
  A(0, 1) = 19;
  A(1, 1) = 9;
  A(2, 2) = 16;
  A(2, 1) = 11;
  A.CalcComplements();
  MyMatrix B(4, 4);
  B(0, 0) = 426;
  B(0, 1) = 446;
  B(0, 2) = -259;
  B(0, 3) = -340;
  B(1, 0) = -1247;
  B(1, 1) = -99;
  B(1, 2) = 12;
  B(1, 3) = 773;
  B(2, 0) = -16;
  B(2, 1) = 15;
  B(2, 2) = 613;
  B(2, 3) = -527;
  B(3, 0) = 661;
  B(3, 1) = -197;
  B(3, 2) = -386;
  B(3, 3) = 1060;
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(CalcComplements, OneElement) {
  MyMatrix A(1, 1);
  A(0, 0) = 19;
  A.CalcComplements();
  MyMatrix B(1, 1);
  B(0, 0) = 1.;
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(CalcComplements, DontQadroMatrix_throw) {
  try {
    MyMatrix A(2, 3);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 3; j++) {
        A(i, j) = i + j + 1;
      }
    }
    A.CalcComplements();
  } catch (const runtime_error& error) {
    EXPECT_STREQ("The matrix is not square.", error.what());
  }
}

TEST(InverseMatrix, SUCCESS) {
  MyMatrix A(4, 4);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j + 1;
    }
  }
  A(1, 0) = -3;
  A(0, 1) = 19;
  A(1, 1) = 9;
  A(2, 2) = 16;
  A(2, 1) = 11;
  A.InverseMatrix();

  MyMatrix B(4, 4);
  double determinant = 6763.;
  B(0, 0) = 426;
  B(0, 1) = -1247;
  B(0, 2) = -16;
  B(0, 3) = 661;
  B(1, 0) = 446;
  B(1, 1) = -99;
  B(1, 2) = 15;
  B(1, 3) = -197;
  B(2, 0) = -259;
  B(2, 1) = 12;
  B(2, 2) = 613;
  B(2, 3) = -386;
  B(3, 0) = -340;
  B(3, 1) = 773;
  B(3, 2) = -527;
  B(3, 3) = 1060;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = B(i, j) / determinant;
    }
  }
  EXPECT_EQ(A.EqMatrix(B), true);
}

TEST(InverseMatrix, OneElement) {
  MyMatrix A(1, 1);
  A(0, 0) = 19.;
  A.InverseMatrix();
  MyMatrix B(1, 1);
  B(0, 0) = 1. / 19;
  EXPECT_EQ(A.EqMatrix(B), true);
}

TEST(InverseMatrix, DontQadroMatrix_throw) {
  try {
    MyMatrix A(4, 5);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        A(i, j) = i + j + 1;
      }
    }
    A.InverseMatrix();
  } catch (const runtime_error& error) {
    EXPECT_STREQ("The matrix is not square.", error.what());
  }
}

TEST(InverseMatrix, NullDeterminant_throw) {
  try {
    MyMatrix A(4, 4);
    for (int i = 1; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j + 1;
      }
    }
    for (int i = 0; i < 1; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j + 2;
      }
    }
    A.InverseMatrix();
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Matrix determinant is 0.", error.what());
  }
}

TEST(OperatorSum, SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix C(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      C(i, j) = 5;
    }
  }
  MyMatrix B = A + C;
  MyMatrix D(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      D(i, j) = i + j + 5;
    }
  }
  EXPECT_TRUE(B.EqMatrix(D));
}

TEST(OperatorSum, DifferentSizes_throw) {
  try {
    MyMatrix A(3, 4);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j;
      }
    }
    MyMatrix C(5, 4);
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 4; j++) {
        C(i, j) = 5;
      }
    }
    MyMatrix B = A + C;
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Matrices have different sizes.", error.what());
  }
}

TEST(OperatorSub, SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix C(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      C(i, j) = 5;
    }
  }
  MyMatrix B = A - C;
  MyMatrix D(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      D(i, j) = i + j - 5;
    }
  }
  EXPECT_TRUE(B.EqMatrix(D));
}

TEST(OperatorSub, DifferentSizes_throw) {
  try {
    MyMatrix A(3, 4);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j;
      }
    }
    MyMatrix C(5, 4);
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 4; j++) {
        C(i, j) = 5;
      }
    }
    MyMatrix B = A - C;
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Matrices have different sizes.", error.what());
  }
}

TEST(OperatorMul, MatrixMulMatrix_SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix C(4, 2);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      C(i, j) = 5;
    }
  }
  MyMatrix B;
  B = A * C;
  MyMatrix D(3, 2);
  for (int i = 0, j = 0; j < 2; j++) {
    D(i, j) = 30;
  }
  for (int i = 1, j = 0; j < 2; j++) {
    D(i, j) = 50;
  }
  for (int i = 2, j = 0; j < 2; j++) {
    D(i, j) = 70;
  }
  EXPECT_TRUE(B.EqMatrix(D));
}

TEST(OperatorMul, ColsNotEqualRows_throw) {
  try {
    MyMatrix A(3, 4);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j;
      }
    }
    MyMatrix C;
    MyMatrix B = A * C;
  } catch (const runtime_error& error) {
    EXPECT_STREQ(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.",
        error.what());
  }
}

TEST(OperatorMul, MatrixMulNumber_SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix C(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      C(i, j) = (i + j) * 5;
    }
  }
  MyMatrix B = A * 5;
  EXPECT_TRUE(B.EqMatrix(C));
}

TEST(OperatorMul, NumberMulMatrix_SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix C(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      C(i, j) = (i + j) * 5.;
    }
  }
  MyMatrix B = 5. * A;
  EXPECT_TRUE(B.EqMatrix(C));
}

TEST(OperatorComparison, SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(A);
  EXPECT_TRUE(A == B);
}

TEST(OperatorAssaignment, Copy) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(4, 5);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      B(i, j) = 1;
    }
  }
  A = B;
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(OperatorAssaignment, Copy2) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(A);
  A = A;
  EXPECT_TRUE(A.EqMatrix(B));
}

TEST(OperatorAssaignment, MoveOther) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(A);
  MyMatrix C(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      C(i, j) = 5;
    }
  }
  C = std::move(A);  // запускает наш оператор присвоения перемещением
  EXPECT_TRUE(A.GetRows() == 0 && A.GetCols() == 0 && C.EqMatrix(B));
}

TEST(OperatorAssaignment, MoveSelf) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(A);
  A = std::move(A);  // запускает наш оператор присвоения перемещением
  EXPECT_TRUE(A.GetRows() == 3 && A.GetCols() == 4 && A.EqMatrix(B));
}

TEST(OperatorSumAssaignment, SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = 5.;
    }
  }
  MyMatrix C(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      C(i, j) = (i + j) + 5.;
    }
  }
  A += B;
  EXPECT_TRUE(A.EqMatrix(C));
}

TEST(OperatorSumAssaignment, DifferentSizes_throw) {
  try {
    MyMatrix A(3, 4);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j;
      }
    }
    MyMatrix B;
    A += B;
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Matrices have different sizes.", error.what());
  }
}

TEST(OperatorSubAssaignment, SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix B(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = 5.;
    }
  }
  MyMatrix C(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      C(i, j) = (i + j) - 5.;
    }
  }
  A -= B;
  EXPECT_TRUE(A.EqMatrix(C));
}

TEST(OperatorSubAssaignment, DifferentSizes_throw) {
  try {
    MyMatrix A(3, 4);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j;
      }
    }
    MyMatrix B;
    A -= B;
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Matrices have different sizes.", error.what());
  }
}

TEST(OperatorMulAssaignment, MatrixMulMatrix_SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix C(4, 2);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      C(i, j) = 5;
    }
  }
  A *= C;
  MyMatrix D(3, 2);
  for (int i = 0, j = 0; j < 2; j++) {
    D(i, j) = 30;
  }
  for (int i = 1, j = 0; j < 2; j++) {
    D(i, j) = 50;
  }
  for (int i = 2, j = 0; j < 2; j++) {
    D(i, j) = 70;
  }
  EXPECT_TRUE(A.EqMatrix(D));
}

TEST(OperatorMulAssaignment, ColsNotEqualRows_throw) {
  try {
    MyMatrix A(3, 4);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j;
      }
    }
    MyMatrix C;
    A *= C;
  } catch (const runtime_error& error) {
    EXPECT_STREQ(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.",
        error.what());
  }
}

TEST(OperatorMulAssaignment, MatrixMulNumber_SUCCESS) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  MyMatrix C(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      C(i, j) = (i + j) * 5;
    }
  }
  A *= 5;
  EXPECT_TRUE(A.EqMatrix(C));
}

TEST(OperatorIndex, GetElement) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  double element = 0.;
  element = A(1, 1);
  EXPECT_TRUE(element == 2.);
}

TEST(OperatorIndex, SetElement) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  A(1, 1) = 34;
  EXPECT_TRUE(A(1, 1) == 34);
}

TEST(OperatorConstIndex, GetElement_2) {
  const MyMatrix A(3, 4);
  // double element=0.;
  double element = A(1, 1);
  EXPECT_TRUE(element == 0);
}

TEST(OperatorIndex, IndexOutside_throw) {
  try {
    MyMatrix A(3, 4);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        A(i, j) = i + j;
      }
    }
    A(1, 6);
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Index outside of matrix size.", error.what());
  }
}

TEST(OperatorConstIndex, IndexOutside_throw) {
  try {
    const MyMatrix A(3, 4);
    A(1, 6);
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Index outside of matrix size.", error.what());
  }
}

TEST(Mutator, SetRowsLessOrigin) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  A.SetRows(2);
  MyMatrix B(2, 4);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = i + j;
    }
  }
  EXPECT_TRUE(A.EqMatrix(B) && A.GetRows() == 2);
}

TEST(Mutator, SetRowsMoreOrigin) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  A.SetRows(5);
  MyMatrix B(5, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = i + j;
    }
  }
  EXPECT_TRUE(A.EqMatrix(B) && A.GetRows() == 5);
}

TEST(Mutator, SetRowsIncorrectValue_throw) {
  try {
    MyMatrix A(3, 4);
    A.SetRows(0);
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Incorrect number of rows.", error.what());
  }
}

TEST(Mutator, SetColsLessOrigin) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  A.SetCols(2);
  MyMatrix B(3, 2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      B(i, j) = i + j;
    }
  }
  EXPECT_TRUE(A.EqMatrix(B) && A.GetCols() == 2);
}

TEST(Mutator, SetColsMoreOrigin) {
  MyMatrix A(3, 4);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A(i, j) = i + j;
    }
  }
  A.SetCols(5);
  MyMatrix B(3, 5);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      B(i, j) = i + j;
    }
  }
  EXPECT_TRUE(A.EqMatrix(B) && A.GetCols() == 5);
}

TEST(Mutator, SetColsIncorrectValue_throw) {
  try {
    MyMatrix A(3, 4);
    A.SetCols(0);
  } catch (const runtime_error& error) {
    EXPECT_STREQ("Incorrect number of cols.", error.what());
  }
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
