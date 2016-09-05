/*
 * string.h implementation
 *
 * Copyright (C) 2015  Stanislav Gubin
 */
#include <stdlib.h>  //malloc
#include "_string.h"

/* generic memory functions (see details in string.h) */
void *_memset(void *mm, int c, sz_t bc)
{
	register char *m;
	
	for (m = mm; bc--; m++)
		*m = c;
	return mm;
}
void *_memchr(const void *mm, int c, sz_t bc)
{
	register const char *m;
	
	for (m = mm; bc-- ; m++)
		if (*m == c)
			return m;
	return NULL;
}
int _memcmp(const void *mm0, const void *mm1, sz_t bc)
{
	register const uchar *m0, *m1;
	
	for (m0 = mm0, m1 = mm1; bc--; m0++, m1++)
		if (*m0 != *m1)
			return *m0 - *m1;
	return 0;
}
void *_memcpy(void *dst, const void *src, sz_t bc)
{
#define L sizeof(long)
	register char *d;
	register const char *s;
	register sz_t c;
	
	for (d = dst, s = src, c = bc / L; c--; d += L, s += L)
		*(long*)d = *(long*)s;
	for (bc &= L - 1; bc-- ; d++, s++)
		*d = *s;
	return dst;
#undef L
}
void *_memmove(void *dst, const void *src, sz_t bc)
{
#define L sizeof(long)
	register char *d;
	register const char *s;
	register sz_t c;

	d = dst, s = src, c = bc / L;
	if (s < d && s + bc > d) {
		for (s += bc, d += bc; c--; )
			*(long*)(d -= L) = *(long*)(s -= L);
		for (bc &= L - 1; bc--; )
			*--d = *--s;
	}else{
		for (; c--; d += L, s += L)
			*(long*)d = *(long*)s;
		for (bc &= L - 1; bc--; d++, s++)
			*d = *s;
	}
	return dst;
#undef L
}
void *_memccpy(void *dst, const void *src, int c, sz_t bc)
{
	register char *d;
	register const char *s;
	
	for (s = src, d = dst; bc--; s++)
		if ((*d++ = *s) == c)
			return d;
	return NULL;
}
void *_memxswp(void *mm0, void *mm1, sz_t bc)
{
#define L sizeof(long)
	register char *m0, *m1;
	register size_t c;
	
	for (m0 = mm0, m1 = mm1, c = bc / L; c--; m0 += L, m1 += L)
		*(long*)m0 ^= *(long*)m1 ^= *(long*)m0 ^= *(long*)m1;
	for (bc &= L - 1; bc--; m0++, m1++)
		*m0 ^= *m1 ^= *m0 ^= *m1;
	return mm0;
#undef L
}
void *_memswp(void *mm0, void *mm1, sz_t bc)
{
	void *buf;

	buf = malloc(bc);
	if (buf != NULL) {
		_memcpy(buf, mm0, bc);
		_memcpy(mm0, mm1, bc);
		_memcpy(mm1, buf, bc);
		free(buf);
		return mm0;
	}
	return NULL;
}
void *_memdup(const void *mm, sz_t bc)
{
	void *m;

	m = malloc(bc);
	if (m != NULL)
		_memcpy(m, mm, bc);
	return m;
}
  
//string functions (see details in string.h)
//copy/cat
char *_strcpy(char *dst, const char *src)
{
	register char *d;
	
	for (d = dst; *d = *src; d++, src++)
		;
	return dst;
}
char *_strncpy(char *dst, const char *src, sz_t bc)
{
	register char *d;

	d = dst;
	while (bc-- && (*d++ = *src++))
		;
	while (bc--)
		*d++ = '\0';
	return dst;
}
char *_stpcpy(char *dst, const char *src)
{
	while (*dst = *src++)
		dst++;
	return dst;
}
char *_stpncpy(char *dst, const char *src, sz_t bc)
{
	char *d;
	
	do {
		if (!bc--)
			return dst;
	} while (*dst++ = *src++);
	d = dst - 1;
	while (bc--)
		*dst++ = '\0';
	return d;
}
char *_strcat(char *dst, const char *src)
{
	register char *d;

	d = dst;
	while (*d)
		d++;
	while (*d++ = *src++)
		;
	return dst;
}
char *_strncat(char *dst, const char *src, sz_t bc)
{
	register char *d;

	d = dst;
	while (*d)
		d++;
	while (bc-- && (*d = *src++))
		d++;
	*d='\0';
	return dst;
}

//len
sz_t _strlen(const char *str)
{
	register sz_t l;
	
	for (l = 0; *str ; str++, l++)
		;
	return l;
}
sz_t _strnlen(const char *str, sz_t bc)
{
	register sz_t l;
	
	for (l=0; bc-- && *str; str++, l++)
		;
	return l;
}

//find
char *_strchr(const char *str, int c)
{
	for (; *str; str++)
		if (*str == c)
			return str;
	return NULL;
}
char *_strrchr(const char *str, int c)
{
	register sz_t l;
	
	for (l = _strlen(str), str += l - 1; l--; str--)
		if (*str == c)
			return str;
	return NULL;
}
char *_strchrnul(const char *str, int c)
{
	for (; *str && *str!=c; str++)
		;
	return str;
}
sz_t _strcspn(const char *dst, const char *src)
{
	register sz_t l;
	register const char *s;
	
	for (l = 0; *dst; dst++, l++)
		for (s = src; *s; s++)
			if (*s == *dst)
				return l;
	return l;
}
sz_t _strspn(const char *dst, const char *src)
{
	register sz_t l;
	register const char *s;
	
	for (l = 0; *dst; dst++, l++)
		for (s = src; *s; s++)
			if (*s != *dst)
				return l;
	return l;
}
char *_strpbrk(const char *dst, const char *src)
{
	register const char *s;
	
	for (; *dst; dst++)
		for (s = src; *s; s++)
			if (*s == *dst)
				return dst;
	return NULL;
}
/* 
 * only O(N2)
 */
char *_strstr(const char *dst, const char *src)
{
	register const char *base;
	
	while (*dst) {
		for (base = dst; *src && *dst == *src; dst++, src++)
			;
		if (!*src)
			return base;
		src -= dst - base;
		if (*dst != *src)
			dst++;
	}
	return NULL;
}

//compare
int _strcmp(const char *s0, const char *s1)
{
	for (; *s0 == *s1; s0++, s1++)
		if (!*s0)
			return 0;
	return *s0 - *s1;
}
int _strncmp(const char *s0, const char *s1, sz_t bc)
{
	for (; *s0 == *s1 && bc--; s0++, s1++)
		if (!*s0)
			return 0;
	return *s0 - *s1;
}

//reverse
char *_strrev(char *str)
{
	register sz_t l, i;
	register char c;
	
	for (l = _strlen(str), i = 0; i < (l >> 1); i++) {
		c = str[i];
		str[i] = str[l - i - 1];
		str[l - i - 1] = c;
	}
	return str;
}
char *_strnrev(char *str, sz_t bc)
{
	register sz_t l, i;
	register char c;
	
	for (l = _strlen(str), i = 0; i < bc && i < (l >> 1); i++) {
		c = str[i];
		str[i] = str[l - i - 1];
		str[l - i - 1] = c;
	}
	return str;
}

//set each char
char *_strset(char *str, int c)
{
	register char *s;
	
	for (s = str; *s; s++)
		*s = c;
	return str;
}
char *_strnset(char *str, int c, sz_t bc)
{
	register char *s;
	
	for (s = str; bc-- && *str; s++)
		*s = c;
	return str;
}

//alloc
char *_strdup(const char *str)
{
	char *s;

	s = malloc(_strlen(str) + 1);
	if (s != NULL)
		_strcpy(s, str);
	return s;
}
char *_strndup(const char *str, sz_t bc)
{
	register sz_t l;
	char *s;

	l = _strlen(str) + 1;
	if (l > bc)
		l = bc;
	s = malloc(l);
	if (s != NULL)
		_strncpy(s, str, l);
	return s;
}
