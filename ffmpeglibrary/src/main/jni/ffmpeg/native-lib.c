#include <jni.h>

//ffmpeg库
#include "libavformat/avformat.h"
#include <libavutil/log.h>
//打印日志
#include <android/log.h>
#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"ywl5320",FORMAT,##__VA_ARGS__);

//typedef struct UserInfo user;

JNIEXPORT void JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_test(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = (*env)->GetStringUTFChars(env, str_, 0);

    LOGI("路径:%s",str);
    int result=avpriv_io_delete(str_);

    LOGI("删除结果:%2s",av_err2str(result));

    AVIODirContext *ctx=NULL;


    int result2=avio_open_dir(&ctx,str_,NULL);

    if(result2<0){
        LOGI("打开失败,result=%2s",av_err2str(result2));
    }


    (*env)->ReleaseStringUTFChars(env, str_, str);
}

