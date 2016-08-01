#ifndef _TREE_H
#define _TREE_H

#include "_stddef.h"

//main binary tree structure
struct tree{
	void *root;
	unsigned int cnt;
	sz_t loff, roff;
	void *(*mk_node)(void *, void *, void *);
	void *(*upd_node)(void *, void *);
	void (*free_node)(void *);
	int (*cmp)(const void *, const void *);
};

//byte offsets from start of node to left/right subtree pointers
#define left(cur, loff) (*(void **)((char *)cur + loff))
#define right(cur, roff) (*(void **)((char *)cur + roff))

//add
void *add_nodet(struct tree *tr, void *data);

//rm
void rm_nodet(struct tree *tr, void *data);
void rm_tr(struct tree *tr);

//find
void *fnd_nodet(const struct tree *tr, const void *data);

//apply
void appl_tr(struct tree *tr,void (*fun)(void *, void *), void *arg);

#endif
