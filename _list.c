#include "_stddef.h"
#include "_list.h"

//add
void *add_head(struct list *ls, void *data)
{
	void *newh = ls->mk_node(data, ls->head);
	if (newh != NULL) {
		ls->head = newh;
		ls->cnt++;
	}
	return newh;
}
void *add_tail(struct list *ls, void *data)
{
	if (ls->head == NULL)
		return add_head(ls, data);
	void *newt = ls->mk_node(data, NULL);
	if (newt == NULL)
		return NULL;
	ls->cnt++;
	register void *cur;
	for (cur = ls->head; next(cur, ls->off) != NULL; cur = next(cur, ls->off))
		;
	return next(cur, ls->off) = newt;
}
void *add_pos(struct list *ls, void *data, unsigned int pos)
{
	if (!pos)
		return add_head(ls, data);
	if (pos > ls->cnt)
		return NULL;
	//try alloc (no need loop if fail)
	void *new = ls->mk_node(data, NULL); //NULL is temporary
	if (new == NULL)
		return NULL;
	ls->cnt++;
	register void *cur;
	for (cur = ls->head; --pos; cur = next(cur, ls->off))
		;
	next(new, ls->off) = next(cur, ls->off);
	return next(cur, ls->off) = new;
}

//rm
void rm_head(struct list *ls)
{
	if (ls->head == NULL)
		return;
	void *newh = next(ls->head, ls->off);
	ls->free_node(ls->head);
	ls->head = newh;
	ls->cnt--;
}
void rm_tail(struct list *ls)
{
	if (ls->head == NULL)
		return;
	if (next(ls->head, ls->off) == NULL) {
		rm_head(ls);
		return;
	}
	register void *cur;
	for (cur = ls->head; next(next(cur, ls->off), ls->off) != NULL;
	     cur = next(cur, ls->off))
		;
	ls->free_node(next(cur, ls->off));
	next(cur, ls->off) = NULL;
	ls->cnt--;
}
void rm_pos(struct list *ls, unsigned int pos)
{
	if (ls->head == NULL)
		return;
	if (!pos) {
		rm_head(ls);
		return;
	}
	if (pos >= ls->cnt)
		return;
	register void *cur;
	for (cur = ls->head; --pos; cur = next(cur, ls->off))
		;
	void *nxt = next(next(cur, ls->off), ls->off);
	ls->free_node(next(cur, ls->off));
	next(cur, ls->off) = nxt;
	ls->cnt--;
}
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
void rm_nodes(struct list *ls, void *data)
{
	register void *prv = ls->head;
	if (prv == NULL)
		return;
	register void *cur;
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

//find
void *fnd_tail(const struct list *ls)
{
	if (ls->head == NULL)
		return NULL;
	register void *cur;
	for (cur = ls->head; next(cur, ls->off) != NULL;
	    cur = next(cur, ls->off))
		;
	return cur;
}
void *fnd_pos(const struct list *ls, unsigned int pos)
{
	if (pos >= ls->cnt)
		return NULL;
	register void *cur;
	for (cur = ls->head; pos--; cur=next(cur, ls->off))
		;
	return cur;
}
void *fnd_node(const struct list *ls, const void *data)
{
	register void *cur;
	for (cur = ls->head; cur != NULL; cur = next(cur, ls->off))
		if (!ls->cmp(cur, data))
			return cur;
	return NULL;
}

//apply to each
void appl_ls(const struct list *ls, void (*fun)(void *, void *), void *arg)
{
	register void *cur;
	for (cur = ls->head; cur != NULL; cur = next(cur, ls->off))
		fun(cur, arg);
}
