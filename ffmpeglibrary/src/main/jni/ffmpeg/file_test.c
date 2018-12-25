//
// Created by alick on 2018/11/20.
//
#include <jni.h>
#include <libavformat/avformat.h>
#include <libavutil/log.h>
#include <android/log.h>
#include <libavcodec/avcodec.h>
#include <stdio.h>
#include "lib_utils.h"


static double r2d(AVRational avRational) {
    return avRational.num == 0 || avRational.den == 0 ? 0.0 : ((double) avRational.num) /
                                                              ((double) avRational.den);
}


JNIEXPORT void JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_read(JNIEnv *env, jobject instance, jstring filePath_) {

    av_register_all();

    const char *filePath = (*env)->GetStringUTFChars(env, filePath_, 0);

    AVFormatContext *pFormatCtx = avformat_alloc_context();
    int open_input = avformat_open_input(&pFormatCtx, filePath, 0, 0);

    LOGI("打开文件结果码:%2d,错误信息:%s", open_input, av_err2str(open_input));
    if (open_input != 0) {
        char buf[1024];
        av_strerror(open_input, buf, 1024);
        LOGE("Couldn't open file :(%s)", buf);
        LOGE("打开失败");
    } else {
        LOGI("文件信息");
        av_dump_format(pFormatCtx, 0, filePath, 0);
        LOGI("--------------------------------");

        /*int videoindex = -1;
        int i = 0;
        for (i = 0; i < pFormatCtx->nb_streams; i++){
            if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
                videoindex = i;
                break;
            }
        }*/

        avformat_close_input(&pFormatCtx);
    }

    (*env)->ReleaseStringUTFChars(env, filePath_, filePath);
}

JNIEXPORT jstring JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_getFFmpegConfigInfo(JNIEnv *env, jobject instance) {
    return (*env)->NewStringUTF(env, avcodec_configuration());
}

JNIEXPORT jstring JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_readFileContent(JNIEnv *env, jobject instance,
                                                          jstring filePath_) {
    const char *filePath = (*env)->GetStringUTFChars(env, filePath_, 0);

    FILE *pFILE = fopen(filePath, "r");

    if (pFILE == NULL) {
        LOGE("打开文件失败");
        return NULL;
    }

    const int size = 1024;
    char buf[size] = "\0";
    int len = 0;
    int i = 0;
    while (fgets(buf, size, pFILE) != NULL) {
        len = strlen(buf);
        buf[len - 1] = '\0';
        LOGI("%s %d \n", buf, len - 1);
    }

    fclose(pFILE);


    (*env)->ReleaseStringUTFChars(env, filePath_, filePath);

    return (*env)->NewStringUTF(env, filePath);
}

JNIEXPORT jstring JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_readVideoFileInfo(JNIEnv *env, jobject instance,
                                                            jstring filePath_) {
    const char *filePath = (*env)->GetStringUTFChars(env, filePath_, 0);

    avcodec_register_all();

    AVFormatContext *avFormatContext = NULL;
    int result = avformat_open_input(&avFormatContext, filePath, 0, 0);

    if (result != 0) {
        char *str = NULL;
        LOGE("打开视频文件失败%s", av_err2str(result));
        return NULL;
    }

    char *info = "视频信息:\n";
    char *duationStr = "视频时长";
    int64_t duration = (avFormatContext->duration) / 1000000;
    char *second = "秒\n";

    char *streamsStr = "流的个数:";
    int streamNumber = avFormatContext->nb_streams;
    char *number = "个\n";

    char buff1[100];
    sprintf(buff1, "%s%s%lld%s%s%d%s", info, duationStr, duration, second, streamsStr,
            streamNumber, number);

    char *string=NULL;
    for (int i = 0; i < streamNumber; ++i) {
        AVStream *pStream = avFormatContext->streams[i];
        enum AVMediaType type = pStream->codecpar->codec_type;
        int width = 0;
        char *str;
        if(type==AVMEDIA_TYPE_VIDEO){
            double fps = r2d(pStream->avg_frame_rate);
            int width = pStream->codecpar->width;
            int height = pStream->codecpar->height;
            enum AVCodecID codecID = pStream->codecpar->codec_id;
            char buff2[100];
            sprintf(buff2,"fps:%f,宽:%d,编码器ID:%d,高:%d\n",fps,width,height,codecID);
            LOGI("buff2:%s",buff2);
            string= (char *)malloc(strlen(buff1) + strlen(buff2));

            strcpy(string,buff1);
            strcat(string,buff2);

        } else if(type==AVMEDIA_TYPE_AUDIO){
            int sample_rate = pStream->codecpar->sample_rate;
            int channels = pStream->codecpar->channels;
            int format = pStream->codecpar->format;
            char buf3[100];
            sprintf(buf3,"采样率:%d,频道个数:%d,格式:%d\n",sample_rate,channels,format);
            strcat(string,buf3);
//            malloc(strlen(string))
//            string="音频";
        }
    }


    //关闭文件流
    avformat_close_input(&avFormatContext);

    return (*env)->NewStringUTF(env, string);
}




JNIEXPORT jstring JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_readVideoFileInfo2(JNIEnv *env, jobject instance,
                                                             jstring filePath_) {
    const char *filePath = (*env)->GetStringUTFChars(env, filePath_, 0);

    av_register_all();

    avformat_network_init();

    avcodec_register_all();

    AVFormatContext *pAVFormatContext = avformat_alloc_context();

    int open_input = avformat_open_input(&pAVFormatContext, filePath, 0, 0);
    char *string=NULL;
    if(open_input==0){
        string=buildStr("打开文件成功:",filePath);
    } else{
        char *s1="打开文件失败:";
        char *error=av_err2str(open_input);
        string=malloc(strlen(s1)+strlen(error));

        sprintf(string,"%s%s",s1,error);

        LOGE(string,"eeewwwwwww");
        (*env)->ReleaseStringUTFChars(env, filePath_, filePath);

        return (*env)->NewStringUTF(env,string);
    }

    //
    int audioStream = av_find_best_stream(pAVFormatContext, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);

    int videoStream=0;
    int streams = pAVFormatContext->nb_streams;
    for (int i = 0; i < streams; ++i) {
        AVStream *pStream = pAVFormatContext->streams[i];
        if(pStream->codecpar->codec_type==AVMEDIA_TYPE_VIDEO){
            videoStream=i;
        }
    }

    //取出软解码器
    AVCodecParameters *avCodecParameters = pAVFormatContext->streams[videoStream]->codecpar;
    AVCodec *avCodec=avcodec_find_decoder(avCodecParameters->codec_id);

    //取出硬解码器
//    avCodec=avcodec_find_decoder_by_name("h264_mediacodec");

    if(!avCodec){
        //释放jni的字符串
        (*env)->ReleaseStringUTFChars(env, filePath_, filePath);
        return (*env)->NewStringUTF(env, "查找解码器失败");
    }

    AVCodecContext *avCodecContext=avcodec_alloc_context3(avCodec);
    //将stream流中的参数拷贝到avCodecParameters中
    avcodec_parameters_to_context(avCodecContext,avCodecParameters);
    avCodecContext->thread_count=1;


    //打开解码器
    int result_codec_open = avcodec_open2(avCodecContext, NULL, NULL);
    if(result_codec_open!=0){
        //释放jni的字符串
        (*env)->ReleaseStringUTFChars(env, filePath_, filePath);
        return (*env)->NewStringUTF(env, "打开解码器失败");
    }

    AVPacket *pPacket = av_packet_alloc();

    AVFrame *avFrame=av_frame_alloc();


    for(;;){
        int result = av_read_frame(pAVFormatContext, pPacket);

        if(result!=0){
            LOGI("读到结尾处!");

            int pos = 3 * r2d(pAVFormatContext->streams[videoStream]->time_base);

            //从视频流的中间部分向后查找关键帧
            av_seek_frame(pAVFormatContext,videoStream,pos,AVSEEK_FLAG_BACKWARD|AVSEEK_FLAG_FRAME);
            continue;
        }

        //非适配流则不做任何处理
        if(pPacket->stream_index!=videoStream){
            continue;
        }

//        LOGI("stream=%d size=%d pts=%lld flag=%d",
//             pPacket->stream_index,pPacket->size,pPacket->pts,pPacket->flags
//        );
        AVCodecContext *cc=avCodecContext;
        if(pPacket->stream_index==audioStream){
            cc=avCodecContext;
        }

        //发送到线程中解码
        result=avcodec_send_packet(avCodecContext,pPacket);

        if(result!=0 ){
            LOGE("avcodec_send_packet失败:",av_err2str(result));
            continue;
        }

        result=avcodec_receive_frame(avCodecContext,avFrame);

        if(result!=0){
            LOGE("avcodec_receive_frame失败:",av_err2str(result));
        }

        LOGI("avcodec_receive_frame成功:%lld",avFrame->pts);




        av_packet_unref(pPacket);
    }

    avformat_close_input(&pAVFormatContext);

    //释放jni的字符串
    (*env)->ReleaseStringUTFChars(env, filePath_, filePath);

    return (*env)->NewStringUTF(env, string);
}

