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
void *_bsearch(const void *key, const void *mm, sz_t n, sz_t size,
	       int (*cmp)(const void *, const void *))
{
	register sz_t low, high, mid;
	register int cm;
	register void *cur;
	
	for (low = 0, high = n - 1; low <= high; ) {
		mid = (low + high) >> 1;
		cur = (char *)mm + mid * size;
		cm = cmp(cur, key);
		if (cm < 0)
			low = mid + 1;
		else if (cm > 0)
			high = mid - 1;
		else
			return cur;
	}
	return NULL;
}

//sort
void _qsort(void *mm, sz_t n, sz_t sz, int (*cmp)(const void *, const void *))
{
	if (n <= 1)
		return;
	register char *cur, *top, *end;
	_memswp(mm, (char *)mm + rand() % n * sz, sz);
	for (top = mm, cur = top + sz, end = top + sz * n; cur != end; cur += sz)
		if (cmp(cur, mm) < 0)
			_memswp(cur, top += sz, sz);
	_memswp(mm, top, sz);
	_qsort(mm, (top - (char*)mm) / sz, sz, cmp);
	_qsort(top + sz, (end - top) / sz - 1, sz, cmp);
}
