#include "ascii.h"

int ascii_write_char(char* str, int x, int y, uint32_t color)
{
}

void ascii_write(char* str, int x, int y, uint32_t color)
{
	while (*str)
	{
		x += ascii_write_char(*str++, x, y, color);
	}
}
