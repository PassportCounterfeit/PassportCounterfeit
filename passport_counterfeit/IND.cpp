#include "IND.h"
#include "utils.h"

bool IND_P3(const string& uvPath, const string& wiPath, const string& irPath) {
	Mat uvJPN = imread(uvPath);
	int width = uvJPN.cols;
	int height = uvJPN.rows;
	Mat checkArea = uvJPN(Rect(width * 0.316, 0, width * 0.052, height * 0.767));//截取目标区域
	vector<Mat> channels;
	split(checkArea, channels);
	Mat uvR = channels[2];//分离出R通道的像素值
	threshold(uvR, uvR, 110, 255, THRESH_BINARY);//二值化处理
	//morphologyEx(uvR, uvR, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	int whiteArea = pixelCount(uvR, 255, 255);//直接计算荧光文字面积
	int totalArea = checkArea.cols * checkArea.rows;
	double proportion = (double)(whiteArea) / totalArea;//计算面积占比，测试值约为0.2398
	if (proportion >= 0.16 && proportion <= 0.32)
		return true;
	else
		return false;
}