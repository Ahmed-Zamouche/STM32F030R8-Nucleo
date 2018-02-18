
#include "msuart.h"

#include <stdio.h>

#include "console.h"

int msuart_putc(char c) {
	Console_Status_t status = Console_Putc(CONSOLE_1, c);
	return (status == CONSOLE_STATUS_OK) ? c : -1;
}

int msuart_getc(void) {
	char ch;
	Console_Status_t status = Console_Getc(CONSOLE_1, &ch);
	return (status == CONSOLE_STATUS_OK) ? ch : -1;
}

int msuart_puts(const char *s) {
	Console_Status_t status = Console_Puts(CONSOLE_1, s);
	return (status == CONSOLE_STATUS_OK) ? 0 : -1;
}

void msuart_init(void) {

}
