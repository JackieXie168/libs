#ifndef _LISTB_H
#define _LIST_H

#include "_stddef.h"

//both-linked list main structure
struct listb {
	void *head, *tail;
	unsigned int cnt;
	sz_t noff, poff;
	void *(*mk_node)(void *, void *, void *);
	void (*free_node)(void*);
	int (*cmp)(const void *, const void *);
};

//byte offset between node start and pointer to prev/next node
#define nextb(cur, noff) (*(void **)((char*)cur + noff))
#define prevb(cur, poff) (*(void **)((char*)cur + poff))

//add
void *add_headb(struct listb *ls, void *data);
void *add_tailb(struct listb *ls, void *data);
void *add_posb(struct listb *ls, void *data, unsigned int pos);

//rm
void rm_headb(struct listb *ls);
void rm_tailb(struct listb *ls);
void rm_posb(struct listb *ls, unsigned int pos);
void rm_nodeb(struct listb *ls, void *data);
void rm_nodesb(struct listb *ls, void *data);
void rm_lsb(struct listb *ls);

//find
void *fnd_posb(const struct listb *ls, unsigned int pos);
void *fnd_nodeb(const struct listb *ls, const void *data);

//apply
void appl_lsb(const struct listb *ls, void (*fun)(void *, void *), void *arg);

#endif
