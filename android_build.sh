#!/bin/bash

. settings.sh

BASEDIR=$(pwd)
TOOLCHAIN_PREFIX=${BASEDIR}/toolchain-android

# $1 architecture
# $2 base directory
# $3 pass 1 if export default compiler environment variables
#rm -rf ${TOOLCHAIN_PREFIX}
#./fdk_aac_build.sh $ARCHITECTURES $BASEDIR 1 || exit 1
#./x264_build.sh $ARCHITECTURES $BASEDIR 1 || exit 1
./ffmpeg_build.sh $ARCHITECTURES $BASEDIR 0 || exit 1
#./live555_build.sh $ARCHITECTURES $BASEDIR 0 || exit 1

#rm -rf ${TOOLCHAIN_PREFIX}
