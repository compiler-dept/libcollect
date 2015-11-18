LIB=libcollect.a

CFLAGS+=-g -Wall -std=gnu11 -fPIC

SOURCES=array_list.c hashmap.c stack.c deque.c tree.c
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

.PHONY: all test valgrind docs clean style

all: $(LIB)

$(LIB): $(OBJECTS)
	ar -rcs $@ $^

SPECK_CFLAGS=-I.
SPECK_LDFLAGS=-L.
SPECK_LIBS=-lcollect -lm
-include speck/speck.mk

get-speck:
	git submodule init
	git submodule update

test: $(SPECK) $(SUITES)
	@$(SPECK)

valgrind: $(SPECK) $(SUITES)
	@valgrind --leak-check=full --error-exitcode=1 $(SPECK)

docs:
	doxygen docs/Doxyfile

clean:
	rm -f libcollect.a $(OBJECTS)
	rm -f spec/*.o
	rm -f spec/*.so
	rm -rf spec/*.dSYM
	rm -rf docs/html docs/latex

style:
	astyle -A3s4SpHk3jn "*.c" "*.h" "spec/*.c"
