#include<opencv2/opencv.hpp>
#include<iostream>
#include "ETH.h"

using namespace std;
using namespace cv;

int DMA1(Mat uvDMA) {
	Mat checkArea = uvDMA(Rect(0, 0, uvDMA.cols, uvDMA.rows / 2 + 10));
	//imshow("checkArea", checkArea);
	vector<Mat> vec;
	split(checkArea, vec); //ͨ������
	Mat gcheckArea = vec[1];
	//imshow("gcheck", gcheckArea);
	threshold(gcheckArea, gcheckArea, 100, 255, THRESH_BINARY);
	erode(gcheckArea, gcheckArea, Mat());
	dilate(gcheckArea, gcheckArea, Mat());
	dilate(gcheckArea, gcheckArea, Mat());
	erode(gcheckArea, gcheckArea, Mat());
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(gcheckArea, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat ImageContours = Mat::zeros(gcheckArea.size(), CV_8UC1);  //����
	Mat ImgContours = Mat::zeros(gcheckArea.size(), CV_8UC1);

	vector<vector<Point>>::iterator k;                    //��������������������

	for (k = contours.begin(); k != contours.end();)      //��������,�����������
	{
		if (contourArea(*k, false) < 500)
		{//ɾ��ָ��Ԫ�أ�����ָ��ɾ��Ԫ����һ��Ԫ��λ�õĵ�����
			k = contours.erase(k);
		}
		else
			++k;
	}

	//contours[i]�����i��������contours[i].size()�����i�����������е����ص�
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
		{
			//��ȡ�����ϵ������
			Point P = Point(contours[i][j].x, contours[i][j].y);
			ImgContours.at<uchar>(P) = 255;
		}
		drawContours(ImageContours, contours, i, Scalar(255), -1, 8);
	}
	vector<vector<Point>> contours1;
	vector<Vec4i> hierarchy1;
	findContours(ImageContours, contours1, hierarchy1, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));
	if (contours1.size() == 3)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int DMA1(const char* uvDMA) {
	Mat uvDMA1 = imread(uvDMA);
	return DMA1(uvDMA1);
}