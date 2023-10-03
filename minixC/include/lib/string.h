#ifndef __JOS_LIB_STRING_H__
#define __JOS_LIB_STRING_H__

#include <lib/types.h>

void itoa(uint64_t n, char *s, int b);
size_t strlen(const char *str);
int strcmp(const char *s1, const char *s2);

#endif
