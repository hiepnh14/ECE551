#include "Matrix.h"

Matrix::Matrix() : numRows(0), numColumns(0), rows(NULL) {
}
Matrix::Matrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new T **[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new T *[numColumns];
  }
}
Matrix::Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
  rows = new T **[numRows];
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      rows[i][j] = new T(rhs[i][j]);
    }
  }
}
Matrix::~Matrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

Matrix & Matrix::operator=(const Matrix & rhs) {
  if (this != &rhs) {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    numColumns = rhs.numColumns;
    numRows = rhs.numRows;
    rows = new T **[numRows];
    for (int i = 0; i < numRows; i++) {
      rows[i] = new T *[numColumns];
      for (int j = 0; j < numColumns; j++) {
        rows[i][j] = rhs.rows[i][j];
      }
    }
  }

  return *this;
}
int Matrix::getRows() const {
  return numRows;
}
int Matrix::getColumns() const {
  return numColumns;
}
const T *& Matrix::operator[](int index) const {
  assert((0 <= index) && (index < numRows));
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert((0 <= index) && (index < numRows));
  return *rows[index];
}
bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows) {
    return false;
  }
  if (numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if ((*this)[i] != *rhs.rows[i]) {
      return false;
    }
  }
  return true;
}
