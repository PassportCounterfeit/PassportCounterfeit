#include"IDN.h"
using namespace std;
using namespace cv;

void Curve(Mat& img, int num) {	//多通道融合分离
	Mat dstImage;
	vector<Mat> g_vChannels;

	//分离通道
	split(img, g_vChannels);
	Mat imageBlueChannel = g_vChannels.at(0);
	Mat imageGreenChannel = g_vChannels.at(1);
	Mat imageRedChannel = g_vChannels.at(2);
	if (num == 1) {
		img = imageRedChannel - imageGreenChannel;
	}
	else if (num == 2) {
		img = imageGreenChannel;
	}
	else if (num == 3) {
		img = imageBlueChannel - imageRedChannel;
	}
	imshow("Blue", imageBlueChannel);
	imshow("Greeen", imageGreenChannel);
	imshow("Red", imageRedChannel);
	//threshold(imageRGChannel, imageRGChannel, 0, 255, THRESH_OTSU);
//	imshow("R-G", img2);
}

int main() {
	//图片初始化
	Mat image_IDN, image_Flower, image_TUN,image_MMR,image_ZAF, result;
	double maxVal;
	image_IDN = imread("IDN_UV.jpg");
	image_Flower = imread("IDN_FLOWER.jpg",0);
	image_TUN = imread("TUN_UV.jpg",0);
	image_MMR = imread("MMR_UV.jpg");
	image_ZAF = imread("ZAF_UV.png");

	imshow("IDN_UV",image_IDN);
	Curve(image_IDN,1);
	//GaussianBlur(image_IDN, image_IDN, Size(3, 3), 1);//高斯滤波
	threshold(image_IDN, image_IDN, 0, 255, THRESH_OTSU);//二值化
	imshow("IDN_R-G", image_IDN);
	matchTemplate(image_IDN, image_Flower, result, TM_CCOEFF_NORMED);//相似度匹配
	minMaxLoc(result, 0, &maxVal, 0, 0);				  //取匹配结果矩阵最大值
	imshow("IDN_Flower", image_Flower);
	//for (int i = 0; i < image_Flower.rows; i++) {
	//	for (int j = 0; j < image_Flower.cols; j++) {
	//		cout << int(image_Flower.at<uchar>(i, j)) << " ";
	//	}
	//	cout << endl;
	//}
	cout << "模板匹配花纹结果：" << maxVal << endl;

	imshow("TUN_UV", image_TUN);
	medianBlur(image_TUN, image_TUN, 7);//中值滤波,ksize必须是大于1的奇数
	threshold(image_TUN, image_TUN, 0, 255, THRESH_OTSU);//二值化
	imshow("TUN_二值图", image_TUN);
	Rect rect2(40, 300, 60, 80);
	Mat image_ban1 = image_TUN(rect2);
	imshow("TUN_检测图", image_ban1);

	Curve(image_MMR,2);
	threshold(image_MMR, image_MMR, 170, 255, THRESH_BINARY);//二值化
	medianBlur(image_MMR, image_MMR, 3);//中值滤波,ksize必须是大于1的奇数
	Mat element1 = getStructuringElement(MORPH_ELLIPSE, Size(9, 9));//获取自定义核,第一个参数是内核的形状,矩形: MORPH_RECT,椭圆形: MORPH_ELLIPSE
	Mat out, in;
//	erode(image_MMR, out, element1);//进行腐蚀操作
	dilate(image_MMR, in, element1);//进行膨胀操作
	imshow("MMR_UV", in);
	//indContours(InputOutputArray image, OutputArrayOfArrays contours,OutputArray hierarchy, int mode, int method, Point offset = Point());//轮廓提取函数
	
	//imshow("ZAF_UV", image_ZAF);
	Curve(image_ZAF, 3);
	imshow("ZAF_UV", image_ZAF);
	threshold(image_ZAF, image_ZAF, 0, 255, THRESH_OTSU);//二值化
	imshow("ZAF_二值图", image_ZAF);

	cv::waitKey(0);
	return 0;
}