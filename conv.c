#include "ntlang.h"

void convert_error(char *err) {
    printf("convert_error: %s\n", err);
    exit(-1);
}

uint32_t convert_char_to_uint32_digit(char ch) {
    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    } else if (ch >= 'a' && ch <= 'f') {
        return ch - 'a' + 10;
    } else if (ch >= 'A' && ch <= 'F') {
        return ch - 'A' + 10;
    } else {
       convert_error("Invalid character in conversion");
    }
}


uint32_t convert_string_to_uint32(char *str, int base) {
	uint32_t result = 0;
	char *p = str;
	uint32_t max_value = UINT32_MAX;
	while(*p != '\0') {
		int digit = convert_char_to_uint32_digit(*p);
		if(result > (max_value - digit) / base) {
			printf("overflows uint32_t: %s", str);
			exit(-1);	
		} 
		result = result * base + digit;
	    p++;
	}

	return result;
}

char convert_uint32_digit_to_char(uint32_t digit) {
    if (digit < 10) {
    	return '0' + digit;
   	} else if (digit>9 && digit<17) {
   		return 'A' + digit - 10;
   	} else {
       convert_error("Invalid character in conversion");
    }
}
