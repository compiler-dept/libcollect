LIB=libcollect.a

CFLAGS+=-g -Wall -std=gnu99

SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

.PHONY: all test valgrind docsm clean

all: $(LIB)

$(LIB): $(OBJECTS)
	ar -rcs $@ $^

TEST_SOURCES=$(wildcard tests/*.c)
tests/testsuite: $(LIB)
	tests/generate.py tests
	$(CC) $(CFLAGS) -I. -L. -Wno-unused-function -o $@ $(TEST_SOURCES) -lcollect -lm

test: tests/testsuite
	tests/testsuite

valgrind: tests/testsuite
	valgrind --leak-check=full --error-exitcode=1 --suppressions=tests/valgrind.supp tests/testsuite

docs:
	doxygen docs/Doxyfile

clean:
	rm -f libcollect.a $(OBJECTS)
	rm -f tests/testsuite tests/.clarcache tests/clar.suite
	rm -rf docs/html docs/latex
