#include "utils.h"


int pixelCount(Mat& img, uchar minValue, uchar maxValue) {
	int res = 0;
	for (Mat_<uchar>::iterator it = img.begin<uchar>(); it != img.end<uchar>(); it++) {
		if ((*it) >= minValue && (*it) <= maxValue)
			res++;
	}
	return res;
}

int perceptualHash(const Mat& src, const Mat& target) {
	Mat img1 = src.clone();
	Mat img2 = target.clone();
	resize(img1, img1, Size(8, 8), 0, 0, INTER_CUBIC);
	resize(img2, img2, Size(8, 8), 0, 0, INTER_CUBIC);

	//cvtColor(img1, img1, COLOR_BGR2GRAY);
	//cvtColor(img2, img2, COLOR_BGR2GRAY);

	int average1 = 0;
	int average2 = 0;
	int arr1[64], arr2[64];
	for (int i = 0; i < 8; i++) {
		uchar* data1 = img1.ptr<uchar>(i);
		uchar* data2 = img2.ptr<uchar>(i);
		int head = i * 8;
		for (int j = 0; j < 8; j++){
			int tmp = head + j;
			arr1[tmp] = data1[j] / 4 * 4;
			arr2[tmp] = data2[j] / 4 * 4;
			average1 += arr1[tmp];
			average2 += arr2[tmp];
		}
	}
	average1 /= 64;
	average2 /= 64;
	for (int i = 0; i < 64; i++) {
		arr1[i] = (arr1[i] >= average1) ? 1 : 0;
		arr2[i] = (arr2[i] >= average2) ? 1 : 0;
	}
	int iDiffNum = 0;
	for (int i = 0; i < 64; i++) {
		if (arr1[i] != arr2[i])
			++iDiffNum;
	}
	return iDiffNum;
}

void curve(const Mat& src,Mat& dst, CurveType num) {	
	Mat dstImage;
	vector<Mat> g_vChannels;

	//∑÷¿ÎÕ®µ¿
	split(src, g_vChannels);
	Mat imageBlueChannel = g_vChannels.at(0);
	Mat imageGreenChannel = g_vChannels.at(1);
	Mat imageRedChannel = g_vChannels.at(2);
	switch (num) {
	case B:dst = imageBlueChannel; break;
	case R_DIFF_G:dst = imageRedChannel - imageGreenChannel; break;
	case G:dst = imageGreenChannel; break;
	case B_DIFF_R:dst = imageBlueChannel - imageRedChannel; break;
	case R:dst = imageRedChannel; break;
	case R_DIFF_B:dst = imageRedChannel - imageBlueChannel; break;
	case G_DIFF_B:dst = imageGreenChannel - imageBlueChannel; break;
	}
}

void quickMatchTemplate(InputArray src, const string& patternPath, double* maxVal, double* minVal, TemplateMatchModes method) {
	Mat matchResult;
	Mat areaPattern1 = imread(patternPath, IMREAD_GRAYSCALE);
	matchTemplate(src, areaPattern1, matchResult, method);
	minMaxLoc(matchResult, minVal, maxVal, 0, 0, Mat());
}