/*
 * single-linked list
 *
 * Copyright (C) 2015  Stanislav Gubin
 */
#include "_stddef.h"
#include "_list.h"

/* add to head */
void *add_head(struct list *ls, void *data)
{
	void *newh;

	newh = ls->mk_node(data, ls->head);
	if (newh != NULL) {
		ls->head = newh;
		ls->cnt++;
	}
	return newh;
}

/* add to tail */
void *add_tail(struct list *ls, void *data)
{
	void *newt;
	register void *cur;
	
	if (ls->head == NULL)
		return add_head(ls, data);
	newt = ls->mk_node(data, NULL);
	if (newt == NULL)
		return NULL;
	ls->cnt++;
	for (cur = ls->head; next(cur, ls->off) != NULL; cur = next(cur, ls->off))
		;
	return next(cur, ls->off) = newt;
}

/* add by index */
void *add_pos(struct list *ls, void *data, unsigned int pos)
{
	void *new;
	register void *cur;
	
	if (!pos)
		return add_head(ls, data);
	if (pos > ls->cnt)
		return NULL;
	/* try alloc (no need loop if fail) */
	new = ls->mk_node(data, NULL); /* NULL is temporary */
	if (new == NULL)
		return NULL;
	ls->cnt++;
	for (cur = ls->head; --pos; cur = next(cur, ls->off))
		;
	next(new, ls->off) = next(cur, ls->off);
	return next(cur, ls->off) = new;
}

/* remove from head */
void rm_head(struct list *ls)
{
	void *newh;
	
	if (ls->head == NULL)
		return;
	newh = next(ls->head, ls->off);
	ls->free_node(ls->head);
	ls->head = newh;
	ls->cnt--;
}

/* remove from tail */
void rm_tail(struct list *ls)
{
	register void *cur;
	
	if (ls->head == NULL)
		return;
	if (next(ls->head, ls->off) == NULL) {
		rm_head(ls);
		return;
	}
	for (cur = ls->head; next(next(cur, ls->off), ls->off) != NULL;
	     cur = next(cur, ls->off))
		;
	ls->free_node(next(cur, ls->off));
	next(cur, ls->off) = NULL;
	ls->cnt--;
}

/* remove by index */
void rm_pos(struct list *ls, unsigned int pos)
{
	register void *cur;
	void *nxt;
	
	if (ls->head == NULL)
		return;
	if (!pos) {
		rm_head(ls);
		return;
	}
	if (pos >= ls->cnt)
		return;
	for (cur = ls->head; --pos; cur = next(cur, ls->off))
		;
	nxt = next(next(cur, ls->off), ls->off);
	ls->free_node(next(cur, ls->off));
	next(cur, ls->off) = nxt;
	ls->cnt--;
}

/* remove first match by data */
void rm_node(struct list *ls, void *data)
{
	register void *prv, *cur;
	
	for (prv = NULL, cur = ls->head; cur != NULL;
	     prv = cur, cur = next(cur, ls->off))
		if (!ls->cmp(cur, data)) {
			if (prv != NULL)
				next(prv, ls->off) = next(cur, ls->off);
			else
				ls->head = next(cur, ls->off);
			ls->free_node(cur);
			ls->cnt--;
			return;
		}
}

/* remove all match by data */
void rm_nodes(struct list *ls, void *data)
{
	register void *prv, *cur;

	prv = ls->head;
	if (prv == NULL)
		return;
	while ((cur = next(prv, ls->off)) != NULL)
		if (!ls->cmp(cur, data)) {
			next(prv, ls->off) = next(cur, ls->off);
			ls->free_node(cur);
			ls->cnt--;
		} else
			prv = cur;
	if (!ls->cmp(ls->head, data))
		rm_head(ls); 
}

/* remove all */
void rm_ls(struct list *ls)
{
	register void *cur, *nxt;
	
	for (cur = ls->head; cur!=NULL; cur = nxt) {
		nxt = next(cur, ls->off);
		ls->free_node(cur);
	}
	ls->head = NULL;
	ls->cnt = 0;
}

/* find tail */
void *fnd_tail(const struct list *ls)
{
	register void *cur;
	
	if (ls->head == NULL)
		return NULL;
	for (cur = ls->head; next(cur, ls->off) != NULL;
	    cur = next(cur, ls->off))
		;
	return cur;
}

/* find by index */
void *fnd_pos(const struct list *ls, unsigned int pos)
{
	register void *cur;
	
	if (pos >= ls->cnt)
		return NULL;
	for (cur = ls->head; pos--; cur=next(cur, ls->off))
		;
	return cur;
}

/* find first match by data */
void *fnd_node(const struct list *ls, const void *data)
{
	register void *cur;

	for (cur = ls->head; cur != NULL; cur = next(cur, ls->off))
		if (!ls->cmp(cur, data))
			return cur;
	return NULL;
}

/* apply function to each */
void appl_ls(const struct list *ls, void (*fun)(void *, void *), void *arg)
{
	register void *cur;

	for (cur = ls->head; cur != NULL; cur = next(cur, ls->off))
		fun(cur, arg);
}
