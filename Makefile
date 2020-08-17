OBJS=lib/snprintf.o lib/snprintf_utils.o lib/toa.o lib/exit.o lib/setvbuf.o lib/assert.o
IOP_OBJS=lib/snprintf-iop.o lib/snprintf_utils-iop.o lib/toa-iop.o lib/exit-iop.o lib/setvbuf-iop.o lib/assert-iop.o
TEST_OBJS=test/main.o test/snprintf.o test/snprintf_string.o test/snprintf_utils.o test/toa.o

all: $(OBJS)

.PHONY: test
test: test-bin
	./test-bin

test-bin: $(TEST_OBJS) $(OBJS)
	gcc -lcunit -o $@ $^

libps2_cunit.a: $(IOP_OBJS)
	iop-ar cru $@ $^
	iop-ranlib $@

%.o: %.c
	gcc -I./include -o $@ -c $^

%-iop.o: %.c
	iop-gcc -I $(PS2SDK)/common/include -I $(PS2SDK)/iop/include -I./include -nostdlib -std=c99 -D_IOP -o $@ -c $^
