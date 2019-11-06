#include <math.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class FFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int r = 0;
  if (low == high) {
    r = 1;
  }
  else if (low > high) {
    r = 1;
  }
  else {
    r = log2(high - low) + 1;
  }
  CountedIntFn * ff = new CountedIntFn(r, f, mesg);
  int result = binarySearchForZero(ff, low, high);
  if (result != expected_ans) {
    fprintf(stderr, "Wrong output answer in %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  SinFunction * sf = new SinFunction();
  check(sf, 0, 150000, 52359, "Sin\n");
  FFunction * ff = new FFunction();
  check(ff, 1, 1, 1, "Positive Empty\n");
  check(ff, 0, 2, 0, "Zero,no negative\n");
  check(ff, -1, 1, 0, "Zero\n");
  check(ff, -5, -2, -3, "Negative\n");
  check(ff, -5, 0, -1, "No Positive\n");
  check(ff, 1, 5, 1, "All positive");
  check(ff, -2, 4, 0, "Large log");
}
