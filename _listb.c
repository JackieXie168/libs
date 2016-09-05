/*
 * double-linked list
 *
 * Copyright (C) 2015  Stanislav Gubin
 */
#include "_stddef.h"
#include "_listb.h"

/* add to head */
void *add_headb(struct listb *ls, void *data)
{
	void *newh;

	newh = ls->mk_node(data, ls->head, NULL);
	if (newh == NULL)
		return NULL;
	ls->cnt++;
	if (ls->head != NULL)
		prevb(ls->head, ls->poff) = newh;
	else
		ls->tail = newh;
	return ls->head = newh;
}

/* add to tail */
void *add_tailb(struct listb *ls, void *data)
{
	void *newt;

	newt = ls->mk_node(data, NULL, ls->tail);
	if (newt == NULL)
		return NULL;
	ls->cnt++;
	if (ls->tail != NULL)
		nextb(ls->tail, ls->noff) = newt;
	else
		ls->head = newt;
	return ls->tail = newt;
}

/* add by index */
void *add_posb(struct listb *ls, void *data, unsigned int pos)
{
	register void *cur;
	register sz_t off0;
	void *new;
	sz_t off1;

	if (!pos)
		return add_headb(ls, data);
	if (pos == ls->cnt)
		return add_tailb(ls, data);
	if (pos > ls->cnt)
		return NULL;
	/* try alloc (no need loop if fail) */
	new = ls->mk_node(data, NULL, NULL); /* NULL is temporary */
	if (new == NULL)
		return NULL;
	ls->cnt++;
	/* choose best way to go */
	if (pos < (ls->cnt >> 1)) {
		cur = ls->head;
		off0 = ls->noff;
		off1 = ls->poff;
	} else {
		cur = ls->tail;
		off0 = ls->poff;
		off1 = ls->noff;
		pos = ls->cnt - pos;
	}
	for (; --pos; cur = nextb(cur, off0))
		;
	nextb(new, off0) = nextb(cur, off0);
	nextb(new, off1) = nextb(nextb(cur, off0), off1);
	return nextb(cur, off0) = nextb(nextb(new, off0), off1) = new;
}

/* remove head */
void rm_headb(struct listb *ls)
{
	void *newh;
	
	if (ls->head == NULL)
		return;
	newh = nextb(ls->head, ls->noff);
	ls->free_node(ls->head);
	ls->head = newh;
	ls->cnt--;
	if (ls->head != NULL)
		prevb(ls->head, ls->poff) = NULL;
	else
		ls->tail = NULL;
}

/* remove tail */
void rm_tailb(struct listb *ls)
{
	void *newt;
	
	if (ls->tail == NULL)
		return;
	newt = prevb(ls->tail, ls->poff);
	ls->free_node(ls->tail);
	ls->tail = newt;
	ls->cnt--;
	if (ls->tail != NULL)
		nextb(ls->tail, ls->noff) = NULL;
	else
		ls->head = NULL;
}

/* remove by index */
void rm_posb(struct listb *ls, unsigned int pos)
{
	register void *cur;
	register sz_t off0;
	sz_t off1;
	void *new;

	if (ls->head == NULL)
		return;
	if (!pos) {
		rm_head(ls);
		return;
	}
	if (pos == ls->cnt - 1) {
		rm_tail(ls);
		return;
	}
	if (pos >= ls->cnt)
		return;
	ls->cnt--;
	/* choose best way to go */
	if (pos < (ls->cnt >> 1)) {
		cur = ls->head;
		off0 = ls->noff;
		off1 = ls->poff;
	} else {
		cur = ls->tail;
		off0 = ls->poff;
		off1 = ls->noff;
		pos = ls->cnt - pos - 1;
	}
	for (; --pos; cur = nextb(cur, off0))
		;
	nxt = nextb(nextb(cur, off0), off0);
	ls->free_node(nextb(cur, off0));
	nextb(cur, off0) = nxt;
	nextb(nxt, off1) = cur;
}

/* remove first match by data */
void rm_nodeb(struct listb *ls, void *data)
{
	register void *cur;
	
	for (cur = ls->head; cur != NULL; cur = nextb(cur, ls->noff))
		if (!ls->cmp(cur, data)) {
			if (prevb(cur, ls->poff) != NULL)
				nextb(prevb(cur, ls->poff), ls->noff) = nextb(cur, ls->noff);
			else
				ls->head=cur;
			if (nextb(cur, ls->noff) != NULL)
				prevb(nextb(cur, ls->noff), ls->poff) = prevb(cur, ls->poff);
			else
				ls->tail = cur;
			ls->free_node(cur);
			ls->cnt--;
			return;
		}
}

/* remove all match by data */
void rm_nodesb(struct listb *ls, void *data)
{
	register void *cur, *nxt;
	
	if (ls->head == NULL)
		return;
	for (cur = ls->head; nextb(cur, ls->noff) != NULL; cur = nextb(cur, ls->noff))
		if (!ls->cmp(nextb(cur, ls->noff), data)){
			nxt=nextb(nextb(cur, ls->noff), ls->noff);
			ls->free_node(nextb(cur, ls->noff));
			nextb(cur, ls->noff) = nxt;
			if (nxt != NULL)
				prevb(nxt, ls->poff) = cur;
			else
				ls->tail = cur;
			ls->cnt--;
		}
	if (!ls->cmp(ls->head, data))
		rm_headb(ls);
}

/* remove all */
void rm_lsb(struct listb *ls)
{
	register void *cur, *nxt;
	
	for (cur = ls->head; cur != NULL; cur = nxt) {
		nxt = nextb(cur, ls->noff);
		ls->free_node(cur);
	}
	ls->cnt = 0;
	ls->head = ls->tail = NULL;
}

/* find by index */
void *fnd_posb(const struct listb *ls, unsigned int pos)
{
	register void *cur;
	register sz_t off;

	if (ls->head == NULL || pos >= ls->cnt)
		return NULL;
	if (pos < (ls->cnt >> 1)) {
		cur = ls->head;
		off = ls->noff;
	} else {
		cur = ls->tail;
		off = ls->poff;
		pos = ls->cnt - pos - 1;
	}
	for (; pos--; cur = nextb(cur, off))
		;
	return cur;
}

/* find by data */
void *fnd_nodeb(const struct listb *ls, const void *data)
{
	register void *cur;
	
	for (cur = ls->head; cur != NULL; cur = nextb(cur, ls->noff))
		if (!ls->cmp(cur, data))
			return cur;
	return NULL;
}

/* apply function to each */
void appl_lsb(const struct listb *ls, void (*fun)(void *, void *), void *arg)
{
	register void *cur;
	
	for (cur = ls->head; cur != NULL; cur = nextb(cur, ls->noff))
		fun(cur,arg);
}
