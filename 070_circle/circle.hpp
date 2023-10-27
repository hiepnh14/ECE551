// Class cicle
#include "point.hpp"

class Circle {
 private:
  Point center;  // Private member variablef ro the center of the cicle
  const double radius;

 public:
  // Constructor that initializes the Circle with a center and a radius
  Circle(const Point & c, double r) : center(c), radius(r) {}
  // Method to move the circle's center by dx and dy
  void move(double dx, double dy);
  // Get fucntions to access to private members
  Point getCenter() const;
  double getRadius() const;
  // Method to compute the area of intersection with another Circle
  double intersectionArea(const Circle & otherCircle);
};
