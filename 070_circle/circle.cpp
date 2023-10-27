#include "circle.hpp"

#include <algorithm>
#include <cmath>

// Impelementation of the move method:
void Circle::move(double dx, double dy) {
  center.move(dx, dy);  // Delegates the movement to the Point class
}

double Circle::intersectionArea(const Circle & otherCircle) {
  // calculate the distance between the centers of the two circle
  double distance = center.distanceFrom(otherCircle.center);

  //If the circles dont' intersect, or one is entirely within the other, return 0
  if (distance >= radius + otherCircle.radius) {
    return 0.0;
  }
  if (distance <= std::abs(radius - otherCircle.radius)) {
    double pi = M_PI;
    return pi * std::min(radius, otherCircle.radius) *
           std::min(radius, otherCircle.radius);
  }
  // Calculate the areas of the two circle segments
  double r1 = radius;
  double r2 = otherCircle.radius;
  double d = distance;

  double arg1 = std::acos((r1 * r1 - r2 * r2 + d * d) / (2.0 * d * r1));
  double arg2 = std::acos((r2 * r2 - r1 * r1 + d * d) / (2.0 * d * r2));

  // Calculate the intersection area
  double intersection = r1 * r1 * arg1 + r2 * r2 * arg2 - d * r1 * sin(arg1);
  return intersection;
}
