//
// Created by alick on 2018/11/26.
//
#include "lib_utils.h"


JNIEXPORT jstring JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_executeImoocDemo(JNIEnv *env, jobject instance,
                                                           jstring srcFilePath_,
                                                           jstring dstFilePath_) {
    //1.获取源文件和存放目标文件路径
    const char *srcFilePath = (*env)->GetStringUTFChars(env, srcFilePath_, 0);
    const char *dstFilePath = (*env)->GetStringUTFChars(env, dstFilePath_, 0);

    char *endResult = NULL;
    AVPacket *pkt = NULL;
    int len;

    av_register_all();
    avcodec_register_all();

    AVFormatContext *fmt_ctx = NULL;

    int audio_stream_index=-1;

    int result = avformat_open_input(&fmt_ctx, srcFilePath, 0, 0);

    if (result != 0) {
        LOGE("打开文件失败:%s", av_err2str(result));
        return (*env)->NewStringUTF(env, buildStr("打开文件失败:%s", av_err2str(result)));
    }

    LOGI("打开源文件成功:%s", srcFilePath);

    int videoStreamIndex = 0;

    FILE *dstFILE = fopen(dstFilePath, "wb");

    if (dstFILE == NULL) {
        LOGE("不能打开输出文件:%s", dstFilePath);
        endResult = buildStr("不能打开输出文件:", (char *) dstFilePath);
        goto end;
    }
    LOGI("打开输出文件成功:%s", dstFilePath);

    av_dump_format(fmt_ctx, 0, srcFilePath, 0);

    //2.获取音频流
    result = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);


    if (result < 0) {
        LOGE("获取音频流失败:%s", av_err2str(result));
        endResult = buildStr("获取音频流失败", av_err2str(result));
        goto end;
    }

    audio_stream_index=result;
    LOGI("获取音频流成功,索引为:%d", audio_stream_index);

    av_init_packet(&pkt);

    //3.将音频数据写入到aac文件中
    while (av_read_frame(fmt_ctx, &pkt)>=0){
        if(pkt->stream_index==audio_stream_index){
            //为啥if里面从来不会被执行???
            len=fwrite(pkt->data, 1, (size_t) pkt->size, dstFILE);//其中参数1代表每个元素1字节
            if(len!=pkt->size){
                LOGW("读取音频长度不一致,len=%d,pkt.size=%d",len,pkt->size);
            }
        }
        av_packet_unref(&pkt);
    }

    endResult="写入成功";
    LOGI(endResult,"");

    end:

    avformat_close_input(&fmt_ctx);

    //关闭目标(输出)文件
    if(dstFILE){
        fclose(dstFILE);
    }

    (*env)->ReleaseStringUTFChars(env, srcFilePath_, srcFilePath);
    (*env)->ReleaseStringUTFChars(env, dstFilePath_, dstFilePath);

    return (*env)->NewStringUTF(env, endResult);
}
