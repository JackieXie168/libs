#include <stdlib.h>  //rand()
#include "_stdlib.h" 
#include "_string.h" //memswp()

//search
void *_lsearch(const void *key, const void *mm, sz_t n, sz_t size,
	       int (*cmp)(const void *,const void *))
{
	for (; n--; mm = (char *)mm + size)
		if (!cmp(mm, key))
			return mm;
	return NULL;
}

//sort
void _qsort(void *mm, sz_t n, sz_t sz, int (*cmp)(const void *, const void *))
{
	register char *cur, *top, *end;

	if (n <= 1)
		return;
	_memswp(mm, (char *)mm + rand() % n * sz, sz);
	for (top = mm, cur = top + sz, end = top + sz * n; cur != end; cur += sz)
		if (cmp(cur, mm) < 0)
			_memswp(cur, top += sz, sz);
	_memswp(mm, top, sz);
	_qsort(mm, (top - (char*)mm) / sz, sz, cmp);
	_qsort(top + sz, (end - top) / sz - 1, sz, cmp);
}

void *bsearch(const void *key, const void *mm, sz_t n, sz_t bc, int (*cmp)(const void *, const void *))
{
	register sz_t l, h, m;
	register int c;

	/* ... */
	for (l = 0, h = n - 1; l < h; ) {
		m = (l + h) >> 1;
		c = (*cmp)((char *)mm + m * bc, key);
		if (c >= 0)
			h = m;
		else
			l = m + 1;
	}
	/* ... */
	cur = (char *)mm + h * bc;
	return !(*cmp)(cur, key) ? cur : NULL;
}	
