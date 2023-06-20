LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_CPP_EXTENSION := .cpp .cc
LOCAL_MODULE    := DebugInfo.SA
LOCAL_SRC_FILES := main.cpp
LOCAL_CFLAGS += -O2 -mfloat-abi=softfp -DNDEBUG -std=c++17
LOCAL_LDLIBS += -llog
include $(BUILD_SHARED_LIBRARY)