//
// Created by admin on 2019/12/10.
//
#include <android/native_window_jni.h>
#include <android/native_window.h>
#include <android/bitmap.h>
#include <opencv2/imgproc.hpp>
#include <native_window.h>
#include <jni.h>
void throwExp(JNIEnv *env, const char *clazzName, const char* desc){
    jclass clazz=env->FindClass(clazzName);
    if(clazz){
        env->ThrowNew(clazz,desc);
    }
}

void nativeShow(JNIEnv *env,jobject surface,cv::Mat mat){

    //创建本地surface
    ANativeWindow* aNativeWindow= ANativeWindow_fromSurface(env,surface);
    if(aNativeWindow== NULL){
        throwExp(env, "java/lang/RuntimeException","native window null");
        return;
    }
    if(ANativeWindow_setBuffersGeometry(aNativeWindow,mat.cols,mat.rows,WINDOW_FORMAT_RGBA_8888)<0){
        throwExp(env, "java/lang/RuntimeException","ANativeWindow_setBuffersGeometry error");
        ANativeWindow_release(aNativeWindow) ;
        aNativeWindow=NULL;
        return;
    }
    ANativeWindow_acquire(aNativeWindow);
    ANativeWindow_Buffer buffer;
    if(ANativeWindow_lock(aNativeWindow,&buffer,NULL)<0){
        throwExp(env, "java/lang/RuntimeException","ANativeWindow_lock error");
        ANativeWindow_release(aNativeWindow) ;
        aNativeWindow=NULL;
        return;
    }
    int8_t* dstData=(int8_t*)buffer.bits;
    //stride一行数据
    int  dst_lineSize=buffer.stride*4;
    for (int i = 0; i < buffer.height; ++i) {
      memcpy(dstData+i*dst_lineSize,mat.data+i*mat.cols*4,dst_lineSize);
    }
    ANativeWindow_unlockAndPost(aNativeWindow);
}


