#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DESTDIR=$DIR/../wk.unix/bin/release
make clean
make
cp $DIR/dbServer $DESTDIR/dbServer
make clean