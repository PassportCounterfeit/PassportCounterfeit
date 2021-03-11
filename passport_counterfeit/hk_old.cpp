#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include "hk_old.h"
#define uvRectangleWidth  290
#define uvRectangleHight 180
#define uvtopleftX 345
#define uvtopleftY 215
using namespace std;
using namespace cv;

int idenHKCardOld1(const char* uv)
{
	Mat uvimage = imread(uv);
	return idenHKCardOld1(uvimage);
}

int idenHKCardOld1(cv::Mat uv)
{
	const Size imgSize = { 990, 640 };
	resize(uv, uv, imgSize);
	Mat gray_uv;
	cvtColor(uv, gray_uv, COLOR_RGB2GRAY);
	Mat bin_uv;
	threshold(gray_uv, bin_uv, 80, 255, THRESH_BINARY);
	dilate(bin_uv, bin_uv, Mat());
	erode(bin_uv, bin_uv, Mat());
	
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(bin_uv, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//cout << contours.size() << endl;
	Mat linePic = Mat::zeros(bin_uv.rows, bin_uv.cols, CV_8UC3);
	for (int index = 0; index < contours.size(); index++)
	{
		drawContours(linePic, contours, index, Scalar(rand() & 255, rand() & 255, rand() & 255, rand() & 255), 1, 8);
	}

	//imshow("linePic", linePic);
	vector<vector<Point>> polyContours(contours.size());
	int maxArea = 0;
	for (int index = 0; index < contours.size(); index++)
	{
		if (contourArea(contours[index]) > contourArea(contours[maxArea]))
		{
			maxArea = index;
		}
		approxPolyDP(contours[index], polyContours[index], 10, true);
	}
	//cout << maxArea << endl;
	//Mat polyPic = Mat::zeros(bin_uv.rows, bin_uv.cols, CV_8UC3);
	//drawContours(bin_uv, polyContours, maxArea, Scalar(0, 0, 255, 2));
	Rect uv_rect = boundingRect(contours[maxArea]);
	if (((abs(uv_rect.height - uvRectangleHight) <= 10) && (abs(uv_rect.width - uvRectangleWidth) <= 10)
		&& (abs(uv_rect.tl().x - uvtopleftX) <= 10) && (abs(uv_rect.tl().y - uvtopleftY) <= 10)) || (abs(uv_rect.area() - uvRectangleHight * uvRectangleWidth) <= 200))
	{
		return 0;
	}
	//cout << uv_rect.tl() << endl;
	//rectangle(uv, uv_rect, Scalar(0, 0, 255), 2, 8, 0);
	//imshow("gray_uv", uv);
	return 1;
}

int idenHKCardOld2(const char* vi)
{
	Mat viimage = imread(vi);
	return idenHKCardOld2(viimage);
}

int idenHKCardOld2(cv::Mat vi)
{
	const Size imgSize = { 990, 640 };
	resize(vi, vi, imgSize);
	//imshow("vi", vi);
	//½ØÈ¡½¥±ä±³¾°Çø
	Mat vi_back = vi(Rect(880,245,80,90));
	vector<Mat> vec;
	split(vi_back, vec);
	Mat R = vec[2];
	Mat G = vec[1];
	Mat B = vec[0];
	Mat gray_vi,dst;
	
	cvtColor(vi_back, gray_vi, COLOR_RGB2GRAY);
	cv::Mat resultImageUV = cv::Mat::zeros(gray_vi.size(), gray_vi.type());
	vec[0].convertTo(resultImageUV, CV_32F);
	resultImageUV = resultImageUV + 1;
	cv::log(resultImageUV, resultImageUV);
	//resultImage = c * resultImage;
	cv::normalize(resultImageUV, resultImageUV, 0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(resultImageUV, resultImageUV);
	Mat bin_vi;
	threshold(resultImageUV, bin_vi, 180, 255, THRESH_BINARY);
	dilate(bin_vi, bin_vi, Mat());
	erode(bin_vi, bin_vi, Mat());
	//equalizeHist(gray_vi, dst);
	namedWindow("vi_back", WINDOW_NORMAL);
	imshow("vi_back", bin_vi);
	//Mat bin_vi_left = bin_vi(Rect(0, 0, bin_vi.cols / 2, bin_vi.rows));
	//Mat bin_vi_right = bin_vi(Rect(0, bin_vi.cols / 2, bin_vi.cols / 2, bin_vi.rows));
	

	return 1;
}