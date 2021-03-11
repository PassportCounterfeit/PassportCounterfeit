#include<opencv2/opencv.hpp>
#include "judge.h"
using namespace std;
using namespace cv;

int judge(Mat pic) {

	//imshow("aomen", aomenwi);
	//Mat checkArea = aomenwi(Rect(aomenwi.cols / 4, aomenwi.rows / 5, aomenwi.cols / 4, aomenwi.rows / 3));
	//imshow("check", checkArea);
	Mat grayaomen;
	cvtColor(pic, grayaomen, COLOR_RGB2GRAY);
	//imshow("g", grayaomen);
	threshold(grayaomen, grayaomen, 150, 255, THRESH_BINARY);
	dilate(grayaomen, grayaomen, Mat());
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(grayaomen, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat ImageContours = Mat::zeros(grayaomen.size(), CV_8UC1);  //����
	Mat ImgContours = Mat::zeros(grayaomen.size(), CV_8UC1);

	vector<vector<Point>>::iterator k;                    //��������������������

	for (k = contours.begin(); k != contours.end();)      //��������,�����������
	{
		if (contourArea(*k, false) < 2500)
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
	dilate(ImageContours, ImageContours, Mat());
	Canny(ImageContours, ImageContours, 10, 250, 5);
	//����Բ���
	vector<Vec3f> pcircles;
	//���룬��������������ͣ�-HOUGH_GRADIENT��dp(dp=1ʱ��ʾ����ռ�������ͼ��ռ�Ĵ�Сһ�£�dp=2ʱ����ռ�������ͼ��ռ��һ�룬�Դ�����)����̾���-���Էֱ�������Բ�� ����Ϊ��ͬ��Բ ,��Ե���ʱʹ��Canny���ӵĸ���ֵ�����ĵ��ۼ�����ֵ����ѡԲ�ģ�����ռ����ۼӺʹ��ڸ���ֵ�ĵ�Ͷ�Ӧ��Բ�ģ�����⵽Բ����С�뾶����⵽Բ�ĵ����뾶
	HoughCircles(ImageContours, pcircles, HOUGH_GRADIENT, 1, 60, 100, 13, 80, 150);
	//if(pcircles.size()==)
	/*����forѭ�����Խ�������Բ����ͼ���л�����*/
	//for (size_t i = 0; i < pcircles.size(); i++)//size_t �޷������� unsigned int 
	//{
	//	//��ȡԲ������
	//	Point center(cvRound(pcircles[i][0]), cvRound(pcircles[i][1]));//cvRound ���غͲ�����ӽ�������ֵ
	//	//��ȡ�뾶
	//	int radius = cvRound(pcircles[i][2]);
	//	//Բ��
	//	circle(aomenwi, center, 3, Scalar(0, 255, 0), -1, 8, 0);
	//	//Բ
	//	circle(aomenwi, center, radius, Scalar(0, 255, 0), 3, 8, 0);
	//}

	//cout << pcircles.size() << endl;
	//imshow("gray", aomenwi);
	if (pcircles.size() == 1)
	{
		return 3;
	}
	else
	{
		Mat checkArea = pic(Rect(0, 0, pic.cols, pic.rows / 6));
		vector<Mat> vec;
		split(checkArea, vec);
		Mat rcheckArea = vec[2];
		threshold(rcheckArea, rcheckArea, 150, 255, THRESH_BINARY);
		Mat binleftcheckArea = rcheckArea(Rect(0, 0, rcheckArea.cols / 2, rcheckArea.rows));
		Mat binrightcheckArea = rcheckArea(Rect(rcheckArea.cols / 2, 0, rcheckArea.cols / 2, rcheckArea.rows));
		Mat finalcheck = binleftcheckArea(Rect(binleftcheckArea.cols / 2, binleftcheckArea.rows / 2, binleftcheckArea.cols / 2, binleftcheckArea.rows / 2));
		//imshow("bin", finalcheck);waitKey(0);
		cv::Scalar mean;
		cv::Scalar dev;
		cv::meanStdDev(finalcheck, mean, dev);
		float m = mean.val[0];
		float n = dev.val[0];
		cout << m << endl << n << endl;
		if (n<20) {
			return 20;
		}
		else {
			return 2;
		}
		/*cout << m << endl << n << endl;
		imshow("check", binleftcheckArea);
		waitKey(0);*/
		
	}
}

int judge(const char* wi) {
	Mat wi1 = imread(wi);
	return judge(wi1);
}