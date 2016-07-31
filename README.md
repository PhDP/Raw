<p align='center'>
  <img src='http://phdp.github.io/images/randamu.png' alt='Randamu logo'/>
</p>

[![Build status](https://travis-ci.org/PhDP/Randamu.svg?branch=master)](https://travis-ci.org/PhDP/Randamu)
[![Build status](https://ci.appveyor.com/api/projects/status/9nqqxwsbdufa2wfj)](https://ci.appveyor.com/project/PhilippeDesjardinsProulx/randamu-855)

...

The bogosort algorithm is a joke (don't use it!), but everything
else is not.

References
----------

* Sebastiano Vigna. An experimental exploration of Marsaglia's xorshift generators, scrambled. ACM Trans. Math. Software, 42(4), 2016.
* FO Panneton, P L'Ecuyer, and M Matsumoto. Improved long-period generators based on linear recurrences modulo 2. ACM Transactions on Mathematical Software 32 (1): 1–16, 2006.

Installing
----------
On Linux or UNIX-like systems:

    $ git clone https://github.com/PhDP/Randamu.git
    $ mkdir -p Randamu/build && cd $_
    $ cmake ..
    $ make
    $ sudo make install

To launch tests simply add:

    $ make test

after 'make'.

You can generate Visual Studio project files with cmake, which can
be installed with [chocolatey](https://chocolatey.org/), and using the
command

    $ cmake .

at the root of the randamu directory. To run the tests, simply build
the RUN_TESTS project in Visual Studio.

Usage
-----

``` C
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <randamu/xorshift1024.h>

int main(int argc, char **argv) {
  const clock_t start = clock();
  rd_xs1024 r; // A random number generator.
  rd_xs1024_init(&r, time(NULL)); // Initialize with the current time.
  const uint64_t n = argc > 1? atoi(argv[1]) : 100000000;
  printf("Estimating pi with %lu random points.\n", n);
  uint64_t success = 0, i = 0;
  for (; i < n; ++i) {
    // Creates points in the unit square:
    const double x = rd_xs1024_double(&r);
    const double y = rd_xs1024_double(&r);
    // Tests if they are within the unit circle:
    success += (x * x + y * y) < 1.0;
  }
  // Print estimate of pi:
  printf("Pi ~= %f!\n", 4.0 * success / n);
  printf("Time: %.4f seconds.\n", ((double)(clock() - start) / CLOCKS_PER_SEC));
  return EXIT_SUCCESS;
}
```

...will compile with:

    $ gcc -Wall -O3 main.c -o main -lrandamu -lm

The xorshift1024 algorithm is bit less than 30% faster than well1024
and 35% faster than the gsl's mersenne twister (see examples/pi for
code). Plus, unlike the GSL, you don't need to adopt the GPL license...

License
-------
[MIT](http://opensource.org/licenses/MIT)

