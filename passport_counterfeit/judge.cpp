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

	Mat ImageContours = Mat::zeros(grayaomen.size(), CV_8UC1);  //绘制
	Mat ImgContours = Mat::zeros(grayaomen.size(), CV_8UC1);

	vector<vector<Point>>::iterator k;                    //迭代器，访问容器数据

	for (k = contours.begin(); k != contours.end();)      //遍历容器,设置面积因子
	{
		if (contourArea(*k, false) < 2500)
		{//删除指定元素，返回指向删除元素下一个元素位置的迭代器
			k = contours.erase(k);
		}
		else
			++k;
	}

	//contours[i]代表第i个轮廓，contours[i].size()代表第i个轮廓上所有的像素点
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
		{
			//获取轮廓上点的坐标
			Point P = Point(contours[i][j].x, contours[i][j].y);
			ImgContours.at<uchar>(P) = 255;
		}
		drawContours(ImageContours, contours, i, Scalar(255), -1, 8);
	}
	dilate(ImageContours, ImageContours, Mat());
	Canny(ImageContours, ImageContours, 10, 250, 5);
	//霍夫圆检测
	vector<Vec3f> pcircles;
	//输入，输出，方法（类型）-HOUGH_GRADIENT，dp(dp=1时表示霍夫空间与输入图像空间的大小一致，dp=2时霍夫空间是输入图像空间的一半，以此类推)，最短距离-可以分辨是两个圆否 则认为是同心圆 ,边缘检测时使用Canny算子的高阈值，中心点累加器阈值—候选圆心（霍夫空间内累加和大于该阈值的点就对应于圆心），检测到圆的最小半径，检测到圆的的最大半径
	HoughCircles(ImageContours, pcircles, HOUGH_GRADIENT, 1, 60, 100, 13, 80, 150);
	//if(pcircles.size()==)
	/*下列for循环可以将检测出的圆形在图像中画出来*/
	//for (size_t i = 0; i < pcircles.size(); i++)//size_t 无符号整数 unsigned int 
	//{
	//	//提取圆心坐标
	//	Point center(cvRound(pcircles[i][0]), cvRound(pcircles[i][1]));//cvRound 返回和参数最接近的整数值
	//	//提取半径
	//	int radius = cvRound(pcircles[i][2]);
	//	//圆心
	//	circle(aomenwi, center, 3, Scalar(0, 255, 0), -1, 8, 0);
	//	//圆
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