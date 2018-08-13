#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <cilk/cilk.h>
#include "PerfUtils/cycles_wrapper.h"
#include "PerfUtils/perf_wrapper.h"

int64_t fib(int64_t n) {
    if (n < 2) return n;
    int x, y;
    x = cilk_spawn fib(n - 1);
    y = fib(n - 2);
    cilk_sync;
    return x + y;
}
int64_t N, res;
void operation() {
    res = fib(N);
}

int main(int argc, char** argv){
    if (argc > 1) {
        N = atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: Fib <Number>\n");
        exit(1);
    }
    cycles_init();
    Statistics stats = bench(operation, 1000);
    printf("Computed fib %ld to be %ld\n", N, res);
    stats = transformStatistics(stats, cycles_to_microseconds);
    printStatistics(stats, "Fib_Cilk");
}
