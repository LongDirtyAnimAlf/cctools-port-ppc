#!/usr/bin/env bash

#---------------------------------------------------------------------------------
# set the target
#---------------------------------------------------------------------------------

target=powerpc-apple-darwin8

#---------------------------------------------------------------------------------
# Source and Install directories
#---------------------------------------------------------------------------------

SRCDIR=./../../cctools               # the source code dir for cctools
prefix=~/cctools-port/$target        # installation directory

#---------------------------------------------------------------------------------
# set compiler flags
#---------------------------------------------------------------------------------


WARNINGS="-D_GNU_SOURCE -fcommon -Wno-deprecated -Wno-attributes -Wno-maybe-uninitialized -Wno-narrowing -Wno-int-conversion -Wno-address -Wall -Wno-implicit-function-declaration -Wno-format -Wno-enum-compare -Wno-unused-result -Wno-unused-variable -Wno-unused-but-set-variable -Wno-deprecated -Wno-deprecated-declarations -Wno-char-subscripts -Wno-strict-aliasing -Wno-shift-negative-value -Wno-misleading-indentation -Wno-stringop-truncation -Wno-pointer-sign -Wno-parentheses"

export CFLAGS="-O2 $WARNINGS"
export CXXFLAGS="-O2 $WARNINGS"
export LDFLAGS='-s'
export DEBUG_FLAGS=''

#---------------------------------------------------------------------------------
# Build and install cctools
#---------------------------------------------------------------------------------
REALDIR=$(readlink -f $SRCDIR)


cd $REALDIR
make clean 2>&1

mkdir -p cctools-build/$target
cd cctools-build/$target

$REALDIR/configure --prefix=$prefix --target=$target \
    --enable-ld64 \
    2>&1 | tee cctools_configure.log


make 2>&1 | tee cctools_make.log
make install 2>&1 | tee cctools_install.log
