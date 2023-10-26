#include "point.hpp"

#include <cmath>

void Point::move(double dx, double dy) {
  x = x + dx;
  y = y + dy;
}
double Point::distanceFrom(const Point & p) {
  // Distance Square
  double temp = (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
  return std::sqrt(temp);
}
