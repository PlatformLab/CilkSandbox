CC = clang-5.0

# Output binaries
BINS=Fib FibSerial
# Dependencies
PERFUTILS=../PerfUtils
LIBS=-I$(PERFUTILS)/include $(PERFUTILS)/lib/libPerfUtils.a

all: $(BINS)

# Cilk Programs
Fib: Fib.c
	$(CC) -fcilkplus $< $(LIBS) -o $@

# Non-Cilk Programs
FibSerial: FibSerial.c
	$(CC)  $< $(LIBS) -o $@

clean:
	rm -rf $(BINS)
