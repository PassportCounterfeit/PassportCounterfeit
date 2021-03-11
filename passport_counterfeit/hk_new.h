#pragma once
#include<opencv.hpp>

using namespace cv;

//0, 鉴定结果为真
//1, 鉴定结果为假
int idenHKCardNew1(const char* front, const char* back);
int idenHKCardNew1(cv::Mat front, cv::Mat back);

int idenHKCardNew2(const char* ir_B, const char* uv_B);
int idenHKCardNew2(Mat ir_B, Mat uv_B);

int idenHKCardNew3(const char* vi);
int idenHKCardNew3(Mat vi);