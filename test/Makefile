include $(PS2SDK)/Defs.make

TEST_BINS = local-test ee-test.elf iop-test.elf
TEST_OBJS = main.o snprintf.o snprintf_string.o snprintf_utils.o toa.o
IOP_TEST_OBJS = $(patsubst %.o, %-iop.o, $(TEST_OBJS)) irx-imports-iop.o
EE_TEST_OBJS = $(patsubst %.o, %-ee.o, $(TEST_OBJS))

COMMON_INCS = -I ../include
INCS = $(COMMON_INCS)
EE_INCS = $(COMMON_INCS)  -I. -I$(PS2DEV)/ee/include -I$(PS2SDK)/common/include -I$(PS2SDK)/ee/include
IOP_INCS = $(COMMON_INCS) -I. -I$(PS2DEV)/iop/include -I$(PS2SDK)/common/include -I$(PS2SDK)/iop/include

CC=gcc
CFLAGS = -std=c99
EE_CFLAGS = -std=c99
IOP_CFLAGS = -std=c99 -D_IOP -include ../include/iop-cunit-overrides.h
LDFLAGS = -L..
EE_LDFLAGS = -L../ee -L$(PS2DEV)/ee/lib -static
IOP_LDFLAGS = -L../iop -static -nostdlib

all: $(TEST_BINS)

# runs test on host
test: local-test
	./$<

clean:
	rm -f *.o *.elf $(TEST_BINS)

test-iop: iop-test.elf

local-test: $(TEST_OBJS)
	$(CC) $(LDFLAGS) -lps2_cunit -lcunit $^ -o $@

ee-test.elf: $(EE_TEST_OBJS)
	$(EE_CC) $(EE_LDFLAGS) $^ -lps2_cunit -lcunit -o $@

iop-test.elf: $(IOP_TEST_OBJS) $(PS2DEV)/iop/lib/libcunit.a
	$(IOP_CC) $(IOP_LDFLAGS) $^ -lcunit -lgcc -o $@

%-ee.o: %.c
	$(EE_CC) $(EE_INCS) $(EE_CFLAGS) -c $^ -o $@

%-iop.o: %.c
	$(IOP_CC) $(IOP_INCS) $(IOP_CFLAGS) -c $^ -o $@

%.o: %.c
	$(CC) $(COMMON_INCS) $(CFLAGS) -c $^ -o $@
