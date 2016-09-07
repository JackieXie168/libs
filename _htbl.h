/*
 * hash table
 *
 * Copyright (C) 2015  Stanislav Gubin
 */
#ifndef _HTBL_H
#define _HTBL_H

#include "_stddef.h"

/* main hash table data structure */
struct htbl{
	void **ht;
	unsigned int len, cnt;
	sz_t off;
	void *(*mk_node)(void *, void *);
	void *(*upd_node)(void *, void *);
	void (*free_node)(void *);
	int (*cmp)(const void *, const void *);
	unsigned int (*hash)(const void *);
};

/* byte offset between node start and pointer to next node */
#define next(cur, off) (*(void **)((char *)cur + off))

/* alloc/dealloc */
int mk_ht(struct htbl *ht);
void rm_ht(struct htbl *ht);

/* add */
void *add_nodeh(struct htbl *ht, void *data);

/* remove */
void rm_nodeh(struct htbl *ht, void *data);

/* find */
void *fnd_nodeh(const struct htbl *ht, const void *data);

/* apply */
void appl_ht(const struct htbl *ht, void (*fun)(void *,void *), void *arg);

#endif
