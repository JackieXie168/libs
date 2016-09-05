/*
 * string.h
 *
 * Copyright (C) 2015  Stanislav Gubin
 */
#ifndef __STRING_H
#define __STRING_H

#include "_stddef.h"

/*
 * generic memory functions
 *  
 * short description:
 * - memdup/memswp/memxswp are not ANSI;
 * - memdup is dynamic allocator;
 * - memswp swaps using temp buffer;
 * - memxswp swaps using XOR.
 */
void *_memset(void *mm, int c, sz_t bc);
void *_memchr(const void *mm, int c, sz_t bc);
int _memcmp(const void *mm0, const void *mm1, sz_t bc);
void *_memcpy(void *dst, const void *src, sz_t bc);
void *_memmove(void *dst, const void *src, sz_t bc);
void *_memccpy(void *dst, const void *src, int c, sz_t bc);
void *_memdup(const void *mm, sz_t bc);
void *_memswp(void *mm0, void *mm1, sz_t bc);
void *_memxswp(void *mm0, void *mm1, sz_t bc);

/*
 * string functions
 *
 * NB: no memory allocation except strdup/strndup
 */
/* copy/cat */
char *_strcpy(char *dst, const char *src);
char *_strncpy(char *dst, const char *src, sz_t bc);
char *_strcat(char *dst, const char *src);
char *_strncat(char *dst, const char *src, sz_t bc);
char *_stpcpy(char *dst, const char *src);
char *_stpncpy(char *dst, const char *src, sz_t bc);

/* length */
sz_t _strlen(const char *str);
sz_t _strnlen(const char *str, sz_t bc);

/* find bytes/substrings */
char *_strchr(const char *str, int c);
char *_strrchr(const char *str, int c);
char *_strchrnul(const char *str, int c);
sz_t _strcspn(const char *dst, const char *src);
sz_t _strspn(const char *dst, const char *src);
char *_strpbrk(const char *dst, const char *src);
char *_strstr(const char *dst, const char *src);

/* compare */
int _strcmp(const char *s0, const char *s1);
int _strncmp(const char *s0, const char *s1, sz_t bc);

/* reverse */
char *_strrev(char *str);
char *_strnrev(char *str, sz_t bc);

/* set each char */
char *_strset(char *str, int c);
char *_strnset(char *str, int c, sz_t bc);

/* alloc */
char *_strdup(const char *str);
char *_strndup(const char *str, sz_t bc);

#endif
