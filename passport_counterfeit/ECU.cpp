#include<opencv2/opencv.hpp>
#include<iostream>
#include "ECU.h"

int ECU1(Mat irECU, Mat wiECU) {
	Mat wiCheckArea = wiECU(Rect(0, 20, wiECU.cols / 4, wiECU.rows / 10));
	Mat irCheckArea = irECU(Rect(0, 20, irECU.cols / 4, wiECU.rows / 10));
	//imshow("ircheckArea", ircheckArea);
	//imshow("checkArea", wicheckArea);
	Mat irCheckAreaGray;
	Mat wiCheckAreaGray;

	cvtColor(wiCheckArea, wiCheckAreaGray, COLOR_RGB2GRAY);
	cvtColor(irCheckArea, irCheckAreaGray, COLOR_RGB2GRAY);
	//imshow("hell", wiCheckAreaGray);
	//imshow("hell1", irCheckAreaGray);
	Mat irCheckAreaBin;
	Mat wiCheckAreaBin;

	threshold(wiCheckAreaGray, wiCheckAreaBin, 180, 255, THRESH_BINARY);
	threshold(irCheckAreaGray, irCheckAreaBin, 180, 255, THRESH_BINARY);
	imshow("hel", wiCheckAreaBin);
	imshow("hel1", irCheckAreaBin);
	cv::Scalar     meanWi, meanIr;
	cv::Scalar     devWi, devIr;
	cv::meanStdDev(wiCheckAreaBin, meanWi, devWi);
	cv::meanStdDev(irCheckAreaBin, meanIr, devIr);
	float wi = meanWi.val[0];
	float ir = meanIr.val[0];
	double dwi = devWi.val[0];
	double dir = devIr.val[0];

	if (((dwi - dir) > 50) && (wi < ir))
		return 0;
	else
	{
		return 1;
	}
}

int ECU1(const char* irECU, const char* wiECU) {
	Mat irECU1 = imread(irECU);
	Mat wiECU1 = imread(wiECU);
	return ECU1(irECU1, wiECU1);
}