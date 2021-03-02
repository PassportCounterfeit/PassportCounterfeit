#include "BRA.h"
#include "utils.h"

bool BRA_P4(const string& uvPath) {
	Mat uvBRA = imread(uvPath);
	int width = uvBRA.cols;
	int height = uvBRA.rows;
	Mat checkArea = uvBRA(Rect(width *0.044, height*0.303, width * 0.913, height * 0.446));//截取目标区域
	vector<Mat> channels;
	split(checkArea, channels);
	Mat uvR = channels[2];//分离出R通道的像素值
	threshold(uvR, uvR, 100, 255, THRESH_BINARY);//二值化处理
	//imshow("uvR", uvR);
	//waitKey();
	int whiteArea = pixelCount(uvR, 255, 255);//直接计算荧光文字面积
	int totalArea = checkArea.cols * checkArea.rows;
	double proportion = (double)(whiteArea) / totalArea;//计算占比，测试值为0.281756
	cout << proportion << endl;
	if (proportion >= 0.2 && proportion <= 0.36)
		return true;
	else
		return false;
}