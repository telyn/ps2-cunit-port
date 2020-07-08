#include <stdarg.h>
#include <string.h>
#include "snprintf.h"
#include "snprintf_utils.h"


// this is not intended to be a complete implementation of snprintf - it is only
// intended to be enough to get CUnit's basic formatter to work.
// For that, it needs to understand four format specifiers: %s, %*s, %d, %u
// TODO: rewrite in terms of format_snpf_str
// TODO: split into one-function-per-state
// TODO: see if we can inline all those functions?
int _ps2_cunit_snprintf (char * dst, size_t n, const char *format, ... ) {
	va_list args;
	va_start(args, format);

	int pos = 0;
	int dpos = 0;
	enum snpf_state_label state = PS2SNPF_STATE_DEFAULT;

	struct snpf_format format_spec;
	reset_snpf_format(&format_spec);

	while(format[pos] != '\0') {
		char chr = format[pos];
		switch(state) {
			case PS2SNPF_STATE_DEFAULT:
				switch(chr) {
					case '%':
						state = PS2SNPF_STATE_FMT_ALIGN;
						break;
					default:
						if(dpos < n) {
							dst[dpos] = chr;
						}
						dpos++;
						break;
				}
				break;

			case PS2SNPF_STATE_FMT_ALIGN:
			case PS2SNPF_STATE_FMT_WIDTH:
				if ((chr >= 'a' && chr <= 'z') ||
						(chr >= 'A' && chr <= 'Z')) {
					switch(chr) {
						case 's':
						case 'S':
							{
							}
							break;
						case 'd':
						case 'D':
							break;
						case 'u':
						case 'U':
							break;
					}
					reset_snpf_format(&format_spec);
					state = PS2SNPF_STATE_DEFAULT;
				} else if (chr >= '0' && chr <= '9') {
					format_spec.width *= 10;
					format_spec.width += chr;
				} else if (chr == '-') {
					format_spec.align = PS2SNPF_LEFT;
				} else if (chr == '*') {
					format_spec.width = va_arg(args, int);
				} else if (chr == '%') {
					dst[dpos++] = chr;
					state = PS2SNPF_STATE_DEFAULT;
				}
				break;
			case PS2SNPF_STATE_FMT_PRECISION:
				break;
		}
		pos++;
	}
	dst[n] = '\0';
	va_end(args);
	return dpos+1;
}

//vi:set tabstop=4
