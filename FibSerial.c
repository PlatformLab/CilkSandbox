#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <cilk/cilk.h>

int64_t fib(int64_t n) {
    if (n < 2) return n;
    int x, y;
    x = fib(n - 1);
    y = fib(n - 2);
    return x + y;
}

int main(int argc, char** argv){
    if (argc > 1) {
        printf("%ld\n", fib(atoi(argv[1])));
    } else {
        fprintf(stderr, "Usage: Fib <Number>\n");
    }
}
