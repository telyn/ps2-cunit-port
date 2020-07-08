#ifndef SNPRINTF_UTILS_H
#define SNPRINTF_UTILS_H

enum snpf_state_label { PS2SNPF_STATE_DEFAULT, PS2SNPF_STATE_FMT_ALIGN, PS2SNPF_STATE_FMT_WIDTH, PS2SNPF_STATE_FMT_PRECISION };
enum snpf_align { PS2SNPF_RIGHT, PS2SNPF_LEFT };
struct snpf_format {
	int width;
	int precision;
	// character to use as padding. defaults to ' '.
	char padding;
	enum snpf_align align;
};

struct snpf_state {
	struct snpf_format fmt;
	int dstlen;
	int bytes_written;
	char *dst;
	char *src;
};

void reset_snpf_format(struct snpf_format *fmt);
char *snpf_pad_str(char *dst, char padding, int width, int *dstc, int dstlen);
int format_snpf_str(char *dst, int dstlen, struct snpf_format *fmt, char *src);

#endif
