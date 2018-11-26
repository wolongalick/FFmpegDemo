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
            )


#添加libavcodec-57.so
add_library( avcodec-57
             SHARED
             IMPORTED)
set_target_properties( avcodec-57
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libavcodec-57.so)

#添加libavdevice-57.so
#add_library( avdevice-57
#             SHARED
#             IMPORTED)
#set_target_properties( avdevice-57
#                       PROPERTIES IMPORTED_LOCATION
#                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libavdevice-57.so)

add_library( avfilter-6
             SHARED
             IMPORTED)
set_target_properties( avfilter-6
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libavfilter-6.so)

add_library( avformat-57
             SHARED
             IMPORTED)
set_target_properties( avformat-57
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libavformat-57.so)

add_library( avutil-55
             SHARED
             IMPORTED)
set_target_properties( avutil-55
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libavutil-55.so)

add_library( swresample-2
             SHARED
             IMPORTED)
set_target_properties( swresample-2
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libswresample-2.so)

add_library( swscale-4
             SHARED
             IMPORTED)
set_target_properties( swscale-4
                       PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libswscale-4.so)

#add_library( postproc-54
#             SHARED
#             IMPORTED)
#set_target_properties( postproc-54
#                       PROPERTIES IMPORTED_LOCATION
#                       ${CMAKE_SOURCE_DIR}/src/main/jni/ffmpeg/armeabi/libpostproc-54.so)



#头文件位置
include_directories(src/main/jni/ffmpeg/include)

target_link_libraries( # Specifies the target library.
                      cxw_ffmpeg
                      avcodec-57
                      avfilter-6
                      avformat-57
                      avutil-55
                      swresample-2
                      swscale-4
                      #avdevice-57
                      #postproc-54

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       ${android-lib}
                    )