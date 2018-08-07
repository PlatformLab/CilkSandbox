#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <cilk/cilk.h>
#include "PerfUtils/cycles_wrapper.h"

int64_t fib(int64_t n) {
    if (n < 2) return n;
    int x, y;
    x = cilk_spawn fib(n - 1);
    y = fib(n - 2);
    cilk_sync;
    return x + y;
}

int main(int argc, char** argv){
    int64_t N, res;
    if (argc > 1) {
        N = atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: Fib <Number>\n");
        exit(1);
    }
    cycles_init();

    uint64_t startCycles = cycles_rdtsc();
    res = fib(N);
    uint64_t stopCycles = cycles_rdtsc();
    printf("Computed fib %ld to be %ld in %lu us\n", N, res, cycles_to_microseconds(stopCycles - startCycles));
}
