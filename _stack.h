/*
 * stack
 *
 * Copyright (C) 2015  Stanislav Gubin
 */
#ifndef _STACK_H
#define _STACK_H

#include "_stddef.h"

//stack main structure
struct stack {
	void *base, *end, *top;
	sz_t off;
	int (*cp)(void *, void *);
	int (*cmp)(const void *, const void *);
	unsigned int rc;
};

//alloc/dealloc
int mk_st(struct stack *st, unsigned int cnt);
void rm_st(struct stack *st);

//logic
int push_st(struct stack *st, void *data);
void *pop_st(struct stack *st);

//find
void *fnd_st(const struct stack *st, const void *data);
void *fndr_st(const struct stack *st, const void *data);

//apply
void appl_st(const struct stack *st, void (*fun)(void *, void *), void *arg);
void applr_st(const struct stack *st, void (*fun)(void *, void *), void *arg);

#endif
