//
// Created by alick on 2018/11/26.
//
#include <stdio.h>
#include <jni.h>
#include <libavformat/avformat.h>

JNIEXPORT jstring JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_executeImoocDemo(JNIEnv *env, jobject instance,
                                                           jstring s_) {
    const char *s = (*env)->GetStringUTFChars(env, s_, 0);

    // TODO

    AVFormatContext *fmt_ctx=NULL;





    (*env)->ReleaseStringUTFChars(env, s_, s);

    return (*env)->NewStringUTF(env, "滚滚滚");
}