#include "JPN.h"
#include "utils.h"

bool JPN_P3(const string& uvPath,const string& wiPath,const string& irPath) {
	Mat uvJPN = imread(uvPath);
	int widthUV = uvJPN.cols;
	int heightUV = uvJPN.rows;
	Mat wiJPN = imread(wiPath);
	int widthWI = wiJPN.cols;
	int heightWI = wiJPN.rows;

	Mat checkAreaUV = uvJPN(Rect(widthUV * 0.613, heightUV * 0.207, widthUV * 0.338, heightUV * 0.554));//截取目标区域
	Mat checkAreaWI = wiJPN(Rect(widthWI * 0.017, heightWI * 0.205, widthWI * 0.307, heightWI * 0.542));

	//方式一：直接取绿色通道计算各轮廓面积进行判断
	vector<Mat> channels;
	split(checkAreaUV, channels);
	Mat uvG = channels[1];//分离出G通道的像素值
	threshold(uvG, uvG, 160, 255, THRESH_BINARY);//二值化处理
	morphologyEx(uvG, uvG, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));//使用闭操作消除暗点
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

	//方式二：取灰度图滤波后对比白光图的头像进行模板匹配(效果非常不好)
	//Mat uvGray;
	//cvtColor(checkAreaUV,uvGray, COLOR_BGR2GRAY);
	///*medianBlur(uvGray, uvGray, 3);
	//GaussianBlur(uvGray, uvGray, Size(5, 5), 0, 0);*/

	//vector<Mat> channels;
	//split(checkAreaUV, channels);
	//Mat uvG = channels[1];//分离出G通道的像素值
	//threshold(uvG, uvG, 165, 255, THRESH_BINARY);//二值化处理

	//Mat wiGray;
	//cvtColor(checkAreaWI,wiGray,COLOR_BGR2GRAY);
	//threshold(wiGray, wiGray, 120, 255, THRESH_BINARY);//二值化处理
	////medianBlur(wiGray, wiGray, 3);

	//imshow("uvGray", uvG);
	//imshow("wiGray", wiGray);
	//waitKey();

	//cout << perceptualHash(uvGray, wiGray) << endl;
	//Mat matchResult;
	//matchTemplate(wiGray, uvG, matchResult, TM_CCORR_NORMED);
	//double minVal, maxVal;
	//Point minLoc, maxLoc;
	//minMaxLoc(matchResult, &minVal, &maxVal, &minLoc, &maxLoc,Mat());
	//cout << "maxVal: " << maxVal << endl;
	//cout << "minVal: " << minVal << endl;
	//return false;
}