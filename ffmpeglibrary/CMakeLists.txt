cmake_minimum_required(VERSION 3.4.1)
find_library(log-lib log)
find_library(android-lib android)

file(GLOB_RECURSE native_srcs "*.c")

add_library(cxw_ffmpeg
            SHARED
            src/main/jni/ffmpeg/native-lib.c
            src/main/jni/ffmpeg/player.c
            src/main/jni/ffmpeg/c.c
            src/main/jni/ffmpeg/file_test.c
            src/main/jni/ffmpeg/imooc_test.c
            src/main/jni/ffmpeg/lib_utils.c

            # Provides a relative path to your source file(s).
#            src/main/jni/ffmpeg/include/cmdutils.c
#            src/main/jni/ffmpeg/include/ffmpeg.c
#            src/main/jni/ffmpeg/include/ffmpeg_filter.c
#            src/main/jni/ffmpeg/include/ffmpeg_hw.c
#            src/main/jni/ffmpeg/include/ffmpeg_opt.c
        )


#添加libavcodec.so
add_library( avcodec
             SHARED
             IMPORTED)
set_target_properties( avcodec
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libavcodec.so)

#添加libavdevice.so
#add_library( avdevice
#             SHARED
#             IMPORTED)
#set_target_properties( avdevice
#                       PROPERTIES IMPORTED_LOCATION
#                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libavdevice.so)

add_library( avfilter
             SHARED
             IMPORTED)
set_target_properties( avfilter
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libavfilter.so)

add_library( avformat
             SHARED
             IMPORTED)
set_target_properties( avformat
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libavformat.so)

add_library( avutil
             SHARED
             IMPORTED)
set_target_properties( avutil
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libavutil.so)

add_library( swresample
             SHARED
             IMPORTED)
set_target_properties( swresample
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libswresample.so)

add_library( swscale
             SHARED
             IMPORTED)
set_target_properties( swscale
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libswscale.so)

#add_library( postproc
#             SHARED
#             IMPORTED)
#set_target_properties( postproc
#                       PROPERTIES IMPORTED_LOCATION
#                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libpostproc.so)



#头文件位置
include_directories(src/main/jni/ffmpeg/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

target_link_libraries( # Specifies the target library.
                      cxw_ffmpeg
                      avcodec
                      avfilter
                      avformat
                      avutil
                      swresample
                      swscale
                      #avdevice
                      #postproc

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       ${android-lib}
                    )