#include "IND.h"
#include "utils.h"

bool IND_P3(const string& uvPath, const string& wiPath, const string& irPath) {
	Mat uvJPN = imread(uvPath);
	int width = uvJPN.cols;
	int height = uvJPN.rows;
	Mat checkArea = uvJPN(Rect(width * 0.316, 0, width * 0.052, height * 0.767));//��ȡĿ������
	vector<Mat> channels;
	split(checkArea, channels);
	Mat uvR = channels[2];//�����Rͨ��������ֵ
	threshold(uvR, uvR, 110, 255, THRESH_BINARY);//��ֵ������
	//morphologyEx(uvR, uvR, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
	int whiteArea = pixelCount(uvR, 255, 255);//ֱ�Ӽ���ӫ���������
	int totalArea = checkArea.cols * checkArea.rows;
	double proportion = (double)(whiteArea) / totalArea;//�������ռ�ȣ�����ֵԼΪ0.2398
	if (proportion >= 0.16 && proportion <= 0.32)
		return true;
	else
		return false;
}