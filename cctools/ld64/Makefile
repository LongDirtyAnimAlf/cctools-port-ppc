builddir = .
top_builddir = ..
srcdir = .
top_srcdir = ..

prefix		= /usr/local/usr
exec_prefix	= ${prefix}
bindir		= ${exec_prefix}/bin

VPATH = ./src

CC              = gcc -m32
CXX             = g++ -m32
CFLAGS          = -fcommon -Wno-deprecated -Wno-attributes -Wno-maybe-uninitialized -Wno-narrowing -Wno-int-conversion -Wno-address -Wall -Wno-implicit-function-declaration -Wno-format -Wno-enum-compare -Wno-unused-result -Wno-unused-variable -Wno-unused-but-set-variable -Wno-deprecated -Wno-deprecated-declarations -Wno-char-subscripts -Wno-strict-aliasing -Wno-shift-negative-value -fno-builtin-round -fno-builtin-trunc -g -O2
WARNINGS	=  -Wall -Wno-long-double -Wno-import
MDYNAMICNOPIC   = 
CPPFLAGS        = 
DEFS            = -DHAVE_CONFIG_H -D__LITTLE_ENDIAN__=1
LDFLAGS         = -m32
HAVE_PRIVEXT    = NO
HAVE_FOREIGN_HEADERS    = YES

ifeq ($(HAVE_PRIVEXT),NO)
INCPRIVEXT      = -include $(top_srcdir)/include/extern.h
endif

ifeq ($(HAVE_FOREIGN_HEADERS),YES)
FORHDRS         = -I$(top_srcdir)/include/foreign
endif

INSTALL		= /usr/bin/install -c
INSTALL_PROGRAM	= ${INSTALL}
transform       = s&^&powerpc-apple-darwin8-&

MYINCLUDES      = -I$(builddir) -I$(srcdir) -I$(srcdir)/src -I$(top_builddir)/include \
			-I$(top_srcdir)/include $(INCPRIVEXT) $(FORHDRS)
MYWARNINGS      = 
MYDEFS          = -DDEBUG -DLD_CLASSIC="\"$(shell echo ld_classic | sed '$(transform)')\""
MYLDFLAGS	= -L$(top_builddir)/libstuff
MYLIBS		= -lstuff -luuid -lcrypto -ldl

MYCOMPILEFLAGS	= $(WARNINGS) $(MYWARNINGS) $(DEFS) $(MYDEFS) \
	$(CPPFLAGS) $(MYINCLUDES) $(CFLAGS) $(MDYNAMICNOPIC) 

MYLINKFLAGS	= $(LDFLAGS) $(MYLDFLAGS) $(MYLIBS)

CXXFILES = ld.cpp Options.cpp
CFILES = debugline.c strlcpy.c

OBJS = $(CXXFILES:.cpp=.o) $(CFILES:.c=.o)
.cpp.o:
	$(CXX) $(MYCOMPILEFLAGS) -c -o $@ $<
.c.o:
	$(CC)  $(MYCOMPILEFLAGS) -c -o $@ $<

.PHONY: default clean distclean install

default: ld64

ld64: $(OBJS)
	$(CXX) -o $@ $^ $(MYLINKFLAGS)

install: ld64
	mkdir -p $(DESTDIR)$(bindir)
	$(INSTALL_PROGRAM) ld64 \
		$(DESTDIR)$(bindir)/`echo ld64 | sed '$(transform)'`

clean:
	rm -r -f *.o */*.o
	rm -f ld64
