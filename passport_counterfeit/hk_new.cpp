#include<opencv2/opencv.hpp>
#include<iostream>
#include "hk_new.h"

using namespace std;
using namespace cv;


int idenHKCardNew1(const char* front, const char* back) {
	Mat frontImg = imread(front);
	Mat backImg = imread(back);
	return idenHKCardNew1(frontImg, backImg);
}

int idenHKCardNew1(Mat front, Mat back) {
	//resizeͼƬ
	const Size imgSize = { 990, 640 };
	resize(front, front, imgSize);
	resize(back, back, imgSize);
	//imshow("front", front);
	//imshow("back", back);

	////////////////////////////////////////////////////////////////////////////////
	//�����ж�
	cvtColor(front, front, COLOR_BGR2GRAY);
	threshold(front, front, 230, 255, THRESH_BINARY);

	//��ȡ��������
	Mat idenPosFro1 = front(Rect(410, 180, 300, 300));
	
	//imshow("hello",idenPosFro1);
	
	//ͳ�����ص�
	int w = idenPosFro1.cols;
	cout << w << '\t' << endl;
	int h = idenPosFro1.rows;
	cout << h << '\t' << endl;
	int sum = 0;
	for (int i = 0; i <= w - 1; i++) {
		uchar* data = idenPosFro1.ptr<uchar>(i);
		for (int j = 0; j <= h - 1; j++) {
			//cout << int(data[j])<<" ";
			sum += (data[j] == 255 ? 1 : 0);
		}
	}
	float res = sum * 1.0 / w / h;
	//cout << res << endl;
	if (res > 0.35 && res < 0.8) {
		return 0;
	}

	////////////////////////////////////////////////////////////////////////////////////
	//�����ж�
	cvtColor(back, back, COLOR_BGR2GRAY);
	//��ֵ�˲�
	blur(back, back, Size(5, 5));

	//��ֵ��
	threshold(back, back, 80, 255, THRESH_BINARY);

	Mat horizontalShort = getStructuringElement(MORPH_RECT, Size(10, 10));
	morphologyEx(back, back, MORPH_CLOSE, horizontalShort);
	
	//��������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(back, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//imshow("back", back);
	for (vector<Point> contour : contours)
	{
		cv::Rect contourRect = boundingRect(contour);
		if (contourRect.x < 250 || contourRect.x>700 || contourRect.y < 170 || contourRect.y >430)continue;
		//cout << "width:" << contourRect.width << endl;
		//cout << "height:" << contourRect.height << endl;
		if (contourRect.height > 100 && contourRect.height < 250 && contourRect.width>200 && contourRect.width < 400) {
			return 0;
		}
	}

	return 1;
}

//͸������
int idenHKCardNew2(const char* ir_B, const char* uv_B) {
	Mat frontImg = imread(ir_B);
	Mat backImg = imread(uv_B);
	return idenHKCardNew2(frontImg, backImg);
}

int idenHKCardNew2(Mat ir_B, Mat uv_B) {
	//resizeͼƬ
	const Size imgSize = { 990, 640 };
	resize(ir_B, ir_B, imgSize);
	resize(uv_B, uv_B, imgSize);

	////////////////////////////////////////////////////////////////////////////////
	//�����ж�
	cvtColor(ir_B, ir_B, COLOR_BGR2GRAY);
	cvtColor(uv_B, uv_B, COLOR_BGR2GRAY);

	//��ȡ͸������
	Mat transpIr = ir_B(Rect(660, 110, 150, 60));
	Mat transpUv = uv_B(Rect(660, 110, 150, 60));
	

    //������ͼ�������͸�����ڽ��ж����任����ͼƬЧ��
	cv::Mat resultImageUV =cv::Mat::zeros(transpUv.size(), transpUv.type());
	transpUv.convertTo(resultImageUV, CV_32F);
	resultImageUV = resultImageUV + 1;
	cv::log(resultImageUV, resultImageUV);
	//resultImage = c * resultImage;
	cv::normalize(resultImageUV, resultImageUV, 0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(resultImageUV, resultImageUV);
	
	//�Ժ���ͼ�������͸������������ͬ���Ķ����任
	cv::Mat resultImageIR = cv::Mat::zeros(transpUv.size(), transpUv.type());
	transpIr.convertTo(resultImageIR, CV_32F);
	resultImageIR = resultImageIR + 1;
	cv::log(resultImageIR, resultImageIR);
	//resultImage = c * resultImage;
	cv::normalize(resultImageIR, resultImageIR, 0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(resultImageIR, resultImageIR);

	threshold(resultImageUV, resultImageUV, 135, 255, THRESH_BINARY);
	threshold(resultImageIR, resultImageIR, 135, 255, THRESH_BINARY);
	
	//��ͼ�������ֵ�˲�
	medianBlur(resultImageUV, resultImageUV, 3);
	medianBlur(resultImageUV, resultImageUV, 3);
	//GaussianBlur(resultImageUV, resultImageUV, Size(3, 3),0,0, BORDER_DEFAULT);
	
	//������ĺ��������ͼ�������͸�����ڽ��и�ʴ�����Ͳ���
	erode(resultImageIR, resultImageIR, Mat());
	erode(resultImageUV, resultImageUV, Mat());
	dilate(resultImageIR, resultImageIR, Mat());
	dilate(resultImageUV, resultImageUV, Mat());

	//ͼ��ת��Ϊͼ������������׼��
	Mat resultImageUV_inverse = 255 - resultImageUV;
	Mat resultImageIR_inverse = 255 - resultImageIR;

	vector<vector<Point>>contoursUV;
	findContours(resultImageUV_inverse, contoursUV, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	cout << "UV��������Ϊ" << contoursUV.size() << endl;
	
	vector<vector<Point>>contoursIR;
	findContours(resultImageIR_inverse, contoursIR, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	cout << "IR��������Ϊ" << contoursIR.size() << endl;

	if (contoursUV.size() > contoursIR.size())
		return 0;
	else
		return 1;

}

int idenHKCardNew3(const char* vi)
{
	Mat frontImg = imread(vi);
	return idenHKCardNew3(frontImg);
}

int idenHKCardNew3(Mat vi_B)
{
	Mat waveAreaVi = vi_B(Rect(940, 230, 50, 260));
	vector<Mat> vec;
	split(waveAreaVi, vec);

	Mat R = vec[2];
	Mat G = vec[1];
	Mat B = vec[0];

	Mat gray,binary;
	//Canny(waveAreaVi, gray, 150, 200);
	//imshow("wave", waveAreaVi);
	cvtColor(waveAreaVi, gray, COLOR_RGB2GRAY);
	
	threshold(R, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	dilate(binary, binary, Mat());
	dilate(binary, binary, Mat());
	erode(binary, binary, Mat());
	erode(binary, binary, Mat());
	erode(binary, binary, Mat());

	//ͼ��תһ�Σ����ں����Ĵ���
	Mat binary_reverse = 255 - binary;

	vector<vector<Point>>contoursR;
	findContours(binary_reverse, contoursR, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//cout << "��ת��R��������������Ϊ" << contoursR.size() << endl;

	/*namedWindow("binary_reverse", WINDOW_NORMAL);
	imshow("binary_reverse", binary_reverse);*/
	threshold(R, R, 144, 255, THRESH_BINARY);
	int val = countNonZero(R);
	//cout << val << endl;
	if ((val > 200) && (val < 250)&&(contoursR.size()==3))
	{
		return 0;
	}
	else
	{
		return 1;
	}
    //namedWindow("R", WINDOW_NORMAL);
	//imshow("R", R);
	
}



