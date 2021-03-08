#include "ESP.h"

bool ESP_P3(const string& uvPath, const string& wiPath, const string& irPath) {
	Mat uvESP = imread(uvPath);
	int width = uvESP.cols;
	int height = uvESP.rows;
	Mat checkArea = uvESP(Rect(0, height * 0.178, width , height * 0.018));//截取目标区域
	vector<Mat> channels;
	split(checkArea, channels);
	Mat uvG = channels[1];//分离出G通道的像素值
	threshold(uvG, uvG, 100, 255, THRESH_BINARY);//二值化处理
	morphologyEx(uvG, uvG, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));//使用开操作消除小亮点
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(uvG, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));//检测物体轮廓
	int nums = 0;
	for (int i = 0; i < contours.size(); i++) {
		int val = contourArea(contours[i]);
		if (val >= 120)//主要针对三个绿色光带进行辨别
			nums++;
	}
	//imshow("uvG", uvG);
	//waitKey();
	return nums == 3;
}