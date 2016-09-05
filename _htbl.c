/*
 * hash table
 *
 * Copyright (C) 2015  Stanislav Gubin
 */
#include <stdlib.h>
#include "_stddef.h"
#include "_htbl.h"

/* alloc */
int mk_ht(struct htbl *ht)
{
	ht->ht = malloc(ht->len * sizeof(void *));
	if (ht->ht != NULL)
		return 0;
	return -1;
}

/* dealloc */
void rm_ht(struct htbl *ht)
{
	register void **cl;      //current list
	register unsigned int i;
	register void *cn, *nxt;  //current node
	
	for (i = ht->len, cl = ht->ht; i--; cl++)
		for (cn = *cl; cn != NULL; cn = nxt) {
			nxt = next(cn, ht->off);
			ht->free_node(cn);
		}
	free(ht->ht);
	ht->ht = NULL;
	ht->len = ht->cnt = 0;
}

/* add node */
void *add_nodeh(struct htbl *ht, void *data)
{
	unsigned int h;
	register void *cur;
	void *new;
	
	for (h = ht->hash(data), cur = ht->ht[h];
	     cur != NULL; cur = next(cur, ht->off))
		if (!ht->cmp(cur, data))
			return ht->upd_node(cur, data);
	new = ht->mk_node(data, ht->ht[h]);
	if (new != NULL) {
		ht->ht[h] = new;
		ht->cnt++;
	}
	return new;
}

/* rm_node */
void rm_nodeh(struct htbl *ht, void *data)
{
	unsigned int h;
	register void *prv, *cur;
	
	for (h = ht->hash(data), prv = NULL, cur = ht->ht[h];
	     cur != NULL; prv = cur, cur = next(cur, ht->off))
		if (!ht->cmp(cur,data)) {
			if (prv != NULL)
				next(prv, ht->off) = next(cur, ht->off);
			else
				ht->ht[h] = next(cur, ht->off);
			ht->free_node(cur);
			ht->cnt--;
			return;
		}
}

/* find node */
void *fnd_nodeh(const struct htbl *ht,const void *data)
{
	register void *cur;
	
	for (cur = ht->ht[ht->hash(data)]; cur != NULL && ht->cmp(cur, data);
	     cur = next(cur, ht->off))
		;
	return cur;
}

/* apply */
void appl_ht(const struct htbl *ht, void (*fun)(void *, void *), void *arg)
{
	register void **cl;
	register void *cn;
	register unsigned int i;
	
	for (i = ht->len, cl = ht->ht; i--; cl++)
		for (cn = *cl; cn != NULL; cn = next(cn, ht->off))
			(*fun)(cn, arg);
}
