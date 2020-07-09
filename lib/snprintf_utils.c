#include <string.h>
#include <stdio.h>
#include "snprintf_utils.h"

void reset_snpf_format(struct snpf_format *fmt) {
	fmt->width = -1;
	fmt->precision = -1;
	fmt->align = PS2SNPF_RIGHT;
	fmt->padding = ' ';
}

// inputs a maximum of `width` padding characters into the string described by
// dst and dstlen. Increments dstc by width.
// TODO: could be better optimised, but since I'm only intending to use this in CUnit it probably isn't an issue.
char *snpf_pad_str(char *dst, char padding, int width, int *dstc, int dstlen) {
	int i;
	for(i = 0; i < width; i++) {
		if((*dstc)++ >= dstlen) {
			continue;
		}
		*(dst++) = padding;
	}
	return dst;
}

// inserts src at the current position of dst in the manner indicated by fmt.
// dstlen is max number of chars we can write to dst.
// returns length of the string that would be inserted if all characters could be (e.g. %20.5s -> returns 20)
// TODO: test me
int format_snpf_str(char *dst, int dstlen, const struct snpf_format * const fmt, char * src) {
	int len = strlen(src);
	if (fmt->precision < len && fmt->precision != -1) {
		len = fmt->precision;
	}
	//count of characters written into dst - also used for return value
	int dstc = 0;

	if (fmt->align == PS2SNPF_RIGHT && fmt->width != -1) {
		// printf("snpf_pad_str(%s, %c, %d, %d, %d)\n", dst, fmt->padding, fmt->width - len, dstc, dstlen);
		dst = snpf_pad_str(dst, fmt->padding, fmt->width - len, &dstc, dstlen);
	}
	// actual string insertion!
	int cpyn = len;
	if ((dstlen - dstc) < cpyn) {
		cpyn = dstlen - dstc;
	}
	if (cpyn < 0) {
		cpyn = 0;
	}

	strncpy(dst, src, cpyn);
	dstc += len;
	dst += len;

	// right padding
	if (fmt->align == PS2SNPF_LEFT && fmt->width != -1) {
		dst = snpf_pad_str(dst, fmt->padding, fmt->width - len, &dstc, dstlen);
	}
	return dstc;
}

int read_number(const char **src) {
	int num = 0;
	while(**src >= '0' && **src <= '9') {
		num = num * 10 + (**src - '0');
		(*src)++;
	}
	return num;
}
