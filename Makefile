define \n


endef

CFLAGS=-g -Wall -std=c11
LDFLAGS=-L. -lcollect

SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

TEST_SOURCES=$(wildcard tests/*_tests.check)
TEST_OBJECTS=$(patsubst %.check, %.o, $(TEST_SOURCES)) \
	$(patsubst %.check, %.c, $(TEST_SOURCES))
TESTS=$(patsubst %.check, %, $(TEST_SOURCES))

.PHONY: all test indent clean docs

all: libcollect.a

libcollect.a: $(OBJECTS)
	ar -rcs $@ $^

test: $(TESTS)
	$(foreach x, $^, ./$(x)${\n})

tests/%_tests.c: tests/%_tests.check
	checkmk $< > $@

tests/%_tests: tests/%_tests.c libcollect.a
	$(CC) $(CFLAGS) `pkg-config --cflags --libs check` -o $@ $< $(LDFLAGS)

docs:
	doxygen docs/Doxyfile

indent:
	find . \( -iname "*.c" -o -iname "*.h" \) -exec astyle --style=linux {} \;

clean:
	rm -f libcollect.a $(OBJECTS) $(TEST_OBJECTS) $(TESTS)
	rm -rf docs/html docs/latex
	rm -f *.orig
