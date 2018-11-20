package com.alick.ffmpeglibrary;

public class FFmpegPlayer {
    static {
        System.loadLibrary("avcodec-57");
        System.loadLibrary("avfilter-6");
        System.loadLibrary("avformat-57");
        System.loadLibrary("avutil-55");
        System.loadLibrary("swresample-2");
        System.loadLibrary("swscale-4");
        System.loadLibrary("cxw_ffmpeg");

//        System.loadLibrary("postproc-54");
//        System.loadLibrary("avdevice-57");
    }

    public native void playMyMedia(String url);

    public native void test(String str);

    public native void test2(String str);

    public native void read(String filePath);

}