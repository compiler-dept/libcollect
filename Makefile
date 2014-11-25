override CFLAGS+=-g -Wall -std=gnu99
override LDFLAGS+=-L. -lcollect -lm

SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

.PHONY: all test indent clean docs

all: libcollect.a

libcollect.a: $(OBJECTS)
	ar -rcs $@ $^

test: tests/testsuite
	tests/testsuite

tests/testsuite: tests/testsuite.c libcollect.a
	$(CC) $(CFLAGS) $< $(LDFLAGS) -lcunit -o $@

docs:
	doxygen docs/Doxyfile

indent:
	find . \( -iname "*.c" -o -iname "*.h" \) -exec astyle --style=linux {} \;

clean:
	rm -f libcollect.a $(OBJECTS) tests/testsuite
	rm -rf docs/html docs/latex
	rm -f *.orig
