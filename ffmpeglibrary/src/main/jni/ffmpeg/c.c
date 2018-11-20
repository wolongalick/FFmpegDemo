//
// Created by alick on 2018/11/20.
//
#include <jni.h>
#include <stdio.h>

#include <android/log.h>
#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"ywl5320",FORMAT,##__VA_ARGS__);

JNIEXPORT void JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_test2(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = (*env)->GetStringUTFChars(env, str_, 0);

    LOGI("test2内容:%s",str);

    (*env)->ReleaseStringUTFChars(env, str_, str);
}

