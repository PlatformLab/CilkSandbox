all: Fib FibSerial

# Cilk Programs
Fib: Fib.c
	clang-5.0 -fcilkplus $< -o $@

# Non-Cilk Programs
FibSerial: FibSerial.c
	clang-5.0  $< -o $@
