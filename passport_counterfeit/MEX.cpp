#include "MEX.h"

bool MEX_P5(const string& uvPath, const string& wiPath, const string& irPath) {
	Mat uvMEX = imread(uvPath);
	int width = uvMEX.cols;
	int height = uvMEX.rows;
	Mat checkArea = uvMEX(Rect(width * 0.358, height * 0.318, width * 0.29, height * 0.417));//��ȡĿ������
	vector<Mat> channels;
	split(checkArea, channels);
	Mat uvR = channels[2];//�����Rͨ��������ֵ
	threshold(uvR, uvR, 200, 255, THRESH_BINARY);//��ֵ������
	morphologyEx(uvR, uvR, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));//ʹ�ñղ�������С����
	//imshow("uvR", uvR);
	//waitKey();
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(uvR, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE, Point(0, 0));//�����������
	int circle = 0;
	int ring = 0;
	for (int i = 0; i < contours.size(); i++) {
		int val = contourArea(contours[i]);
		//cout << val << endl;
		if (val > 100 && val < 2000)//��⻷״����
			ring++;
		else if (val >= 2800 && val <= 8000)//����м��ͼ��
			circle++;
	}
	return ring >= 2 && circle == 1;
}