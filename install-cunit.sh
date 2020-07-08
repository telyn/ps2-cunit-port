#!/bin/bash
set -eo pipefail

wget -O cunit.tar.gz https://sourceforge.net/projects/cunit/files/latest/download
tar xf cunit.tar.gz
cd CUnit*

echo "running autoreconf -i (CUnit's package maintainer should have done this >:-( )"
autoreconf -i
echo "Configuring for EE build"
./configure --prefix="$PS2DEV/ee" --host=mips64r5900el CC=ee-gcc AR=ee-ar RANLIB=ee-ranlib
echo "Building & installing to $PS2DEV/ee"
make install
echo "Cleaning up to prepare for IOP build"
make clean

echo "Modifying libtool for IOP"
sed -i -e 's/ee\//iop\//g' -e 's/ee-/iop-/g' -e 's/mips64r5900el/mipsel-scei' libtool
echo "Building & installing for IOP"
make CC=iop-gcc LD=iop-ld AR=iop-ar ac_ct_AR=iop-ar RANLIB=iop-ranlib
