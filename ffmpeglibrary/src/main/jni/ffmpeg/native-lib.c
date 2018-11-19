#include <jni.h>

//ffmpeg库
#include "libavformat/avformat.h"
//打印日志
#include <android/log.h>


#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"ywl5320",FORMAT,##__VA_ARGS__);

//typedef struct UserInfo user;



JNIEXPORT void JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_test(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = (*env)->GetStringUTFChars(env, str_, 0);

//    int result=avpriv_io_delete(str);

    av_log(NULL,AV_LOG_INFO,"路径:%s",str);
//    av_log(NULL,AV_LOG_INFO,"删除结果:%2d",result);

    (*env)->ReleaseStringUTFChars(env, str_, str);
}

