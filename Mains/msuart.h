
#ifndef MSUART_H
#define MSUART_H

void msuart_init(void);
int msuart_putc(char c);
int msuart_getc(void);
int msuart_puts(const char *s);

#endif

