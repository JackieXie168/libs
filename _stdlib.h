#ifndef __STDLIB_H
#define __STDLIB_H

#include "_stddef.h"

void *_lsearch(const void *key, const void *mm, sz_t  n, sz_t size,
	       int (*cmp)(const void *, const void *));
void *_bsearch(const void *key, const void *mm, sz_t n, sz_t size,
	       int (*cmp)(const void *, const void *));
void _qsort(void *mm, sz_t n, sz_t size,
	    int (*cmp)(const void *, const void *));

#endif
