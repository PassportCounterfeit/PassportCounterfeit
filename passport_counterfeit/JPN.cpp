#include "JPN.h"
#include "utils.h"

bool JPN_P3(const string& uvPath,const string& wiPath,const string& irPath) {
	Mat uvJPN = imread(uvPath);
	int widthUV = uvJPN.cols;
	int heightUV = uvJPN.rows;
	Mat wiJPN = imread(wiPath);
	int widthWI = wiJPN.cols;
	int heightWI = wiJPN.rows;

	Mat checkAreaUV = uvJPN(Rect(widthUV * 0.613, heightUV * 0.207, widthUV * 0.338, heightUV * 0.554));//��ȡĿ������
	Mat checkAreaWI = wiJPN(Rect(widthWI * 0.017, heightWI * 0.205, widthWI * 0.307, heightWI * 0.542));

	//��ʽһ��ֱ��ȡ��ɫͨ�������������������ж�
	vector<Mat> channels;
	split(checkAreaUV, channels);
	Mat uvG = channels[1];//�����Gͨ��������ֵ
	threshold(uvG, uvG, 160, 255, THRESH_BINARY);//��ֵ������
	morphologyEx(uvG, uvG, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));//ʹ�ñղ�����������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(uvG, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));//�����������
	for (int i = 0; i < contours.size(); i++) {
		int val = contourArea(contours[i]);
		//cout << val << endl;
		if (val > 10000 && val < 30000);//ʹ������ж��ҵ��������Ƿ��������Ӧ����Բ
		return true;
	}
	return false;

	//��ʽ����ȡ�Ҷ�ͼ�˲���ԱȰ׹�ͼ��ͷ�����ģ��ƥ��(Ч���ǳ�����)
	//Mat uvGray;
	//cvtColor(checkAreaUV,uvGray, COLOR_BGR2GRAY);
	///*medianBlur(uvGray, uvGray, 3);
	//GaussianBlur(uvGray, uvGray, Size(5, 5), 0, 0);*/

	//vector<Mat> channels;
	//split(checkAreaUV, channels);
	//Mat uvG = channels[1];//�����Gͨ��������ֵ
	//threshold(uvG, uvG, 165, 255, THRESH_BINARY);//��ֵ������

	//Mat wiGray;
	//cvtColor(checkAreaWI,wiGray,COLOR_BGR2GRAY);
	//threshold(wiGray, wiGray, 120, 255, THRESH_BINARY);//��ֵ������
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