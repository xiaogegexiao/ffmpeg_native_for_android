#!/bin/sh
pushd ffmpeg

current_time=$(date "+%Y.%m.%d-%H.%M.%S")
echo $current_time
hlsfilename=$"hlsenc-"$current_time$".patch"
echo $hlsfilename
git diff > ../patch/$hlsfilename
