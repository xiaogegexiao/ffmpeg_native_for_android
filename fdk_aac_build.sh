#!/bin/bash

. abi_settings.sh $1 $2 $3

pushd fdk-aac-0.1.4

make clean

autoreconf -fiv

./configure \
    --with-pic \
    --with-sysroot="$NDK_SYSROOT" \
    --host="$NDK_TOOLCHAIN_ABI" \
    --enable-static \
    --disable-shared \
    --disable-libtool-lock \
    --disable-fast-install \
    --prefix="${TOOLCHAIN_PREFIX}" || exit 1

make -j${NUMBER_OF_CROES} && make install || exit 1

popd
