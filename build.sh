#!/bin/bash

export ROOT_PATH=`pwd`
export LIBUSB_PATH=$ROOT_PATH/libusb
export LIBUSB_ABDROID_JNI=$LIBUSB_PATH/android/jni
export LIBUSB_ANDROID_OUT=$LIBUSB_PATH/android/libs/arm64-v8a
export SOURCES=$ROOT_PATH/sources
export SOURCES_OUT=$SOURCES/out
export PATH=$NDK_PATH/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin:$PATH

case $1 in 
	"libusb")
		cd $LIBUSB_ABDROID_JNI; ndk-build -j4
		cd $ROOT_PATH
esac
case $1 in 
	"sources")
		cd $SOURCES; make -j4
		cd $ROOT_PATH
esac
case $1 in 
	"all")
		cd $LIBUSB_ABDROID_JNI; ndk-build -j4
		cd $SOURCES; make -j4
		cd $ROOT_PATH
esac
case $1 in 
	"clean_libusb")
		cd $LIBUSB_ABDROID_JNI; ndk-build clean >/dev/null
		cd $ROOT_PATH
esac
case $1 in 
	"clean_sources")
		cd $SOURCES; make clean >/dev/null
		cd $ROOT_PATH
esac
case $1 in 
	"clean")
		cd $LIBUSB_ABDROID_JNI; ndk-build clean >/dev/null
		cd $SOURCES; make clean >/dev/null
		rm -rf $ROOT_PATH/out >/dev/null
		cd $ROOT_PATH
esac
case $1 in 
	"pack")
		if [ ! -f "$LIBUSB_ANDROID_OUT/libusb1.0.so" ]; then
			echo "Cannot find libusb1.0.so"
			exit
		fi
		if [ ! -f "$SOURCES_OUT/main" ]; then
			echo "Cannot find main"
			exit
		fi
		mkdir -p out
		cp $LIBUSB_ANDROID_OUT/libusb1.0.so ./out/
		cp $SOURCES_OUT/main ./out/
		adb push ./out/ /data/
		rm -rf ./out
esac
