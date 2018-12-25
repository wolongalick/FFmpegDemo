//
// Created by alick on 2018/11/27.
//

#ifndef FFMPEGDEMO_LIB_UTILS_H
#define FFMPEGDEMO_LIB_UTILS_H


#include <jni.h>
#include <libavformat/avformat.h>
#include <libavutil/log.h>
#include <android/log.h>
#include <libavcodec/avcodec.h>
#include <stdio.h>


#define TAG "alick" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型


char *buildStr(char *str1,char *str2);


#endif //FFMPEGDEMO_LIB_UTILS_H
