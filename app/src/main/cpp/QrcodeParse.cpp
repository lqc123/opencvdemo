//
// Created by admin on 2019/12/3.
//

#include <iostream>
#include "QrcodeParse.h"

using namespace cv;
using namespace std;

int QrcodeParse::findQrPoint(Mat &srcImg, vector<vector<Point>> &qrPoint) {
    //彩色图转灰度图
    Mat src_gray;
    cvtColor(srcImg, src_gray, CV_BGR2GRAY);

    //二值化
    Mat threshold_output;
    threshold(src_gray, threshold_output, 0, 255, THRESH_BINARY | THRESH_OTSU);
    Mat threshold_output_copy = threshold_output.clone();
    //调用查找轮廓函数
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE,
                 Point(0, 0));

    //通过黑色定位角作为父轮廓，有两个子轮廓的特点，筛选出三个定位角
    int parentIdx = -1;
    int ic = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (hierarchy[i][2] != -1 && ic == 0) {
            parentIdx = i;
            ic++;
        } else if (hierarchy[i][2] != -1) {
            ic++;
        } else if (hierarchy[i][2] == -1) {
            ic = 0;
            parentIdx = -1;
        }


        {
            bool isQr = isQrPoint(contours[parentIdx], threshold_output_copy);

            //保存找到的三个黑色定位角
            if (isQr)
                qrPoint.push_back(contours[parentIdx]);

            ic = 0;
            parentIdx = -1;
        }
    }

    return 0;
}
bool QrcodeParse::isQrPoint(std::vector<cv::Point>& contour, cv::Mat& img){
    //最小大小限定
    RotatedRect rotatedRect = minAreaRect(contour);
    if (rotatedRect.size.height < 10 || rotatedRect.size.width < 10)
        return false;

    //将二维码从整个图上抠出来
    cv::Mat cropImg = cropImage(img, rotatedRect);
    int flag = i++;

    //横向黑白比例1:1:3:1:1
    bool result = isQrColorRate(cropImg, flag);
    return result;
}

//横向和纵向黑白比例判断
bool QrcodeParse::isQrColorRate(cv::Mat& image, int flag)
{
    bool x = isQrColorRateX(image, flag);
    if (!x)
        return false;
    bool y = isQrColorRateY(image, flag);
    return y;
}
//横向黑白比例判断
bool QrcodeParse::isQrColorRateX(cv::Mat& image, int flag)
{
    int nr = image.rows / 2;
    int nc = image.cols * image.channels();

    vector<int> vValueCount;
    vector<uchar> vColor;
    int count = 0;
    uchar lastColor = 0;

    uchar* data = image.ptr<uchar>(nr);
    for (int i = 0; i < nc; i++)
    {
        vColor.push_back(data[i]);
        uchar color = data[i];
        if (color > 0)
            color = 255;

        if (i == 0)
        {
            lastColor = color;
            count++;
        }
        else
        {
            if (lastColor != color)
            {
                vValueCount.push_back(count);
                count = 0;
            }
            count++;
            lastColor = color;
        }
    }

    if (count != 0)
        vValueCount.push_back(count);

    if (vValueCount.size() < 5)
        return false;

    //横向黑白比例1:1:3:1:1
    int index = -1;
    int maxCount = -1;
    for (int i = 0; i < vValueCount.size(); i++)
    {
        if (i == 0)
        {
            index = i;
            maxCount = vValueCount[i];
        }
        else
        {
            if (vValueCount[i] > maxCount)
            {
                index = i;
                maxCount = vValueCount[i];
            }
        }
    }

    //左边 右边 都有两个值，才行
    if (index < 2)
        return false;
    if ((vValueCount.size() - index) < 3)
        return false;

    //黑白比例1:1:3:1:1
    float rate = ((float)maxCount) / 3.00;

    cout << "flag:" << flag << " ";

    float rate2 = vValueCount[index - 2] / rate;
    cout << rate2 << " ";
    if (!IsQrRate(rate2))
        return false;

    rate2 = vValueCount[index - 1] / rate;
    cout << rate2 << " ";
    if (!IsQrRate(rate2))
        return false;

    rate2 = vValueCount[index + 1] / rate;
    cout << rate2 << " ";
    if (!IsQrRate(rate2))
        return false;

    rate2 = vValueCount[index + 2] / rate;
    cout << rate2 << " ";
    if (!IsQrRate(rate2))
        return false;

    return true;
}
//纵向黑白比例判断 省略
bool QrcodeParse::isQrColorRateY(cv::Mat& image, int flag){
    return false;
}

cv::Mat QrcodeParse::cropImage(cv::Mat &mat, cv::RotatedRect rect) {
    Mat dst(mat,rect.boundingRect());
    return dst;
}

bool QrcodeParse::IsQrRate(float rate) {
    //大概比例 不能太严格
    return rate > 0.6 && rate < 1.9;
}
// pointDest存放调整后的三个点，三个点的顺序如下
// pt0----pt1
//
// pt2
bool QrcodeParse::adjustQrPoint(Point* pointSrc, Point* pointDest, float angle)
{
    bool clockwise;
    int index1[3] = { 2,1,0 };
    int index2[3] = { 0,2,1 };
    int index3[3] = { 0,1,2 };

    for (int i = 0; i < 3; i++)
    {
        int *n = index1;
        if(i==0)
            n = index1;
        else if (i == 1)
            n = index2;
        else
            n = index3;
        if (angle > 80 && angle < 99)
        {
            pointDest[0] = pointSrc[n[2]];
            if (clockwise)
            {
                pointDest[1] = pointSrc[n[0]];
                pointDest[2] = pointSrc[n[1]];
            }
            else
            {
                pointDest[1] = pointSrc[n[1]];
                pointDest[2] = pointSrc[n[0]];
            }
            return true;
        }
    }
    return true;
}

