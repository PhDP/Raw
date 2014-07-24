#include <assert.h>
#include "../src/rng.c"

int main() {
  rd_rng r;
  rd_rng_init_time(&r);
  const int max = 1024;
  double sum = 0.0;
  for (int i = 0; i < max; ++i) {
    const double x = rd_rng_double(&r);
    sum += x;
    assert(x >= 0.0 && x < 1.0);
  }
  const double avr = sum / max;
  assert(avr > 0.45 && avr < 0.55); // P(0.45 < x < 0.55) > 0.99913...
  return EXIT_SUCCESS;
}
