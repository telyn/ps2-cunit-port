#include <string.h>
#include <stdio.h>
#include "snprintf.h"
#include "snprintf_utils.h"
#include "toa.h"

void _ps2snpf_read_normal(struct snpf_state *state);
void _ps2snpf_read_fmt_start(struct snpf_state *state);
void _ps2snpf_read_fmt_align(struct snpf_state *state);
void _ps2snpf_read_fmt_width(struct snpf_state *state);
void _ps2snpf_read_fmt_precision(struct snpf_state *state);
void _ps2snpf_read_fmt_type(struct snpf_state *state);


// this is not intended to be a complete implementation of snprintf - it is only
// intended to be enough to get CUnit's basic formatter to work.
// For that, it needs to understand four format specifiers: %s, %*s, %d, %u
// TODO: rewrite in terms of format_snpf_str
// TODO: split into one-function-per-state
// TODO: see if we can inline all those functions?
int _ps2_cunit_snprintf (char * dst, size_t dstlen, const char *format, ... ) {
	va_list args;
	va_start(args, format);

	struct snpf_state state = {
		.dstlen = dstlen,
		.bytes_written = 0,
		.dst = dst,
		.src = format,
		.values = &args
	};
	reset_snpf_format(&state.fmt);

	while(*state.src != '\0') {
		switch(state.label) {
			case PS2SNPFS_NORMAL:
				_ps2snpf_read_normal(&state);
				break;
			case PS2SNPFS_FMT_START:
				_ps2snpf_read_fmt_start(&state);
				break;
			case PS2SNPFS_FMT_ALIGN:
				_ps2snpf_read_fmt_align(&state);
				break;
			case PS2SNPFS_FMT_WIDTH:
				_ps2snpf_read_fmt_width(&state);
				break;
			case PS2SNPFS_FMT_PRECISION:
				_ps2snpf_read_fmt_precision(&state);
				break;
			case PS2SNPFS_FMT_TYPE:
				_ps2snpf_read_fmt_type(&state);
				break;
		}
	}

	va_end(args);
	return state.bytes_written;
}

void _ps2snpf_write_char(struct snpf_state *state, char chr) {
	if(state->bytes_written < state->dstlen) {
		*state->dst = *state->src;
	}
	state->dst++;
	state->bytes_written++;
}

void _ps2snpf_read_normal(struct snpf_state *state) {
	while(*state->src != '%' && *state->src != '\0') {
		_ps2snpf_write_char(state, *state->src);
		state->src++;
	}
	if(*state->src == '%') {
		state->label = PS2SNPFS_FMT_START;
	}
}

void _ps2snpf_read_fmt_start(struct snpf_state *state) {
	if(*state->src != '%') {
		return;
	}
	state->src++;

	if(*state->src == '%') {
		_ps2snpf_write_char(state, '%');
		state->label = PS2SNPFS_NORMAL;
		return;
	}

	state->label = PS2SNPFS_FMT_ALIGN;
}

void _ps2snpf_read_fmt_align(struct snpf_state *state) {
	if(*state->src == '-') {
		state->fmt.align = PS2SNPF_LEFT;
		state->src++;
	}
	state->label = PS2SNPFS_FMT_WIDTH;
}

void _ps2snpf_read_fmt_width(struct snpf_state *state) {
	if(*state->src == '*') {
		state->fmt.width = va_arg(*state->values, int);
		state->src++;
	} else {
		state->fmt.width = read_number(&state->src);
	}
	state->label = PS2SNPFS_FMT_PRECISION;
}

void _ps2snpf_read_fmt_precision(struct snpf_state *state) {
	if(*state->src != '.') {
		state->label = PS2SNPFS_FMT_TYPE;
		return;
	}
	state->src++;
	if(*state->src == '*') {
		state->fmt.precision = va_arg(*state->values, int);
		state->src++;
	} else {
		state->fmt.precision = read_number(&state->src);
	}
	state->label = PS2SNPFS_FMT_TYPE;
}

void _ps2snpf_read_fmt_type(struct snpf_state *state) {
	char *tmp;
	char buf[32] = { '\0' };
	switch(*state->src++) {
		case 'd':
			{
				int i = va_arg(*state->values, int);
				if(state->fmt.precision == 0 && i == 0) {
					tmp = buf;
					break;
				}
				ps2_itoa(i, buf);
				tmp = buf;
				break;
			}
		case 'f':
			{
				ps2_ftoa(va_arg(*state->values, double), buf);
				tmp = buf;
				break;
			}
		case 's':
			{
				tmp = va_arg(*state->values, char *);
				break;
			}
		default:
			printf("Unexpected char %c at position %ld - pretending none of this ever happened", *state->src, state->src - state->orig);
			return;
	}
	int change = format_snpf_str(state->dst,
			                     state->dstlen,
			                     &state->fmt, tmp);
	state->dst += change;
	state->bytes_written += change;
	reset_snpf_format(&state->fmt);
	state->label = PS2SNPFS_NORMAL;
}

//vi:set tabstop=4
