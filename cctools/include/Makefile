builddir = .
top_builddir = ..
srcdir = .
top_srcdir = ..

prefix	= /usr/local/usr
exec_prefix	= ${prefix}
mandir		= ${prefix}/share/man
includedir	= ${prefix}/include



INSTALL		= /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA	= ${INSTALL} -m 644

.PHONY: default install clean distclean

default:

install: 
	mkdir -p $(DESTDIR)$(includedir)
	mkdir -p $(DESTDIR)$(includedir)/mach-o
	for h in loader.h fat.h; do		\
		$(INSTALL_DATA) $(srcdir)/mach-o/$$h		\
			$(DESTDIR)$(includedir)/mach-o/$$h;	\
	done
	$(INSTALL_DATA) $(srcdir)/mach-o/arch-install.h \
		$(DESTDIR)$(includedir)/mach-o/arch.h
	$(INSTALL_DATA) $(srcdir)/mach/machine.h \
		$(DESTDIR)$(includedir)/mach-o/

clean:
