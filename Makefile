LIB=libcollect.a

CFLAGS+=-g -Wall -std=gnu11 -fPIC

SOURCES=array_list.c hashmap.c stack.c tree.c
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

.PHONY: all test valgrind docs clean style

all: $(LIB)

$(LIB): $(OBJECTS)
	ar -rcs $@ $^

TESTS=$(patsubst %.c, %.so, $(wildcard spec/*.c))

spec/%.so: spec/%.c
	@$(CC) -g -std=gnu11 -fPIC -shared -L. -o $@ $< -lcollect -lm

speck: $(LIB)
	$(CC) -g -std=gnu11 -o speck speck.c -ldl

test: speck $(TESTS)
	@./speck

valgrind: speck $(TESTS)
	@valgrind --leak-check=full --error-exitcode=1 ./speck

docs:
	doxygen docs/Doxyfile

clean:
	rm -f libcollect.a $(OBJECTS)
	rm -f speck
	rm -rf speck.dSYM
	rm -f spec/*.o
	rm -f spec/*.so
	rm -rf spec/*.dSYM
	rm -rf docs/html docs/latex

style:
	astyle -A3s4SpHk3jn "*.c" "*.h"
