OBJS=lib/snprintf.o lib/snprintf_utils.o lib/toa.o
TEST_OBJS=test/main.o test/snprintf.o test/snprintf_string.o test/snprintf_utils.o test/toa.o

all: $(OBJS)

.PHONY: test
test: test-bin
	./test-bin

test-bin: $(TEST_OBJS) $(OBJS)
	gcc -lcunit -o $@ $^

%.o: %.c
	gcc -I./include -o $@ -c $^
