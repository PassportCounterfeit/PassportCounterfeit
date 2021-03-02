#include "BRA.h"
#include "utils.h"

bool BRA_P4(const string& uvPath) {
	Mat uvBRA = imread(uvPath);
	int width = uvBRA.cols;
	int height = uvBRA.rows;
	Mat checkArea = uvBRA(Rect(width *0.044, height*0.303, width * 0.913, height * 0.446));//��ȡĿ������
	vector<Mat> channels;
	split(checkArea, channels);
	Mat uvR = channels[2];//�����Rͨ��������ֵ
	threshold(uvR, uvR, 100, 255, THRESH_BINARY);//��ֵ������
	//imshow("uvR", uvR);
	//waitKey();
	int whiteArea = pixelCount(uvR, 255, 255);//ֱ�Ӽ���ӫ���������
	int totalArea = checkArea.cols * checkArea.rows;
	double proportion = (double)(whiteArea) / totalArea;//����ռ�ȣ�����ֵΪ0.281756
	cout << proportion << endl;
	if (proportion >= 0.2 && proportion <= 0.36)
		return true;
	else
		return false;
}