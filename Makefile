CC = clang-5.0

# Output binaries
BINS=Fib FibSerial knary knarySerial
# Dependencies
PERFUTILS=../PerfUtils
LIBS=$(PERFUTILS)/lib/libPerfUtils.a
INCLUDE=-I$(PERFUTILS)/include

all: $(BINS)

% : %.c
	$(CC) -c  -fcilkplus -O2 $< $(INCLUDE) -o $@.o
	clang++ -fcilkplus -o $@ $@.o $(LIBS)  -lm

clean:
	rm -rf $(BINS) *.o
