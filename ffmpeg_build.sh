#!/bin/bash

. abi_settings.sh $1 $2 $3

if [ ! -d ffmpeg ]; then
    git clone https://github.com/FFmpeg/FFmpeg.git ffmpeg
    pushd ffmpeg
    git checkout `cat ../commit.txt`
    popd
fi

pushd ffmpeg

CPU='cortex-a8'

echo "ls ${OPENSSL_DIR}/armeabi-v7a/lib"

make clean

echo $OPENSSL_DIR
echo $TOOLCHAIN_PREFIX

./configure \
--target-os="$TARGET_OS" \
--cross-prefix="$CROSS_PREFIX" \
--arch="$NDK_ABI" \
--cpu="$CPU" \
--disable-decoders \
--disable-encoders \
--disable-muxers \
--disable-filters \
--disable-doc \
--disable-ffplay \
--disable-ffprobe \
--disable-ffserver \
--disable-debug \
--disable-shared \
--disable-demuxers \
--enable-decoder=pcm_mulaw \
--enable-decoder=h264 \
--enable-decoder=aac \
--enable-decoder=mjpeg \
--enable-decoder=pcm_s8 \
--enable-decoder=pcm_u8 \
--enable-decoder=pcm_s16le \
--enable-decoder=pcm_s16be \
--enable-decoder=pcm_u16le \
--enable-decoder=pcm_u16be \
--enable-encoder=h264 \
--enable-encoder=aac \
--enable-encoder=mjpeg \
--enable-muxer=hls \
--enable-muxer=h264 \
--enable-muxer=rtsp \
--enable-muxer=mjpeg \
--enable-muxer=image2 \
--enable-muxer=aac \
--enable-demuxer=hls \
--enable-demuxer=h264 \
--enable-demuxer=mjpeg \
--enable-demuxer=image2 \
--enable-demuxer=pcm_mulaw \
--enable-demuxer=rtsp \
--enable-demuxer=concat \
--enable-demuxer=pcm_s8 \
--enable-demuxer=pcm_u8 \
--enable-demuxer=pcm_s16le \
--enable-demuxer=pcm_s16be \
--enable-demuxer=pcm_u16le \
--enable-demuxer=pcm_u16be \
--enable-demuxer=foscam \
--enable-demuxer=foscam_s16le \
--enable-demuxer=hevc \
--enable-demuxer=aac \
--enable-filter=scale \
--enable-filter=fps \
--enable-filter=aresample \
--enable-runtime-cpudetect \
--sysroot="$NDK_SYSROOT" \
--enable-pic \
--enable-pthreads \
--enable-version3 \
--enable-hardcoded-tables \
--enable-gpl \
--enable-yasm \
--enable-neon \
--enable-thumb \
--enable-nonfree \
--enable-static \
--enable-openssl \
--enable-protocol=tls_openssl \
--pkg-config="${2}/ffmpeg-pkg-config" \
--prefix="${2}/build/${1}" \
--extra-cflags="-I${TOOLCHAIN_PREFIX}/include -I${OPENSSL_DIR}/include $CFLAGS" \
--extra-ldflags="$LDFLAGS -L${TOOLCHAIN_PREFIX}/lib -L${OPENSSL_DIR}/lib -lssl -lcrypto" \
--extra-cxxflags="$CXX_FLAGS" || exit 1

make -j${NUMBER_OF_CORES} && make install || exit 1

popd
