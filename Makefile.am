ACLOCAL_AMFLAGS = -I m4
AM_LDFLAGS = -lm

SUBDIRS = src include

EXTRA_DIST = doc/*.pdf doc/doxygen doc/doxygen-private patterns/*

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libustdc.pc

doc/doxygen:
	@mkdir -p $(builddir)/$@
	pushd $(abs_srcdir) && sed -e "s|^OUTPUT_DIRECTORY.*$$|OUTPUT_DIRECTORY = $(abs_builddir)/$@|;" < Doxyfile | doxygen - && popd

doc/doxygen-private:
	@mkdir -p $(builddir)/$@
	pushd $(abs_srcdir)/include && sed -e "s|^OUTPUT_DIRECTORY.*$$|OUTPUT_DIRECTORY = $(abs_builddir)/$@|;" < Doxyfile | doxygen - && popd

clean-local:
	rm -rf doc/doxygen
	rm -rf doc/doxygen-private

#DISTCLEANFILES = Makefile.in aclocal.m4 autoscan.log compile config.guess config.sub configure configure.scan config.h.in ltmain.sh *~ 
CLEANFILES = *~ *.log
