#include "TUR.h"


bool TUR_P2(const string& uvPath, const string& wiPath, const string& irPath) {
	Mat uvTUR = imread(uvPath);
	int width = uvTUR.cols;
	int height = uvTUR.rows;
	Mat checkArea = uvTUR(Rect(width * 0.391, height * 0.364, width * 0.231, height * 0.275));//��ȡĿ������
	vector<Mat> channels;
	split(checkArea, channels);
	Mat uvR = channels[2];//�����Rͨ��������ֵ
	//GaussianBlur(uvR, uvRG, Size(3, 3), 0, 0);
	medianBlur(uvR, uvR, 5);
	threshold(uvR, uvR, 120, 255, THRESH_BINARY);//��ֵ������
	//imshow("uvR", uvR);
	//waitKey();
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(uvR, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE, Point(0, 0));//�����������
	int areaSize = checkArea.rows * checkArea.cols;
	bool star = false;//����ֵ0.0487
	bool moon = false;//����ֵ0.2016
	for (int i = 0; i < contours.size(); i++) {
		double val = contourArea(contours[i]);
		val = val / areaSize;
		if (val > 0.03 && val < 0.06) {
			if (star)
				return false;
			else
				star = true;
		}
		if (val > 0.18 && val < 0.22) {
			if (moon)
				return false;
			else
				moon = true;
		}
	}
	return star && moon;

}