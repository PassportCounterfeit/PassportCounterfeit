#pragma once
#include<opencv.hpp>
using namespace std;
using namespace cv;

/*��ʧ����λ���*/
int ETH1(Mat ir,Mat wi);
int ETH1(const char* ir,const char* wi);

/*�ϰ벿�ֻ��Ƽ��*/
int ETH2(Mat uv);
int ETH2(const char* uv);