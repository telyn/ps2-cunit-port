#include "toa.h"
#include <math.h>

void reverse(char* str, int len) {
    int i, j, temp;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int ps2_itoa2(int num, char dst[], int digits) {
    int neg = 0;
    int i = 0;
    if(num < 0) {
	num = -num;
	neg = 1;
    }
    while (num > 0 && i < digits) {
        dst[i++] = (num % 10) + '0';
        num /= 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < digits) {
	dst[i++] = '0';
    }
    if(neg) {
	dst[i++] = '-';
    }

    reverse(dst, i);
    dst[i] = '\0';
    return i;
}

int ps2_itoa(int num, char dst[]) {
    int tmp = num;
    int digits = 0;
    if(tmp < 0) {
	tmp = -tmp;
    }
    while (tmp > 0) {
	tmp /= 10;
	digits++;
    }
    if(digits == 0) {
	digits++;
    }
    return ps2_itoa2(num, dst, digits);
}

void ps2_ftoa(double num, char *dst) {
    // printf("ps2_ftoa(%f)\n", num);
    // why 16? felt like it. go away
    int decimal_places = 8;

    int ipart = (int)num;
    double fpart = num - (double)ipart;
    // position in dst
    int i = 0;

    if(ipart < 0) {
	fpart = -fpart;
    } else if(fpart < 0) {
	// there won't be a - if we do itoa!?
	ipart *= -1;
	fpart = -fpart;
	dst[0] = '-';
	i++;
    }

    i += ps2_itoa(ipart, dst + i);
    //printf("  after ipart: dst: %s\n", dst);

    dst[i] = '.'; // add dot

    fpart = fpart * pow(10, decimal_places);

    //printf("  fpart: %f\n", fpart);

    ps2_itoa2((int)fpart, dst + i + 1, decimal_places);
}
