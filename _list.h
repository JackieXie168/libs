#ifndef _LIST_H
#define _LIST_H

#include"_stddef.h"

/* linked list main structure */
struct list{
	void *head;
	unsigned int cnt;
	sz_t off;
	void *(*mk_node)(void *, void *);
	void (*free_node)(void *);
	int (*cmp)(const void *, const void *);
};

/* byte offset between node start and pointer to next node */
#define next(cur, off) (*(void **)((char *)cur + off))

/* add */
void *add_head(struct list *ls, void *data);
void *add_tail(struct list *ls, void *data);
void *add_pos(struct list *ls, void *data, unsigned int pos);

/* remove */
void rm_head(struct list *ls);
void rm_tail(struct list *ls);
void rm_pos(struct list *ls, unsigned int pos);
void rm_node(struct list *ls, void *data);
void rm_nodes(struct list *ls, void *data);
void rm_ls(struct list *ls);

/* find */
void *fnd_tail(const struct list *ls);
void *fnd_pos(const struct list *ls, unsigned int pos);
void *fnd_node(const struct list *ls, const void *data);

/* apply */
void appl_ls(const struct list *ls, void (*fun)(void *, void *), void *arg);

#endif
