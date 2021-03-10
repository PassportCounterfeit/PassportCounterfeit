#include "ARG.h"
#include "utils.h"

bool ARG_P5(const string& uvPath, const string& wiPath, const string& irPath) {
	Mat uv = imread(uvPath);
	int width = uv.cols;
	int height = uv.rows;
	Mat checkArea1 = uv(Rect(width * 0.111, height * 0.254, width * 0.223, height * 0.52));//截取目标区域
	Mat checkArea2 = uv(Rect(width * 0.695, height * 0.248, width * 0.135, height * 0.519));
	Mat areaR1;
	Mat areaR2;
	curve(checkArea1, areaR1, R);
	curve(checkArea2, areaR2, R);
	threshold(areaR1, areaR1, 150, 255, THRESH_BINARY);
	threshold(areaR2, areaR2, 150, 255, THRESH_BINARY);
	morphologyEx(areaR1, areaR1, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	morphologyEx(areaR2, areaR2, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	//imwrite("F://研究生阶段//实验室//护照鉴伪//pattern//ARG//P5//areaR1.jpg",area1);//保存模板图片
	//imwrite("F://研究生阶段//实验室//护照鉴伪//pattern//ARG//P5//areaR2.jpg",area2);
	
	double maxVal1;
	double maxVal2;
	quickMatchTemplate(areaR1, patternPath + "ARG//P5//area1.jpg", &maxVal1, 0, TM_CCORR_NORMED);
	quickMatchTemplate(areaR2, patternPath + "ARG//P5//area2.jpg", &maxVal2, 0, TM_CCORR_NORMED);
	//cout << maxVal1 << endl;
	//cout << maxVal2 << endl;
	//imshow("1", areaR1);
	//imshow("2", areaR2);
	//waitKey();
	return maxVal1 >= 0.8 && maxVal2 >= 0.8;
}