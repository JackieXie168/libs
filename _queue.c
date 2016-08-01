#include <stdlib.h>
#include "_stddef.h"
#include "_string.h"
#include "_queue.h"

//alloc/dealloc
int mk_qu(struct queue *q, unsigned int cnt)
{
	sz_t bc = cnt * q->off;
	q->base = malloc(bc);
	if (q->base != NULL) {
		q->head = q->tail = q->base;
		q->end = (char *)q->head + bc;
		return 0;
	}
	return -1;
}
void rm_qu(struct queue *q)
{
	free(q->base);
	q->head = q->tail = q->end = q->base = NULL;
}

//add
int push_qu(struct queue *q, void *data)
{
	if (q->tail == q->end) {
		if (q->head != q->base)
			q->tail = q->base;
		else{
			sz_t bc, tc;
			tc = (char *)q->tail - (char *)q->base;
			bc = tc * q->rc;
			char *newb = realloc(q->base, bc);
			if (newb == NULL)
				return -1;
			q->tail = newb + tc;
			q->end = newb + bc;
			q->head = q->base = newb;
		}
	} else if (q->head == q->tail && q->head != q->base) {
		sz_t bh, he, be, bc;
		bh = (char *)q->head - (char *)q->base;
		he = (char *)q->end - (char *)q->head;
		be = bh + he;
		bc = be * q->rc;
		char *newb = malloc(bc);
		if (newb == NULL)
			return -1;
		_memcpy(newb, q->head, he);
		_memcpy(newb + he, q->base, bh);
		q->end = newb + bc;
		q->tail = newb + be;
		q->head = q->base = newb;
	}
	if (!q->cp(q->tail, data)) {
		q->tail = (char *)q->tail + q->off;
		return 0;
	}
	return -1;
}

//get
void *pop_qu(struct queue *q)
{
	if (q->head == q->tail && q->head == q->base)
		return NULL;
	void *ret = q->head;
	q->head = (char *)q->head + q->off;
	if (q->head == q->tail)
		q->head = q->tail = q->base;
	else if (q->head == q->end)
		q->head = q->base;
	return ret;
}

//find
void *fnd_qu(const struct queue *q, const void *data)
{
	if (q->head == q->tail && q->head == q->base)
		return NULL;
	register char *cur = q->head;
	if (cur >= (char *)q->tail) {
		for (; cur != q->end; cur += q->off)
			if (!q->cmp(cur, data))
				return cur;
		cur = q->base;
	}
	for (; cur != q->tail; cur += q->off)
		if (!q->cmp(cur, data))
			return cur;
	return NULL;
}
void *fndr_qu(const struct queue *q, const void *data)
{
	if (q->head == q->tail && q->head == q->base)
		return NULL;
	register char *cur = q->tail;
	if (cur < (char *)q->head) {
		for (cur -= q->off; cur != q->base; cur -= q->off)
			if (!q->cmp(cur, data))
				return cur;
		cur = q->end;
	}
	for (cur -= q->off; cur != q->head; cur -= q->off)
		if (!q->cmp(cur, data))
			return cur;
	return NULL;
}  

//apply
void appl_qu(const struct queue *q, void (*fun)(void *, void *), void *arg)
{
	if (q->head == q->tail && q->head == q->base)
		return;
	register char *cur = q->head;
	if (cur >= (char *)q->tail) {
		for (; cur != q->end; cur += q->off)
			fun(cur, arg);
		cur = q->base;
	}
	for (; cur != q->tail; cur += q->off)
		fun(cur, arg);
}
void applr_qu(const struct queue *q, void (*fun)(void *, void *), void *arg)
{
	if (q->head == q->tail && q->head == q->base)
		return;
	register char *cur = q->tail;
	if (cur < (char *)q->tail) {
		for (cur -= q->off; cur != q->base; cur -= q->off)
			fun(cur, arg);
		cur = q->end;
	}
	for (cur -= q->off; cur != q->head; cur -= q->off)
		fun(cur, arg);
}
