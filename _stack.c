#include <stdio.h>
#include <stdlib.h>
#include "_stddef.h"
#include "_stack.h"

//alloc/dealloc
int mk_st(struct stack *st, unsigned int cnt)
{
	sz_t bc;

	bc = cnt * st->off;
	st->base = malloc(bc);
	if (st->base != NULL) {
		st->end = (char*)(st->top = st->base) + bc;
		return 0;
	}
	return -1;
}
void rm_st(struct stack *st)
{
	free(st->base);
	st->top = st->end = st->base = NULL;
}

//add
int push_st(struct stack *st, void *data)
{
	sz_t bc, tc;
	char *newb;
	
	//try realloc if full
	if (st->top == st->end) {
		bc = ((char*)st->end - (char*)st->base) * st->rc;
		tc = (char*)st->top - (char*)st->base;
		newb = realloc(st->base, bc);
		if (newb == NULL)
			return -1;
		st->end = newb + bc;
		st->top = newb + tc;
		st->base = newb;
	}
	//try add
	if (!st->cp(st->top, data)) {
		st->top = (char*)st->top + st->off;
		return 0;
	}
	return -1;
}

//add
void *pop_st(struct stack *st)
{
	if (st->top != st->base)
		return st->top = (char*)st->top - st->off;
	return NULL;
}

//find
void *fnd_st(const struct stack *st, const void *data)
{
	register char *cur;
	
	for (cur = st->top; cur != st->base; )
		if (!st->cmp(cur -= st->off, data))
			return cur;
	return NULL;
}
void *fndr_st(const struct stack *st, const void *data)
{
	register char *cur;
	
	for (cur = st->base; cur != st->top; cur += st->off)
		if (!st->cmp(cur, data))
			return cur;
	return NULL;
}

//apply
void appl_st(const struct stack *st, void (*fun)(void *, void *), void *arg)
{
	register char *cur;
	
	for (cur = st->top; cur != st->base; )
		fun(cur -= st->off, arg);
}
void applr_st(const struct stack *st, void (*fun)(void *, void *), void *arg)
{
	register char *cur;
	
	for (cur = st->base; cur != st->top; cur += st->off)
		fun(cur, arg);
}
