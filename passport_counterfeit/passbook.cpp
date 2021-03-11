#include<opencv2/opencv.hpp>
#include "passbook.h"
using namespace std;
using namespace cv;

Mat numReturn(const char* pic)
{
	Mat picture = imread(pic);
	return numReturn(picture);
}

Mat numReturn(Mat pic)
{
	vector<Mat> vec;
	split(pic, vec); //通道分离
	Mat grayPic, grayPicr;
	Mat imageReturn;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	cv::Scalar     mean, mean1;
	cv::Scalar     dev, dev1;

	grayPic = vec[1];
	grayPicr = vec[2];
	cv::meanStdDev(grayPic, mean, dev);
	cv::meanStdDev(grayPicr, mean1, dev1);
	float m1 = mean.val[0];
	float m2 = mean1.val[0];
	//cout << m1 << "  " << m2 << endl;
	char color = ' ';

	if (m1 > m2)
		color = 'g';
	else
		color = 'r';
	//cout << color << endl;
	switch (color)
	{
	case 'g':
		//cvtColor(pic, grayPic, COLOR_BGR2GRAY);
	{
		cv::Mat resultImage = cv::Mat::zeros(grayPic.size(), grayPic.type());
		grayPic.convertTo(resultImage, CV_32F);
		resultImage = resultImage + 1;
		cv::log(resultImage, resultImage);
		cv::normalize(resultImage, resultImage, 0, 255, cv::NORM_MINMAX);
		cv::convertScaleAbs(resultImage, resultImage);

		//imshow("pic1", resultImage);
		Mat elementerode = getStructuringElement(MORPH_RECT, Size(30, 9));
		Mat elementdilate = getStructuringElement(MORPH_RECT, Size(24, 4));

		medianBlur(resultImage, resultImage, 5);
		medianBlur(resultImage, resultImage, 5);
		medianBlur(resultImage, resultImage, 5);
		//GaussianBlur(resultImage, resultImage, Size(3, 3), 0, 0, BORDER_DEFAULT);
		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y;
		Sobel(resultImage, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
		Sobel(resultImage, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);

		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);
		Mat grad;
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

		adaptiveThreshold(grad, grad, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 5);
		//dilate(grad, grad, Mat());
		//dilate(grad, grad, Mat());
		//erode(grad, grad, Mat());
		erode(grad, grad, Mat());
		medianBlur(grad, grad, 5);
		medianBlur(grad, grad, 5);
		medianBlur(grad, grad, 5);
		//imshow("pic",resultImage);
		erode(grad, grad, elementerode);
		dilate(grad, grad, elementdilate);
		erode(grad, grad, elementerode);
		dilate(grad, grad, elementdilate);
		dilate(grad, grad, elementdilate);

		Mat grad_inverse = 255 - grad;
		//imshow("hell0", grad_inverse);
		vector<Rect> rects;
		//1.查找轮廓
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(grad, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));

		for (int i = 0; i < contours.size(); i++)
		{
			double area = contourArea(contours[i]);
			if (area < 10000)
				continue;
			Rect rect = boundingRect(contours[i]);
			int m_width = rect.width;
			int m_height = rect.height;
			if (m_height * 10 < m_width)
				continue;
			rects.push_back(rect);

		}
		Rect zf_rect;
		int temp = 0;
		int max = rects[0].tl().y;
		for (int i = 0; i < rects.size(); i++)
		{
			if (rects[i].tl().y > max)
			{
				max = rects[i].tl().y;
				temp = i;
			}
		}
		zf_rect = rects[temp];
		Rect finrect = Rect(zf_rect.x - 15, zf_rect.y - 3, zf_rect.width + 20, zf_rect.height + 3);
		imageReturn = pic(finrect);
		//rectangle(pic, zf_rect, Scalar(0, 0, 255), 2, 8, 0);
		/*cout << max << endl;
		cout << temp << endl;
		cout << rects.size() << endl;
		cout << rects[0].tl() << endl;
		cout << rects[1].tl() << endl;
		cout << rects[2].tl() << endl;*/
		//imshow("grad", pic);

		//waitKey(0);
		//system("pause");
		break;
	}
	case 'r':
		Mat gray = grayPicr;
		Mat elementerode = getStructuringElement(MORPH_RECT, Size(30, 9));
		Mat elementdilate = getStructuringElement(MORPH_RECT, Size(24, 4));
		medianBlur(gray, gray, 5);
		adaptiveThreshold(gray, gray, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 5);
		erode(gray, gray, Mat());
		medianBlur(gray, gray, 5);
		medianBlur(gray, gray, 5);
		dilate(gray, gray, Mat());
		erode(gray, gray, elementerode);
		Mat gray_inverse = 255 - gray;
		vector<Rect> rects;
		//1.查找轮廓
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(gray, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));

		for (int i = 0; i < contours.size(); i++)
		{
			double area = contourArea(contours[i]);
			if (area < 10000)
				continue;
			Rect rect = boundingRect(contours[i]);
			int m_width = rect.width;
			int m_height = rect.height;
			if (m_height * 10 < m_width)
				continue;
			if (m_width > 500)
				continue; 
			rects.push_back(rect);

		}
		Rect zf_rect;
		int temp = 0;
		int max = rects[0].tl().y;
		for (int i = 0; i < rects.size(); i++)
		{
			if (rects[i].tl().y > max)
			{
				max = rects[i].tl().y;
				temp = i;
			}
		}
		zf_rect = rects[temp];
		imageReturn = pic(zf_rect);
		/*rectangle(pic, zf_rect, Scalar(0, 0, 255), 2, 8, 0);
		imshow("gray", pic);
		waitKey(0);*/
		break;
	}
	return imageReturn;
}
