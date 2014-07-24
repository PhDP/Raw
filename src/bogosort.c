#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bogosort.h"
#include "compar.h"
#include "rng.h"

size_t bogosort(void *base, size_t nmemb, size_t size,
                int (*cmp)(const void *, const void *), unsigned int seed) {
    well rng;
    well_init(&rng, seed);
    size_t attempts = 0;
    while (!sorted(base, nmemb, size, cmp)) {
        ++attempts;
        knuth_shuffle(base, nmemb, size, &rng);
    }
    return attempts;
}

size_t bogosort_noseed(void *base, size_t nmemb, size_t size,
                       int (*cmp)(const void *, const void *)) {
    return bogosort(base, nmemb, size, cmp, time_seed());
}
