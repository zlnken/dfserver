#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SRCDIR=$DIR/src
DESTDIR=$DIR/../../wk.unix/bin/release/lib
#MACOSX_DEPLOYMENT_TARGET="10.6"
cd $SRCDIR
make clean
make DEFAULT_CC=gcc HOST_CC="gcc -m64 -arch x86_64" clean all

cp $SRCDIR/libluajit.a $DESTDIR/libluajit.a

make clean
#-pagezero_size 10000 -image_base 100000000