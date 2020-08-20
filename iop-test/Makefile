include $(PS2SDK)/Defs.make

TEST_BINS = local-test ee-test.elf iop-test.elf
TEST_OBJS = iop-test.o iop-imports.o
IOP_TEST_OBJS = $(patsubst %.o, %-iop.o, $(TEST_OBJS))

IOP_INCS = $(COMMON_INCS) -I. -I$(PS2DEV)/iop/include -I$(PS2SDK)/common/include -I$(PS2SDK)/iop/include

IOP_CFLAGS = -std=c99 -D_IOP -include ../../ps2-cunit-port/include/cunit-overrides.h
IOP_LDFLAGS = -L$(PS2SDK)/../iop/lib -static -nostdlib

run-all: test test-iop

all: $(TEST_BINS)

# runs test on host
test: local-test
	./$<

clean:
	rm -f $(TEST_OBJS) $(EE_TEST_OBJS) $(IOP_TEST_OBJS)

# not yet set up properly. I *think* that iop cunit tests will be visible via
# ps2link
test-iop: iop-test.elf

local-test: $(TEST_OBJS)
	$(CC) $(LDFLAGS) -lcunit $^ -o $@

iop-test.elf: $(IOP_TEST_OBJS) $(PS2DEV)/iop/lib/libcunit.a
	$(IOP_CC) $(IOP_LDFLAGS) $^ -lcunit -lgcc -o $@

%-iop.o: %.c
	$(IOP_CC) $(IOP_INCS) $(IOP_CFLAGS) -c $^ -o $@

%.o: %.c
	$(CC) $(COMMON_INCS) $(CFLAGS) -c $^ -o $@
