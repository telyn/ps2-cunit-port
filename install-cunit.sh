#!/bin/bash
set -eo pipefail

wget -O cunit.tar.gz https://sourceforge.net/projects/cunit/files/latest/download
tar xf cunit.tar.gz
cd CUnit*

autoreconf -i
./configure --prefix="$PS2DEV" --host=mips64r5900el CC=ee-gcc AR=ee-ar RANLIB=ee-ranlib
