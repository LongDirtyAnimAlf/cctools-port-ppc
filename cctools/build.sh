#!/usr/bin/env bash

export TARGET=powerpc-apple-darwin8

export PREFIX=/usr

WARNINGS="-Wno-deprecated -Wno-attributes -Wno-maybe-uninitialized -Wno-narrowing -Wno-int-conversion -Wno-address -Wall -Wno-implicit-function-declaration -Wno-format -Wno-enum-compare -Wno-unused-result -Wno-unused-variable -Wno-unused-but-set-variable -Wno-deprecated -Wno-deprecated-declarations -Wno-char-subscripts -Wno-strict-aliasing -Wno-shift-negative-value"

make clean

CC="gcc -m32" CXX="g++ -m32" LDFLAGS="-m32" CFLAGS=$WARNINGS ./configure --prefix=$PREFIX/usr --target=$TARGET --enable-ld64

make -j3
make install -j3 DESTDIR=~/build/$TARGET
