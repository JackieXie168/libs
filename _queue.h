/*
 * queue
 *
 * Copyright (C) 2015  Stanislav Gubin
 */
#ifndef _QUEUE_H
#define _QUEUE_H

#include "_stddef.h"

/* queue main structure */
struct queue {
	void *base, *end, *head, *tail;
	sz_t off;
	int (*cp)(void*, void*);
	int (*cmp)(const void *, const void *);
	unsigned int rc;
};

/* alloc/dealloc */
int mk_qu(struct queue *q, unsigned int cnt);
void rm_qu(struct queue *q);

/* logic */
int push_qu(struct queue *q, void *data);
void *pop_qu(struct queue *q);

/* find */
void *fnd_qu(const struct queue *q, const void *data);
void *fndr_qu(const struct queue *q, const void *data);

/* apply function to each */
void appl_qu(const struct queue *q, void (*fun)(void *, void *), void *arg);
void applr_qu(const struct queue *q ,void (*fun)(void *, void *), void *arg);

#endif
