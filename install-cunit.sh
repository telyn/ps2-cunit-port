#!/bin/bash
set -eo pipefail

PS2CUNIT=$PWD
DL=0
CONFIG=1
EE=1
IOP=1

if [ $DL -eq 1 ]; then
    wget -O cunit.tar.gz https://sourceforge.net/projects/cunit/files/latest/download
    tar xf cunit.tar.gz
fi

cd CUnit*
if [ $CONFIG -eq 1 ]; then
    echo "running autoreconf -i (CUnit's package maintainer should have done this >:-( )"
    autoreconf -i
    echo "Configuring for EE build"
    ./configure --prefix="$PS2DEV/ee" --host=mips64r5900el CC=ee-gcc AR=ee-ar RANLIB=ee-ranlib
fi


if [ $EE -eq 1 ]; then
    echo "Building & installing to $PS2DEV/ee"
    make install
    echo "Cleaning up to prepare for IOP build"
    make clean
fi

if [ "$IOP" -eq 1 ]; then
    # using the ee binaries to perform the configure, since iop-gcc fails
    # configure checks. Just need PREFIX swapped, anyway, so should delete this
    # to save time later
    ./configure --enable-automated=no --enable-console=no --prefix="$PS2DEV/iop" --host=mips64r5900el CC=ee-gcc AR=ee-ar RANLIB=ee-ranlib
    echo "make libtool"
    make libtool
    echo "Modifying libtool for IOP"
    sed -i'.bak' -e 's/ee\//iop\//g' -e 's/ee-/iop-/g' -e 's/mips64r5900el/mipsel-scei/' libtool
    echo "Building & installing for IOP"
    make install CC=iop-gcc LD=iop-ld AR=iop-ar ac_ct_AR=iop-ar RANLIB=iop-ranlib CFLAGS="-miop -nostdlib -D_IOP -DRELEASE=@RELEASE@ -Wall -W -pedantic -Wshadow -I/Users/telyn/Code/CUnit-2.1-3/CUnit/Headers -std=c99 -I$PS2SDK/iop/include -I$PS2SDK/common/include -I$PS2CUNIT/include" LDFLAGS="-nostdlib -static"
fi
