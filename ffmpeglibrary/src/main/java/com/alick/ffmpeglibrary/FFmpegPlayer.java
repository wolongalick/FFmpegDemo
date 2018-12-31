package com.alick.ffmpeglibrary;

public class FFmpegPlayer {
    static {
        System.loadLibrary("avcodec");
        System.loadLibrary("avfilter");
        System.loadLibrary("avformat");
        System.loadLibrary("avutil");
        System.loadLibrary("swresample");
        System.loadLibrary("swscale");
        System.loadLibrary("cxw_ffmpeg");

//        System.loadLibrary("postproc");
//        System.loadLibrary("avdevice");
    }

    public native void playMyMedia(String url);

    public native void test(String str);

    public native void test2(String str);

    public native void read(String filePath);

    public native String getFFmpegConfigInfo();

    public native String readFileContent(String filePath);

    public native String readVideoFileInfo(String filePath);

    public native String readVideoFileInfo2(String filePath);

    public native String executeImoocDemo(String srcFilePath,String dstFilePath);
}