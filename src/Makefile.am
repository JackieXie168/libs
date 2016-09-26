AM_CFLAGS=-I$(top_srcdir)/include
AM_LDFLAGS=
AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES = libustdc.la
libustdc_la_SOURCES = \
	_htbl.c \
	_list.c \
	_listb.c \
	_queue.c \
	_stack.c \
	_stdlib.c \
	_string.c \
	_tree.c

#libustdc_la_LIBADD = $(top_srcdir)/nvram/libdniutils-1.0.la

#DISTCLEANFILES = Makefile.in
CLEANFILES = *~ *.log
