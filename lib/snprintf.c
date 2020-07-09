#include <string.h>
#include "snprintf.h"
#include "snprintf_utils.h"

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
	}
	state->label = PS2SNPFS_FMT_WIDTH;
}

void _ps2snpf_read_fmt_width(struct snpf_state *state) {
	if(*state->src < '0' || *state->src > '9') {
		state->label = PS2SNPFS_FMT_PRECISION;
		return;
	}

	read_number(&state->src);
	state->label = PS2SNPFS_FMT_PRECISION;
}

void _ps2snpf_read_fmt_precision(struct snpf_state *state) {

}

void _ps2snpf_read_fmt_type(struct snpf_state *state) {

}

//vi:set tabstop=4
