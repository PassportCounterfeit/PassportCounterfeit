#include "JPN.h"


bool JPN_P3(const string& uvPath) {
	Mat uvJPN = imread(uvPath);
	int width = uvJPN.cols;
	int height = uvJPN.rows;
	Mat checkArea = uvJPN(Rect(width * 0.613, height * 0.207, width * 0.338, height * 0.554));//截取目标区域
	vector<Mat> channels;
	split(checkArea, channels);
	Mat uvG = channels[1];//分离出G通道的像素值
	threshold(uvG, uvG, 160, 255, THRESH_BINARY);//二值化处理
	morphologyEx(uvG, uvG, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));//使用闭操作消除暗点
	//imshow("uvG", uvG);
	//waitKey();
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(uvG, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));//检测物体轮廓
	for (int i = 0; i < contours.size(); i++) {
		int val = contourArea(contours[i]);
		//cout << val << endl;
		if (val > 10000 && val < 30000);//使用面积判断找到的轮廓是否是人像对应的椭圆
			return true;
	}
	return false;
}