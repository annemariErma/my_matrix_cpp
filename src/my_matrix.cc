//created by M.Ermakova (Annemari)
#include "My_matrix_oop.h"

// конструктор по-умолчанию
MyMatrix::MyMatrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

// параметризированный конструктор
MyMatrix::MyMatrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
    //Класс runtime_error наследует от exception и принимает строку
    throw std::runtime_error("Incorrect number of rows or columns.");
  }
  rows_ = rows;
  cols_ = cols;
  MemoryAllocate();
}

// конструктор копирования
MyMatrix::MyMatrix(const MyMatrix& other)
    : rows_(0), cols_(0), matrix_(nullptr) {  //
  *this = other;
}

// конструктор переноса
MyMatrix::MyMatrix(MyMatrix&& other) noexcept
    : rows_(0), cols_(0), matrix_(nullptr) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

// деструктор
MyMatrix::~MyMatrix() {
  for (int i = 0; i < rows_; i++) {
    if (matrix_[i]) delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

// Проверяет матрицы на равенство между собой
bool MyMatrix::EqMatrix(const MyMatrix& other) noexcept {
  bool flag_err = true;
  if (!CheckEqMatrixSizes(other)) {
    return false;
  }
  for (int i = 0; flag_err == true && i < rows_; ++i) {
    for (int j = 0; flag_err == true && j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= PRECISION) {
        flag_err = false;
      }
    }
  }
  return flag_err;
}

// Прибавляет вторую матрицу к текущей
void MyMatrix::SumMatrix(const MyMatrix& other) {
  if (!CheckEqMatrixSizes(other)) {
    throw std::runtime_error("Matrices have different sizes.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

// Вычитает из текущей матрицы другую
void MyMatrix::SubMatrix(const MyMatrix& other) {
  if (!CheckEqMatrixSizes(other)) {
    throw std::runtime_error("Matrices have different sizes.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

// Умножает текущую матрицу на число
void MyMatrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

// Умножает текущую матрицу на вторую
void MyMatrix::MulMatrix(const MyMatrix& other) {
  if (cols_ != other.rows_) {
    throw std::runtime_error(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.");
  }
  MyMatrix result_matrix(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result_matrix.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result_matrix;
}

// Создает новую транспонированную матрицу из текущей и возвращает ее
MyMatrix MyMatrix::Transpose() {
  MyMatrix new_matrix(cols_, rows_);
  for (int i = 0; i < new_matrix.rows_; ++i) {
    for (int j = 0; j < new_matrix.cols_; ++j) {
      new_matrix.matrix_[i][j] = matrix_[j][i];
    }
  }
  *this = new_matrix;
  return *this;
}

// Вычисляет и возвращает определитель текущей матрицы
double MyMatrix::Determinant() {
  if (rows_ != cols_) {
    throw std::runtime_error("The matrix is not square.");
  }
  double determinant = 1.;
  if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else if (rows_ == 2) {
    determinant = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    TriangularView();
    for (int i = 0; i < rows_; ++i) {
      determinant = determinant * matrix_[i][i];
    }
  }
  return determinant;
}

// приведение к треугольному виду по методу Гаусса через опорный элемент
MyMatrix MyMatrix::TriangularView() {
  int i = 0, j = 0, k = 0, swap_count = 1;
  MyMatrix new_matrix(*this);
  for (i = 0; i < rows_; ++i) {
    // находим строку с максимальным первым элементом
    int max_element_in_i_string = i;
    for (j = i + 1; j < rows_; ++j) {
      if (fabs(new_matrix.matrix_[j][i]) >
          fabs(new_matrix.matrix_[max_element_in_i_string][i])) {
        max_element_in_i_string = j;
      }
    }
    if (fabs(new_matrix.matrix_[max_element_in_i_string][i]) < 1e-9) {
      continue;
    }
    for (k = 0; k < cols_; ++k) {
      std::swap(new_matrix.matrix_[i][k],
                new_matrix.matrix_[max_element_in_i_string][k]);
    }
    swap_count = -swap_count * (i != max_element_in_i_string ? 1 : -1);
    //  вычитаем текущую строку из всех остальных
    for (j = i + 1; j < rows_; ++j) {
      double q = -new_matrix.matrix_[j][i] / new_matrix.matrix_[i][i];
      for (k = cols_ - 1; k >= i; k--) {
        new_matrix.matrix_[j][k] += q * new_matrix.matrix_[i][k];
      }
    }
  }
  // умножаем матрицу на -1, если мы сделали  нечётное количество
  // перестановок строк
  if (swap_count == -1) {
    new_matrix.MulNumber(swap_count);
  }
  *this = new_matrix;
  return *this;
}

//Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
MyMatrix MyMatrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::runtime_error("The matrix is not square.");
  }
  MyMatrix temp(rows_, cols_);
  if (rows_ == 1) {
    temp(0, 0) = 1.;
  } else {
    for (int i = 0; i < temp.rows_; ++i) {
      for (int j = 0; j < temp.cols_; ++j) {
        MyMatrix sub_matrix;
        sub_matrix.SubMatrixFromMain(*this, i, j);
        double result = sub_matrix.Determinant();
        temp.matrix_[i][j] = result * ((i + j) % 2 == 0 ? 1 : -1);
      }
    }
  }
  *this = temp;
  return *this;
}

MyMatrix MyMatrix::SubMatrixFromMain(MyMatrix& other, int i_rows,
                                       int j_cols) {
  MyMatrix sub_matrix(other.rows_ - 1, other.cols_ - 1);
  for (int i = 0; i < i_rows; ++i) {
    for (int j = 0; j < j_cols; ++j) {
      sub_matrix.matrix_[i][j] = other.matrix_[i][j];
    }
    for (int j = j_cols + 1; j < other.cols_; ++j) {
      sub_matrix.matrix_[i][j - 1] = other.matrix_[i][j];
    }
  }

  for (int i = i_rows + 1; i < other.rows_; ++i) {
    for (int j = 0; j < j_cols; ++j) {
      sub_matrix.matrix_[i - 1][j] = other.matrix_[i][j];
    }
    for (int j = j_cols + 1; j < other.cols_; ++j) {
      sub_matrix.matrix_[i - 1][j - 1] = other.matrix_[i][j];
    }
  }
  *this = sub_matrix;
  return *this;
}

//Вычисляет и возвращает обратную матрицу
MyMatrix MyMatrix::InverseMatrix() {
  MyMatrix temp(*this);
  double determinant = 0.;
  determinant = temp.Determinant();
  if (determinant == 0) {
    throw std::runtime_error("Matrix determinant is 0.");
  }
  temp = *this;
  if (rows_ == 1) {
    temp.matrix_[0][0] = 1. / determinant;
  } else {
    temp.CalcComplements();
    temp.Transpose();
    temp.MulNumber(1. / determinant);
  }
  *this = temp;
  return *this;
}

// Операторы
MyMatrix MyMatrix::operator+(const MyMatrix& other) const {
  MyMatrix result(*this);
  result.SumMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator-(const MyMatrix& other) const {
  MyMatrix result(*this);
  result.SubMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator*(const MyMatrix& other) const {
  MyMatrix result(*this);
  result.MulMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator*(const double num) const {
  MyMatrix result(*this);
  result.MulNumber(num);
  return result;
}

MyMatrix operator*(const double num, const MyMatrix& other) {
  MyMatrix result(other);
  result.MulNumber(num);
  return result;
}

bool MyMatrix::operator==(const MyMatrix& other) {
  return MyMatrix::EqMatrix(other);  // или так return this->EqMatrix(other);
}

// оператор присвоения копированием
MyMatrix& MyMatrix::operator=(const MyMatrix& other) {
  if (this == &other) {
    return *this;
  }
  if (!other.CheckMatrixParam()) {
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  } else {
    if (!matrix_) {
      rows_ = other.rows_;
      cols_ = other.cols_;
      MemoryAllocate();
    } else {
      SetRows(other.rows_);
      SetCols(other.cols_);
    }
  }
  CopyElementsFromRange(other, other.rows_, other.cols_);
  return *this;
}

//оператор присвоения переносом
MyMatrix& MyMatrix::operator=(MyMatrix&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  for (int i = 0; i < other.rows_; ++i) {
    if (other.matrix_[i]) delete[] other.matrix_[i];
  }
  delete[] other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
  return *this;
}

MyMatrix& MyMatrix::operator+=(const MyMatrix& other) {
  SumMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator-=(const MyMatrix& other) {
  SubMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator*=(const MyMatrix& other) {
  MulMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& MyMatrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::runtime_error("Index outside of matrix size.");
  }
  return this->matrix_[i][j];
}

const double& MyMatrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::runtime_error("Index outside of matrix size.");
  }
  return this->matrix_[i][j];
}

// Accessors и mutators
int MyMatrix::GetRows() { return rows_; }

int MyMatrix::GetCols() { return cols_; }

MyMatrix MyMatrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::runtime_error("Incorrect number of rows.");
  }
  MyMatrix temp(rows, cols_);
  temp.CopyElementsFromRange(*this, std::min(rows, rows_), cols_);
  std::swap(*this, temp);
  return *this;
}

MyMatrix MyMatrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::runtime_error("Incorrect number of cols.");
  }
  MyMatrix temp(rows_, cols);
  temp.CopyElementsFromRange(*this, rows_, std::min(cols, cols_));
  std::swap(*this, temp);
  return *this;
}

// Additional
//Выделение памяти
void MyMatrix::MemoryAllocate() {
  matrix_ = new double*[rows_];
  if (matrix_ != NULL) {
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_]();
    }
  }
}

// Проверка параметров матрицы на корректность
bool MyMatrix::CheckMatrixParam() const { return (rows_ > 0 && cols_ > 0); }

// Проверка равенства размеров матриц
bool MyMatrix::CheckEqMatrixSizes(const MyMatrix& other) const {
  return (rows_ == other.rows_ && cols_ == other.cols_);
}

// Копирование из заданного диапазона
void MyMatrix::CopyElementsFromRange(const MyMatrix& other, int rows,
                                      int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
