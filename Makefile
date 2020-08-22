OBJS=lib/snprintf.o lib/snprintf_utils.o lib/toa.o lib/exit.o lib/setvbuf.o lib/assert.o lib/clock.o
EE_OBJS=$(patsubst %.o,%-ee.o,$(OBJS))
IOP_OBJS=$(patsubst %.o,%-iop.o,$(OBJS))
TEST_OBJS=test/main.o test/snprintf.o test/snprintf_string.o test/snprintf_utils.o test/toa.o

all: libps2_cunit.a ee/libps2_cunit.a iop/libps2_cunit.a iop/libcunit.a

.PHONY: test
test:
	make -C test
	./test/test-bin

.PHONY: clean
clean:
	rm -f *.o */*.o
	rm -f *.a */*.a
	rm -f *.elf */*.elf
	rm -rf CUnit*
	rm -f cunit.tar.gz
	rm -f test-bin test/test-bin

iop/libcunit.a: $(PS2DEV)/iop/lib/libcunit.a $(IOP_OBJS)
	cp $(PS2DEV)/iop/lib/libcunit.a $@
	iop-ar rsu $@ $(IOP_OBJS)

ee/libps2_cunit.a: $(EE_OBJS)
	ee-ar crsu $@ $^

iop/libps2_cunit.a: $(IOP_OBJS)
	iop-ar crsu $@ $^

libps2_cunit.a: $(OBJS)
	ar crsu $@ $^

%.o: %.c
	gcc -I./include -o $@ -c $^

%-ee.o: %.c
	ee-gcc -I $(PS2SDK)/common/include -I $(PS2SDK)/ee/include -I./include -std=c99 -o $@ -c $^

%-iop.o: %.c
	iop-gcc -I $(PS2SDK)/common/include -I $(PS2SDK)/iop/include -I./include -nostdlib -std=c99 -D_IOP -o $@ -c $^
