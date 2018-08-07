#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <cilk/cilk.h>
#include "PerfUtils/cycles_wrapper.h"


int performWork() {
    // Prevent compiler from removing loops.
    int sum = 0;

    // Actual work
    for (int j = 0; j < 400; j++) {
        sum += j*10;
    }
    return sum;
}

void knary(int k, int n, int r) {
    if (n == 0) return;

    // Do the work for this node.
    performWork();

    // Execute the first r in serial.
    for (int i = 0; i < r; i++) {
        knary(k, n - 1, r);
    }

    // Execute the remainder in parallel
    for (int i = r; i < k; i++) {
        knary(k, n - 1, r);
    }
}

int main(int argc, char** argv){
    int k,n,r;
    if (argc > 3) {
        k = atoi(argv[1]);
        n = atoi(argv[2]);
        r = atoi(argv[3]);
    } else {
        fprintf(stderr, "Usage: knary <k> <n> <r>\n");
        exit(1);
    }
    cycles_init();

    uint64_t startCycles = cycles_rdtsc();
    knary(k, n, r);
    uint64_t stopCycles = cycles_rdtsc();
    printf("Computed knary(%d,%d,%d) in %lu us\n", k,n,r, cycles_to_microseconds(stopCycles - startCycles));
}
