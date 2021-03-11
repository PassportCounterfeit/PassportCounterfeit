#include<opencv2/opencv.hpp>
#include<iostream>
#include "BGR.h"

using namespace std;
using namespace cv;

int BGR1(const char* uv) {
	Mat uvBGR = imread(uv);
	return BGR1(uvBGR);
}

int BGR1(Mat uvGBR) {
	Mat checkArea = uvGBR(Rect(uvGBR.cols / 7, uvGBR.cols / 16, uvGBR.cols / 3.5, uvGBR.rows / 8));
	//imshow("checkArea", checkArea);
	Mat checkAreaGray;
	cvtColor(checkArea, checkAreaGray, COLOR_RGB2GRAY);
	//imshow("gray", checkAreaGray);
	vector<Mat> vec;
	split(checkArea, vec); //通道分离
	//imshow("g", vec[1]);
	Mat gBGR = vec[1];
	threshold(gBGR, gBGR, 80, 255, THRESH_BINARY);
	vector<Rect> rects;
	//1.查找轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(gBGR, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));
	int val = 0;
	//cout << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++) {
		if (contourArea(contours[i]) > 200)
			val++;
	}
	if (val == 2)
		return 0;
	else
		return 1;
}