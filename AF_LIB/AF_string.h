#ifndef _AFSTRING_H
#define _AFSTRING_H

#include "AF_size_t.h"


void itoa(unsigned i, unsigned base, char* buf);


void itoa_s(int i, unsigned base, char* buf);

//! copies string s2 to s1
char *strcpy(char *s1, const char *s2);

//! returns length of string
size_t strlen ( const char* str );

//! copies count bytes from src to dest
void *memcpy(void *dest, const void *src, size_t count);

//! sets count bytes of dest to val
void *memset(void *dest, char val, size_t count);

//! sets count bytes of dest to val
unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);



#endif

