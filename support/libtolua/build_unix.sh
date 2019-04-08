#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DESTDIR=$DIR/../../wk.unix/bin/release/lib

make clean
make
cp $DIR/libtolua.a $DESTDIR/libtolua.a
make clean
