<p align='center'>
  <img src='http://phdp.github.io/images/randamu.png' alt='Randamu logo'/>
</p>

randamu is a small C library that includes a high-quality random number
generator, plus a few probabilistic data-structures, functions for statistics
and handling probabilities.

The bogosort random algorithm is a joke (don't use it!), but everything else is
not. The bloom filter (a probabilistic data structure), is arguably one of the
most original and useful data structure.

Installing
----------
On Linux or UNIX-like systems:

    $ cmake .
    $ make
    $ sudo make install

Usage
-----

    // random.c
    #include <stdlib.h>
    #include <stdio.h>
    #include <randamu/rng.h>

    int main() {
      // Creates a random number generator:
      rd_rng r;
      // Initialize it with the current time:
      rd_rng_init_time(&r);

      printf("Yeee, random numbers!\n");
      for (int i = 0; i < 42; ++i) {
        // Generates double-precision numbers in the [0, 1) range:
        printf("%f\n", rd_rng_double(&r));
      }
      return EXIT_SUCCESS;
    }

...will compile with:

    $ clang -Wall -std=c99 -O2 random.c -o random -lrandamu -lm

Of course 'gcc' or another compiler can be used.

License
-------
MIT <http://opensource.org/licenses/MIT>

