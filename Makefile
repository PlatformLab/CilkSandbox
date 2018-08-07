CC = clang-5.0

# Output binaries
BINS=Fib FibSerial knary knarySerial
# Dependencies
PERFUTILS=../PerfUtils
LIBS=-I$(PERFUTILS)/include $(PERFUTILS)/lib/libPerfUtils.a

all: $(BINS)

% : %.c
	$(CC) -fcilkplus -O2 $< $(LIBS) -o $@

clean:
	rm -rf $(BINS)
