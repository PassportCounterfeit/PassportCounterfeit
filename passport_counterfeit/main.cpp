#include<iostream>
#include<cmath>
#include"hk_new.h"
#include "hk_old.h"
#include "passbook.h"
#include "BGR.h"
#include "judge.h"

using namespace std;
using namespace cv;

void main() {

	//������ʧ����ͼ����
	Mat uvNPL = imread("E:\\��α����\\Paspoorten\\N\\NPL\\NPL_P6\\JPG\\uv.jpg");
	imshow("uvDMA", uvNPL);
	//Mat check_area = uvNPL(Rect(0));
	//Mat checkArea = uvDMA(Rect(0, 0, uvDMA.cols, uvDMA.rows / 2+10));
	//imshow("checkArea", checkArea);
	
	waitKey(0);
}