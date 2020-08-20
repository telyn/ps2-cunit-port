#!/bin/bash
set -eo pipefail

PS2CUNIT=$PWD
DL=1
CONFIG=1
EE=1
IOP=1
DOC=1

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
    make clean  || true
    make distclean || true
    echo "Building & installing to $PS2DEV/ee"
    make install
fi

if [ "$IOP" -eq 1 ]; then
    make clean || true
    make distclean || true
    # using the ee binaries to perform the configure, since iop-gcc fails
    # configure checks. Just need PREFIX swapped, anyway, so should delete this
    # to save time later
    ./configure --enable-automated=no --enable-console=no --prefix="$PS2DEV/iop" --host=mips64r5900el CC=ee-gcc AR=ee-ar RANLIB=ee-ranlib
    echo "make libtool"
    make libtool
    echo "Modifying libtool for IOP"
    sed -i'.bak' -e 's/ee\//iop\//g' -e 's/ee-/iop-/g' -e 's/mips64r5900el/mipsel-scei/' libtool
    echo "Building & installing for IOP"
    make install CC=iop-gcc LD=iop-ld AR=iop-ar ac_ct_AR=iop-ar RANLIB=iop-ranlib CFLAGS="-miop -nostdlib -D_IOP -DRELEASE=@RELEASE@ -Wall -W -pedantic -Wshadow -I'$PWD/CUnit/headers' -std=c99 -I'$PS2SDK/iop/include' -I'$PS2SDK/common/include' -I'$PS2CUNIT/include'" LDFLAGS="-nostdlib -static"

    echo "Removing math.h include from CUnit.h"
    sed -i'.math' -e '/#include.*math\.h/d' "$PS2DEV/iop/include/CUnit/CUnit.h"

    echo "Compiling port compatibility library"
    make libps2_cunit.a
    make libcunit.a
    cp libcunit.a $PS2DEV/iop/lib/cunit.a
fi


if [ $DOC -eq 1 ]; then
    cat <<HERE
CUnit is now installed for EE & IOP in \$PS2DEV/ee and \$PS2DEV/iop

EE instructions:
  Compiling against and running the EE version follows the same procedure as
  any other CUnit test program - no special steps are required beyond the
  normal for compiling a PS2 program (i.e.  using ee-gcc) and adding -lcunit to
  your link.

IOP instructions:
  Please see the README for ps2-cunit-port for information on how to compile
  and run a test program for the IOP.
  The tl;dr is that there's a fair few imports needed
  (see iop-test/iop-imports.c), and if running via ps2link the alloc.irx from
  \$PS2SDK/iop/irx needs to be loaded first, like in the following:

      cd \$PS2SDK/iop/irx
      ps2client execiop host:alloc.irx

  Please feel free to open an issue at github.com/telyn/ps2-cunit-port if you
  can't get it running. Pull requests are welcome too :-)
HERE
fi
