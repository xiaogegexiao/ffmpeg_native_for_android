#!/bin/bash

ARCHITECTURES=armeabi-v7a-neon
ANDROID_NDK_ROOT_PATH=${ANDROID_NDK}

if [[ -z "$ANDROID_NDK_ROOT_PATH" ]]; then
    echo "Error: You need to set ANDROID_NDK environment variable"
    exit
fi

ANDROID_API_VERSION=21
NDK_TOOLCHAIN_ABI_VERSION=4.9

NUMBER_OF_CORES=$(sysctl -n hw.ncpu)
HOST_UNAME=$(uname -m)
TARGET_OS=linux
OPENSSL_DIR=$(pwd)/openssl-1.0.2

CFLAGS='-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2 -fno-strict-overflow -fstack-protector-all'
LDFLAGS='-Wl,-z,relro -Wl,-z,now -pie'

FFMPEG_PKG_CONFIG="$(pwd)/ffmpeg-pkg-config"
