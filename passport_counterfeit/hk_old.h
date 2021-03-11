#pragma once
#include<opencv.hpp>
using namespace std;
using namespace cv;

//0, 鉴定结果为真
//1, 鉴定结果为假

//紫外亮区检测
int idenHKCardOld1(const char* uv);
int idenHKCardOld1(cv::Mat uv);

//彩虹印刷
int idenHKCardOld2(const char* vi);
int idenHKCardOld2(cv::Mat vi);

