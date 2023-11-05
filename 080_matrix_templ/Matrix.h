#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    for (int i = 0; i < numRows; i++) {
      std::vector<T> row(numColumns);
      rows.push_back(row);
    }
  }
  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {}
  ~Matrix() {}
  Matrix<T> & operator=(const Matrix<T> & rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
    return *this;
  }
  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert((numColumns == rhs.numColumns) && (numRows == rhs.numRows));
    Matrix<T> ans(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans[i][j] = rows[i][j] + rhs.rows[i][j];
      }
    }
    return ans;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(0 <= index && index < numRows);
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(0 <= index && index < numRows);
    return rows[index];
  }
  bool operator==(const Matrix<T> & rhs) const {
    if ((numRows != rhs.numRows) || numColumns != rhs.numColumns || rows != rhs.rows) {
      return false;
    }
    else {
      return true;
    }
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << "]";
  return s;
}
template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> rhs) {
  s << "{ ";
  for (size_t i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i != rhs.size() - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}
#endif
