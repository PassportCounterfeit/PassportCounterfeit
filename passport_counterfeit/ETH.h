#pragma once
#include<opencv.hpp>
using namespace std;
using namespace cv;

/*消失人像部位检测*/
int ETH1(Mat ir,Mat wi);
int ETH1(const char* ir,const char* wi);

/*上半部分花纹检测*/
int ETH2(Mat uv);
int ETH2(const char* uv);