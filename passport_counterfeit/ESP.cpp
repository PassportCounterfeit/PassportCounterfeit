#include "ESP.h"

bool ESP_P3(const string& uvPath, const string& wiPath, const string& irPath) {
	Mat uvESP = imread(uvPath);
	int width = uvESP.cols;
	int height = uvESP.rows;
	Mat checkArea = uvESP(Rect(0, height * 0.178, width , height * 0.018));//��ȡĿ������
	vector<Mat> channels;
	split(checkArea, channels);
	Mat uvG = channels[1];//�����Gͨ��������ֵ
	threshold(uvG, uvG, 100, 255, THRESH_BINARY);//��ֵ������
	morphologyEx(uvG, uvG, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));//ʹ�ÿ���������С����
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(uvG, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));//�����������
	int nums = 0;
	for (int i = 0; i < contours.size(); i++) {
		int val = contourArea(contours[i]);
		if (val >= 120)//��Ҫ���������ɫ������б��
			nums++;
	}
	//imshow("uvG", uvG);
	//waitKey();
	return nums == 3;
}