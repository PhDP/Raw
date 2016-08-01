#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

auto main(int argc, char **argv) -> int {
  const clock_t start = clock();
  mt19937_64 r(time(0));
  uniform_real_distribution<double> unif(0.0, 1.0);

  const uint64_t n = argc > 1? atoi(argv[1]) : 100000000;
  cout << "Estimating pi with " << n << " random points." << endl;
  uint64_t success = 0;
  for (uint64_t i = 0; i < n; ++i) {
    // Creates points in the unit square:
    const double x = unif(r);
    const double y = unif(r);
    // Tests if they are within the unit circle:
    success += (x * x + y * y) < 1.0;
  }

  // Print estimate of pi:
  cout << "Pi ~= %f!\n" << (4.0 * success / n)
       << "Time: " << ((double)(clock() - start) / CLOCKS_PER_SEC)
       << " seconds." << endl;

  return 0;
}
