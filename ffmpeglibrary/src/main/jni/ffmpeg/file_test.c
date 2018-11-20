//
// Created by alick on 2018/11/20.
//
#include <jni.h>
#include <libavformat/avformat.h>
#include <libavutil/log.h>
#include <android/log.h>

#define TAG "alick" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

JNIEXPORT void JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_read(JNIEnv *env, jobject instance, jstring filePath_) {

    av_register_all();

    const char *filePath = (*env)->GetStringUTFChars(env, filePath_, 0);

    AVFormatContext *pFormatCtx = avformat_alloc_context();
    int open_input = avformat_open_input(&pFormatCtx, filePath, NULL, NULL);
    LOGI("打开文件结果码:%2d,错误信息:", open_input, av_err2str(open_input));
    if (open_input != 0) {
        char buf[1024];
        av_strerror(open_input, buf, 1024);
        LOGE("Couldn't open file :(%s)", buf);
        LOGE("打开失败");
    } else {
        LOGI("文件信息");
        av_dump_format(pFormatCtx, 0, filePath, 0);
        LOGI("--------------------------------");

        int videoindex = -1;
        int i = 0;
        for (i = 0; i < pFormatCtx->nb_streams; i++){
            if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
                videoindex = i;
                break;
            }
        }

        AVDictionaryEntry *tag = NULL;

        tag=av_dict_get(pFormatCtx->streams[videoindex]->metadata,"rotate",tag,0);//注意    当视频中有这个信息的时候才会有返回，否则返回NULL
        if (tag!=NULL){
            int arg=atoi(tag->value);//将字符转成int类型
            LOGI("角度:%2d",arg);
        }else{
            LOGE("tag==NULL \n");
        }


        avformat_close_input(&pFormatCtx);
    }

    (*env)->
            ReleaseStringUTFChars(env, filePath_, filePath
    );
}