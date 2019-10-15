#include <cmath>
#include <cstdio>
/* write your class interface in this file
   write function definitions only if they are very short
 */

class Vector2D {
 private:
  double x;
  double y;

 public:
  void initVector(double init_x, double init_y);
  double getMagnitude() const;
  Vector2D operator+(const Vector2D & rhs) const;
  Vector2D & operator+=(const Vector2D & rhs);

  double dot(const Vector2D & rhs) const;
  void print();
  Vector2D() : x(0.00), y(0.00) {}
  Vector2D(double ix, double iy) : x(ix), y(iy){};
};
