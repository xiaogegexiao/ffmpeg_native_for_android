#!/bin/bash

. abi_settings.sh $1 $2 $3

pushd live
make clean

./genMakefiles android
make || exit 1
make install || exit 1

popd
