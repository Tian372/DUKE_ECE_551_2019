#include "circle.h"

#include <cmath>
#define PI 3.141592653589793

Circle::Circle(Point c, double r) : center(c), radius(r) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  const double dist = center.distanceFrom(otherCircle.center);

  if (dist >= radius + otherCircle.radius) {
    return 0.0;
  }
  if (dist <= std::abs(radius - otherCircle.radius)) {
    return PI * pow(fmin(radius, otherCircle.radius), 2);
  }
  const double a_pow = pow(radius, 2);
  const double b_pow = pow(otherCircle.radius, 2);

  const double mid_dist1 = (a_pow - b_pow + pow(dist, 2)) / (2 * dist);
  const double mid_dist2 = dist - mid_dist1;
  const double height = sqrt(pow(radius, 2) - pow(mid_dist1, 2));

  const double alpha1 = std::fmod(std::atan2(height, mid_dist1) * 2.0 + 2 * PI, 2 * PI);
  const double alpha2 = std::fmod(std::atan2(height, mid_dist2) * 2.0 + 2 * PI, 2 * PI);

  const double A0 = std::pow(radius, 2) / 2.0 * (alpha1 - std::sin(alpha1));
  const double A1 = std::pow(otherCircle.radius, 2) / 2.0 * (alpha2 - std::sin(alpha2));
  return A0 + A1;
}
