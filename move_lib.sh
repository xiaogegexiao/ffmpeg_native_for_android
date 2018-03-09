cp build/armeabi-v7a-neon/lib/*.a ../library/src/main/jniLibs/armeabi-v7a/
cp -r build/armeabi-v7a-neon/include/* ../library/src/main/cpp/include/ffmpeg/
#cp toolchain-android/lib/libfdk-aac.a ../library/src/main/jniLibs/armeabi-v7a/
cp toolchain-android/lib/libx264.a ../library/src/main/jniLibs/armeabi-v7a/
cp ffmpeg/config.h ../library/src/main/cpp/include/ffmpeg/config.h

#live555
cp toolchain-android/lib/libUsageEnvironment.a ../library/src/main/jniLibs/armeabi-v7a/
cp toolchain-android/lib/libBasicUsageEnvironment.a ../library/src/main/jniLibs/armeabi-v7a/
cp toolchain-android/lib/libgroupsock.a ../library/src/main/jniLibs/armeabi-v7a/
cp toolchain-android/lib/libliveMedia.a ../library/src/main/jniLibs/armeabi-v7a/

cp -r toolchain-android/include/BasicUsageEnvironment ../library/src/main/cpp/include/live555/
cp -r toolchain-android/include/UsageEnvironment ../library/src/main/cpp/include/live555/
cp -r toolchain-android/include/groupsock ../library/src/main/cpp/include/live555/
cp -r toolchain-android/include/liveMedia ../library/src/main/cpp/include/live555/
