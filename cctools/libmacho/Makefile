builddir = .
top_builddir = ..
srcdir = .
top_srcdir = ..



prefix          = /usr/local/usr
exec_prefix     = ${prefix}
libdir          = ${exec_prefix}/lib

CC		= gcc -m32
AR		= ar
RANLIB		= ranlib
CFLAGS		= -fcommon -Wno-deprecated -Wno-attributes -Wno-maybe-uninitialized -Wno-narrowing -Wno-int-conversion -Wno-address -Wall -Wno-implicit-function-declaration -Wno-format -Wno-enum-compare -Wno-unused-result -Wno-unused-variable -Wno-unused-but-set-variable -Wno-deprecated -Wno-deprecated-declarations -Wno-char-subscripts -Wno-strict-aliasing -Wno-shift-negative-value -fno-builtin-round -fno-builtin-trunc
WARNINGS	=  -Wall -Wno-long-double -Wno-import
CPPFLAGS	= 
DEFS		= -DHAVE_CONFIG_H -D__LITTLE_ENDIAN__=1
LDFLAGS		= -m32
HAVE_PRIVEXT	= NO
HAVE_FOREIGN_HEADERS	= YES

INSTALL         = /usr/bin/install -c
INSTALL_DATA    = ${INSTALL} -m 644

ifeq ($(HAVE_PRIVEXT),NO)
INCPRIVEXT	= -include $(top_srcdir)/include/extern.h
endif

ifeq ($(HAVE_FOREIGN_HEADERS),YES)
FORHDRS		= -I$(top_srcdir)/include/foreign
endif

MYINCLUDES	= -I$(top_builddir)/include -I$(top_srcdir)/include \
			$(INCPRIVEXT) $(FORHDRS)
MYWARNINGS	= 
MYDEFS		= 

MYCOMPILEFLAGS	= $(WARNINGS) $(MYWARNINGS) $(DEFS) $(MYDEFS) \
	$(CPPFLAGS) $(MYINCLUDES) $(CFLAGS)

CFILES = arch.c
ECFILES = emulated.c

OBJS = $(CFILES:.c=.o)
EOBJS = $(ECFILES:.c=.o)

.PHONY: default install clean distclean

default: libmacho.a

libmacho.a: $(OBJS) $(EOBJS)
	$(AR) cru $@ $^
	$(RANLIB) $@

$(OBJS): %.o: %.c
	$(CC) $(MYCOMPILEFLAGS) -c -o $@ $<

emulated.o: $(top_srcdir)/libstuff/emulated.c
	$(CC) $(MYCOMPILEFLAGS) -c -o $@ $<

clean:
	rm -r -f *.o
	rm -f libmacho.a

install: libmacho.a
	mkdir -p $(DESTDIR)$(libdir)
	$(INSTALL_DATA) $< $(DESTDIR)$(libdir)/$<
	$(RANLIB) $(DESTDIR)$(libdir)/$<
