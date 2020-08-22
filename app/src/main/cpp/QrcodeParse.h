//
// Created by admin on 2019/12/3.
//
#include <opencv2/imgproc.hpp>
#include <jni.h>
#include <vector>


#ifndef OPENCVDEMO_QRCODEPARSE_H
#define OPENCVDEMO_QRCODEPARSE_H


class QrcodeParse {
public:
    int findQrPoint(cv::Mat& srcImg, std::vector<std::vector<cv::Point>>& qrPoint);
    bool isQrPoint(std::vector<cv::Point>& contour, cv::Mat& img);
    bool isQrColorRate(cv::Mat& image, int flag);
    bool isQrColorRateX(cv::Mat& image, int flag);
    bool isQrColorRateY(cv::Mat& image, int flag);
    bool adjustQrPoint(cv::Point* pointSrc, cv::Point* pointDest, float angle);
private:
    int i;

    cv::Mat cropImage(cv::Mat &mat, cv::RotatedRect rect);

    bool IsQrRate(float rate2);
};


#endif //OPENCVDEMO_QRCODEPARSE_H
