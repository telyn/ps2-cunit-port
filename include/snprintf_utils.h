#ifndef SNPRINTF_UTILS_H
#define SNPRINTF_UTILS_H
#include <stdarg.h>

enum snpf_state_label {
	PS2SNPFS_NORMAL,
	PS2SNPFS_FMT_START,
	PS2SNPFS_FMT_ALIGN,
	PS2SNPFS_FMT_WIDTH,
	PS2SNPFS_FMT_PRECISION,
	PS2SNPFS_FMT_TYPE
};

enum snpf_align { PS2SNPF_RIGHT, PS2SNPF_LEFT };

struct snpf_format {
	int width;
	int precision;
	// character to use as padding. defaults to ' '.
	char padding;
	enum snpf_align align;
};

struct snpf_state {
	enum snpf_state_label label;
	va_list *values;
	struct snpf_format fmt;
	int dstlen;
	int bytes_written;
	char *dst;
	const char *src;
	const char * const orig;
};

void reset_snpf_format(struct snpf_format *fmt);
char *snpf_pad_str(char *dst, char padding, int width, int *dstc, int dstlen);
int format_snpf_str(char *dst, int dstlen, const struct snpf_format * const fmt, char * src);
int read_number(const char **src);

#endif
