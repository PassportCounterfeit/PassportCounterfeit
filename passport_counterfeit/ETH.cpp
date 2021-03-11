#include<opencv2/opencv.hpp>
#include<iostream>
#include "ETH.h"

using namespace std;
using namespace cv;

int ETH1(const char* wi, const char* ir) {
	Mat ir1 = imread(ir);
	Mat wi1 = imread(wi);
	return ETH1(ir1, wi1);
}

int ETH1(Mat wiETH,Mat irETH) {
	
	Mat wicheckArea = wiETH(Rect(wiETH.cols / 2 + 45, wiETH.rows / 5.5, wiETH.cols / 8, wiETH.rows / 4));
	Mat ircheckArea = irETH(Rect(irETH.cols / 2 + 45, irETH.rows / 5.5, irETH.cols / 8, irETH.rows / 4));
	cvtColor(wicheckArea, wicheckArea, COLOR_RGB2GRAY);
	cvtColor(ircheckArea, ircheckArea, COLOR_RGB2GRAY);
	adaptiveThreshold(wicheckArea, wicheckArea, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 5);
	adaptiveThreshold(ircheckArea, ircheckArea, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 5);

	/*imshow("wic", ircheckArea);
	imshow("irc", wicheckArea);*/
	cv::Scalar     meanWi, meanIr;
	cv::Scalar     devWi, devIr;
	cv::meanStdDev(wicheckArea, meanWi, devWi);
	cv::meanStdDev(ircheckArea, meanIr, devIr);
	float wi = meanWi.val[0];
	float ir = meanIr.val[0];
	double dwi = devWi.val[0];
	double dir = devIr.val[0];
	/*cout << wi << "  " << ir << endl;
	cout << dwi << "  " << dir << endl;*/
	if ((wi < ir) && (dwi > dir))
		return 0;
	else
		return 1;
}

int ETH2(const char* uv) {
	Mat uv1 = imread(uv);
	return ETH2(uv1);
}

int ETH2(Mat uvETH) {
	Mat checkArea = uvETH(Rect(0, 0, uvETH.cols, uvETH.rows / 2));

	cvtColor(checkArea, checkArea, COLOR_RGB2GRAY);
	threshold(checkArea, checkArea, 140, 255, THRESH_BINARY);
	//erode(checkArea, checkArea, Mat());
	dilate(checkArea, checkArea, Mat());
	dilate(checkArea, checkArea, Mat());
	dilate(checkArea, checkArea, Mat());
	//dilate(checkArea, checkArea, Mat());
	erode(checkArea, checkArea, Mat());
	erode(checkArea, checkArea, Mat());
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(checkArea, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat ImageContours = Mat::zeros(checkArea.size(), CV_8UC1);  //绘制
	Mat ImgContours = Mat::zeros(checkArea.size(), CV_8UC1);

	vector<vector<Point>>::iterator k;                    //迭代器，访问容器数据

	for (k = contours.begin(); k != contours.end();)      //遍历容器,设置面积因子
	{
		if (contourArea(*k, false) < 400)
		{//删除指定元素，返回指向删除元素下一个元素位置的迭代器
			k = contours.erase(k);
		}
		else
			++k;
	}

	//contours[i]代表第i个轮廓，contours[i].size()代表第i个轮廓上所有的像素点
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
		{
			//获取轮廓上点的坐标
			Point P = Point(contours[i][j].x, contours[i][j].y);
			ImgContours.at<uchar>(P) = 255;
		}
		drawContours(ImageContours, contours, i, Scalar(255), -1, 8);			
	}
	vector<vector<Point>> contours1;
	vector<Vec4i> hierarchy1;
	findContours(ImageContours, contours1, hierarchy1, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));
	if (contours1.size()==9)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}