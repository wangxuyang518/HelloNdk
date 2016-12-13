LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := hello-jni

LOCAL_SRC_FILES    := base64.c
include $(BUILD_SHARED_LIBRARY)