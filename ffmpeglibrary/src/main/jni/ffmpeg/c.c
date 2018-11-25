//
// Created by alick on 2018/11/20.
//
#include <jni.h>
#include <stdio.h>

#include <android/log.h>
#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"ywl5320",FORMAT,##__VA_ARGS__);

void swap1(int a, int b);
void swap2(int *a, int *b);



JNIEXPORT void JNICALL
Java_com_alick_ffmpeglibrary_FFmpegPlayer_test2(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = (*env)->GetStringUTFChars(env, str_, 0);

    int num=1024;
    int *p_num;
    p_num=&num;//取变量num的地址附给指针p_num
    LOGI("初始num=%d",num);
    num=1111;
    LOGI("*p_num=%d",*p_num);//*p_num值为1111
    *p_num=2048;//给指针的值进行赋值
    LOGI("num=%d",num);//num值为2048

    /**
     * 打印结果
     * num=1024
     * p_num=1111
     * num=2048
     * 交换前:a=1,b=2
     */

    /**
     * 结论:
     * 1.修改num的值,会影响指针p_num对应的值
     * 2.修改指针p_num对应的值,也会影响num的值
     */

    int a=1;
    int b=2;

    LOGI("交换前:a=%d,b=%d",a,b);
    swap2(&a, &b);
    LOGI("交换后:a=%d,b=%d",a,b);

    (*env)->ReleaseStringUTFChars(env, str_, str);
}

void swap1(int a, int b){
    int tmp=a;
    a=b;
    b=tmp;
}

void swap2(int *a, int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}