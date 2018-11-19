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

    int ret;
    //1.定义格式上下文（容器）指针变量
    AVFormatContext *fmt_ctx = NULL;
    av_log_set_level(AV_LOG_INFO);
    //2.注册音视频全局解码器
    av_register_all();
    // 3.打开多媒体文件,注意第一个参数为指针变量的地址，而不是上下文容器 fmt_ctx 指向的上下文所存储的内存地址 //参数含义:[指向fmt_ctx指针变量的地址,要打开的视频文件,文件格式-无值程序会根据视频文件类型后缀自动识别,命令行参数]
    ret = avformat_open_input(&fmt_ctx, "test.mp4", NULL, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Can't open file: %s\n", av_err2str(ret));
//        return -1;
    }
    //4.［上下文指针,index 默认值为0,文件src,0表示输入类型文件｜输出流则为1］
    av_dump_format(fmt_ctx, 0, "./test.mp4", 0);
    //5.关闭格式上下文，注意可以从格式上下文中可以获取到对应的AVStream
    avformat_close_input(&fmt_ctx);


    (*env)->ReleaseStringUTFChars(env, str_, str);
}

