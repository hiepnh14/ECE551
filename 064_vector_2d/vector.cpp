#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
void Vector2D::initVector(double init_x, double init_y) {
  x = init_x;
  y = init_y;
}
double Vector2D::getMagnitude() const {
  double temp = x * x + y * y;
  return std::sqrt(temp);
}
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans;
  ans.initVector(x, y);
  ans.x = x + rhs.x;
  ans.y = y + rhs.y;
  return ans;
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  this->x = this->x + rhs.x;
  this->y = this->y + rhs.y;
  return *this;
}
double Vector2D::dot(const Vector2D & rhs) const {
  //Vector2D ans;
  return (x * rhs.x + y * rhs.y);
}
void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
