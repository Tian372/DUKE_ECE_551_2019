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
  double dis = 0;
  dis = sqrt(x * x + y * y);
  return dis;
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D sum;
  sum.x = x + rhs.x;
  sum.y = y + rhs.y;
  return sum;
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  double product;
  product = x * rhs.x + y * rhs.y;
  return product;
}
void Vector2D::print() {
  printf("<%.2f, %.2f>", x, y);
}
