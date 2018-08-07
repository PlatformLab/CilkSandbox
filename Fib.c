#include <cilk/cilk.h>
#include <stdio.h>
#include <stdint.h>

int64_t fib(int64_t n) {
    if (n < 2) return n;
    int x, y;
    x = cilk_spawn fib(n - 1);
    y = fib(n - 2);
    cilk_sync;
    return x + y;
}

int main(){
   printf("%ld\n", fib(20));
}
