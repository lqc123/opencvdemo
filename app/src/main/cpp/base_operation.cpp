
// Created by admin on 2019/6/3.
//

#include <jni.h>
#include "util.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_lqc_opencvdemo_BasicOperationActivity_addOperation(JNIEnv *env, jobject instance,
                                                                    jobject bitmap,
                                                                    jobject bitmap1) {
    Mat resMat1 = bitmap2Mat(env, bitmap);
    Mat resMat2 = bitmap2Mat(env, bitmap1);
    Mat dst;//存储结果
    dst = resMat1 + resMat2;
//    dst=resMat2-resMat1;
    jobject result=createBitmap(env,bitmap);
    mat2bitmap(env, dst, result);
    return result;
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_lqc_opencvdemo_BasicOperationActivity_subOperation(JNIEnv *env, jobject instance,
                                                                    jobject bitmap,
                                                                    jobject bitmap1) {
    Mat resMat1 = bitmap2Mat(env, bitmap);
    Mat resMat2 = bitmap2Mat(env, bitmap1);
    Mat dst;//存储结果
    absdiff(resMat1, resMat2, dst);
//    dst=resMat2-resMat1;
    jobject result=createBitmap(env,bitmap);
    mat2bitmap(env, dst,result );
//    dst = 5 * img1;//增加曝光
//    dst = img1 / 5;//降低曝光
//    bitwise_and(img1, img2, dst);//逻辑与，求交集
//    bitwise_or(img1, img2, dst);//逻辑或，求并集
//    bitwise_not(img1, dst);//逻辑非，求补集
//    bitwise_xor(img1, img2, dst);//异或，相同为0，相异为1
    return result;
}

