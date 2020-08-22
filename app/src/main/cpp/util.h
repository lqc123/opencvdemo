//
// Created by admin on 2019/6/3.
//
#include <jni.h>
#include <opencv2/imgproc.hpp>
#include <android/log.h>
#ifndef OPENCVDEMO_UTIL_H
#define OPENCVDEMO_UTIL_H
#define LOG_TAG    "jnidemo" // 这个是自定义的LOG的标识
//#undef LOG // 取消默认的LOG
#define LOGI(...)  ((void)__android_log_print(ANDROID_LOG_INFO,LOG_TAG, __VA_ARGS__))
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG, __VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG, __VA_ARGS__)
using namespace cv;
 Mat bitmap2Mat(JNIEnv *env, jobject bitmap);
 void mat2bitmap(JNIEnv *env, Mat src, jobject bitmap);
jobject createBitmap(JNIEnv *env, jobject bitmap);
jobject mat_to_bitmap(JNIEnv * env, cv::Mat & src, bool needPremultiplyAlpha, jobject bitmap_config);
#endif //OPENCVDEMO_UTIL_H
