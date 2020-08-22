#include <jni.h>
#include <string>
#include <opencv2/imgproc.hpp>
#include <android/bitmap.h>
#include <opencv2/core.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/core/mat.hpp>
#include "util.h"
#include <native_window.h>


using namespace cv;


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_lqc_opencvdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_lqc_opencvdemo_MainActivity_faceInfo(JNIEnv *env, jobject src,
                                                      jobject dest) {



    // 1. bitmap2Mat
    Mat src_mat = bitmap2Mat(env, dest);
    Mat gray_mat, dst_mat;
    // 2. 讲图片处理成 Gray 可以提升处理速度
    cvtColor(src_mat, gray_mat, COLOR_BGRA2GRAY);
//    // 2.2 3X3降噪处理
    blur(gray_mat, gray_mat, Size(3, 3));
//    // 3. 处理边缘检测
    Canny(gray_mat, gray_mat, 30, 80);
    //霍夫
    std::vector<Vec3f> circles;
    HoughCircles(gray_mat, circles, HOUGH_GRADIENT, 1, gray_mat.rows / 4, 100, 200);
    //二值图
//    threshold(gray_mat,gray_mat,100,255,ThresholdTypes::THRESH_BINARY);
    //自适应阈值
//    adaptiveThreshold(gray_mat,gray_mat,255,AdaptiveThresholdTypes::ADAPTIVE_THRESH_GAUSSIAN_C,ThresholdTypes::THRESH_BINARY,11,5);
    // 4. mat2bitmap
    mat2bitmap(env, gray_mat, dest);

    return dest;
}
/**
 * 初始化分类器
 */
//人脸检测的类
CascadeClassifier faceCascade;
extern "C"
JNIEXPORT void JNICALL
Java_com_example_lqc_opencvdemo_MainActivity_initCascadeClassifier(JNIEnv *env, jobject instance,
                                                                   jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);
    if (!path) {
        LOGD("path alloc error");
        return;
    }
    faceCascade.load(path);
    LOGD("分类器加载成功");
    // TODO

    env->ReleaseStringUTFChars(path_, path);
}
/**
 * 人脸识别
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_lqc_opencvdemo_MainActivity_faceDetection(JNIEnv *env, jobject instance,
                                                           jobject dest) {
    Mat src_mat = bitmap2Mat(env, dest);
    if (src_mat.empty()) {
        return NULL;
    }
    Mat grayMat;
    // 2. 转成灰度图，提升运算速度，灰度图所对应的 CV_8UC1 单颜色通道，信息量少 0-255 1u
    cvtColor(src_mat, grayMat, CV_RGBA2GRAY);
    // 3. 转换直方图均衡化补偿
    Mat equalizeMat;
    equalizeHist(grayMat, equalizeMat);

    // 4. 检测人脸，这是个大问题
    std::vector<Rect> faces;
//    faceCascade.detectMultiScale(equalizeMat, faces, 1.1, 5, 0 | CV_HAAR_SCALE_IMAGE,
//                                       Size(160, 160));
    faceCascade.detectMultiScale(equalizeMat, faces, 1.2, 6, 0, Size(0, 0));
    LOGE("检测到人脸的个数：%d", faces.size());
    if (faces.size() == 1) {
        Rect faceRect = faces[0];
        // 画一个框框，标记出人脸
        rectangle(src_mat, faceRect, Scalar(255, 155, 155), 3);
        mat2bitmap(env, src_mat, dest);

        // 只裁剪人脸部分的直方均衡补偿
//        Mat saveMat = Mat(equalizeMat, faceRect);
        // mat 保存成文件  png ,上传到服务器吧，接着下一张（眨眼，张嘴巴）
//        imwrite("xxxx/xxx.png", equalizeMat);
    }
    return dest;

    // TODO

}
/**
 * 霍夫检测
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_lqc_opencvdemo_MainActivity_houghTest(JNIEnv *env, jobject instance,
                                                       jobject dest) {
    return NULL;
    // TODO

}
/**
 * 行人检测
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_lqc_opencvdemo_MainActivity_hogFaceDetection(JNIEnv *env, jobject thiz,
                                                              jobject dest) {
    Mat src_mat = bitmap2Mat(env, dest);
    if (src_mat.empty()) {
        return NULL;
    }
    std::vector<Rect> region;
    HOGDescriptor hog; // 采用默认参数
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    hog.detectMultiScale(src_mat, region, 0, cv::Size(8, 8), cv::Size(32, 32), 1.05, 1);
    LOGE("检测到人的个数：%d", region.size());
    return dest;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_lqc_opencvdemo_ImageCutActivity_floodFill(JNIEnv *env, jobject thiz,
                                                           jobject bitmap, jobject surface) {
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmap, &info);
    void *pixels;
    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    Mat mat;

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGD("bitmap2Mat: CV_8UC4 -> RGBA_8888");
        cvtColor(Mat(info.height, info.width, CV_8UC4, pixels),mat,CV_RGBA2RGB);
    } else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        LOGD("bitmap2Mat: CV_8UC2 -> RGBA_565");
        cvtColor(Mat(info.height, info.width, CV_8UC2, pixels),mat,CV_BGR5652RGB);
    }
    AndroidBitmap_unlockPixels(env, bitmap);
    Rect rect;
    floodFill(mat,Point(10,10),Scalar(255,0,0),&rect,Scalar(10,255,255),Scalar(10,255,255),8);
    cvtColor(mat,mat,CV_BGR2BGRA);
    nativeShow(env,surface,mat);
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_lqc_opencvdemo_ImageCutActivity_grabCut(JNIEnv *env, jobject thiz,
                                                           jobject bitmap, jobject config) {
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmap, &info);
    void *pixels;
    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    Mat mat;

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGD("bitmap2Mat: CV_8UC4 -> RGBA_8888");
        cvtColor(Mat(info.height, info.width, CV_8UC4, pixels),mat,CV_RGBA2RGB);
    } else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        LOGD("bitmap2Mat: CV_8UC2 -> RGBA_565");
        cvtColor(Mat(info.height, info.width, CV_8UC2, pixels),mat,CV_BGR5652RGB);
    }
    AndroidBitmap_unlockPixels(env, bitmap);
    Rect rect(0, 0, 406, 318);
    Mat result, bg, fg;
    grabCut(mat, result, rect, bg, fg, 1, GC_INIT_WITH_RECT);
    //result和GC_PR_FGD对应像素相等时，目标图像该像素值置为255
    compare(result, GC_PR_FGD, result, CMP_EQ);
    Mat foreground(mat.size(), CV_8UC3, Scalar(255, 0, 0));
    mat.copyTo(foreground, result);//copyTo有两种形式，此形式表示result为mask
    return mat_to_bitmap(env,foreground, false,config);
}