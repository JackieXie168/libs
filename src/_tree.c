/*
 * binary tree
 *
 * Copyright (C) 2015  Stanislav Gubin
 */
#include "_stddef.h"
#include "_tree.h"

/* add node */
void *add_nodet(struct tree *tr, void *data)
{
	register void **cur;
	register int cmp;
	
	for (cur = &tr->root; *cur != NULL; ) {
		cmp = tr->cmp(*cur, data);
		if (!cmp)
			return tr->upd_node(*cur, data);
		cur = cmp < 0 ? &right(*cur, tr->roff) : &left(*cur, tr->loff);
	}
	*cur = tr->mk_node(data, NULL, NULL);
	if (*cur != NULL)
		tr->cnt++;
	return *cur;
}

/* remove node */
void rm_nodet(struct tree *tr, void *data)
{
	register void **cur;
	register int cmp;
	void *l, *r;
	
	for (cur = &tr->root; *cur != NULL && (cmp = tr->cmp(*cur, data)); )
		cur = cmp < 0 ? &right(*cur, tr->roff) : &left(*cur, tr->loff);
	if (*cur == NULL)
		return;
	tr->cnt--;
	l = left(*cur, tr->loff);
	r = right(*cur, tr->roff);
	tr->free_node(*cur);
	if (l != NULL) {
		*cur = l;
		if (r != NULL) {
			while (right(*cur, tr->roff) != NULL)
				cur = &right(*cur, tr->roff);
			right(*cur, tr->roff) = r;
		}
	} else
		*cur = r;
}

/* remove tree */
void rm_tr(struct tree *tr)
{
	register void *root;
	
	if (tr->root == NULL)
		return;
	root = tr->root;
	tr->root = left(root, tr->loff);
	rm_tr(tr);
	tr->root = right(root, tr->roff);
	rm_tr(tr);
	tr->free_node(root);
	tr->cnt--; /* or tr->cnt = 0 */
}

/* find */
void *fnd_nodet(const struct tree *tr, const void *data)
{
	register void *cur;
	register int cmp;
	
	for (cur = tr->root; cur != NULL && (cmp = tr->cmp(cur, data)); )
		cur = cmp < 0 ? right(cur, tr->roff) : left(cur, tr->loff);
	return cur;
}

/* apply function to each */
void appl_tr(struct tree *tr, void (*fun)(void *, void *), void *arg)
{
	register void *root;
	
	if (tr->root == NULL)
		return;
	root = tr->root;
	tr->root = left(root, tr->loff);
	appl_tr(tr, fun, arg);
	(*fun)(root, arg);
	tr->root = right(root, tr->roff);
	appl_tr(tr, fun, arg);
	tr->root = root;
}
