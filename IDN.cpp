#include"IDN.h"
using namespace std;
using namespace cv;

void Curve(Mat& img, int num) {	//��ͨ���ںϷ���
	Mat dstImage;
	vector<Mat> g_vChannels;

	//����ͨ��
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
	//ͼƬ��ʼ��
	Mat image_IDN, image_Flower, image_TUN,image_MMR,image_ZAF, result;
	double maxVal;
	image_IDN = imread("IDN_UV.jpg");
	image_Flower = imread("IDN_FLOWER.jpg",0);
	image_TUN = imread("TUN_UV.jpg",0);
	image_MMR = imread("MMR_UV.jpg");
	image_ZAF = imread("ZAF_UV.png");

	imshow("IDN_UV",image_IDN);
	Curve(image_IDN,1);
	//GaussianBlur(image_IDN, image_IDN, Size(3, 3), 1);//��˹�˲�
	threshold(image_IDN, image_IDN, 0, 255, THRESH_OTSU);//��ֵ��
	imshow("IDN_R-G", image_IDN);
	matchTemplate(image_IDN, image_Flower, result, TM_CCOEFF_NORMED);//���ƶ�ƥ��
	minMaxLoc(result, 0, &maxVal, 0, 0);				  //ȡƥ�����������ֵ
	imshow("IDN_Flower", image_Flower);
	//for (int i = 0; i < image_Flower.rows; i++) {
	//	for (int j = 0; j < image_Flower.cols; j++) {
	//		cout << int(image_Flower.at<uchar>(i, j)) << " ";
	//	}
	//	cout << endl;
	//}
	cout << "ģ��ƥ�仨�ƽ����" << maxVal << endl;

	imshow("TUN_UV", image_TUN);
	medianBlur(image_TUN, image_TUN, 7);//��ֵ�˲�,ksize�����Ǵ���1������
	threshold(image_TUN, image_TUN, 0, 255, THRESH_OTSU);//��ֵ��
	imshow("TUN_��ֵͼ", image_TUN);
	Rect rect2(40, 300, 60, 80);
	Mat image_ban1 = image_TUN(rect2);
	imshow("TUN_���ͼ", image_ban1);

	Curve(image_MMR,2);
	threshold(image_MMR, image_MMR, 170, 255, THRESH_BINARY);//��ֵ��
	medianBlur(image_MMR, image_MMR, 3);//��ֵ�˲�,ksize�����Ǵ���1������
	Mat element1 = getStructuringElement(MORPH_ELLIPSE, Size(9, 9));//��ȡ�Զ����,��һ���������ں˵���״,����: MORPH_RECT,��Բ��: MORPH_ELLIPSE
	Mat out, in;
//	erode(image_MMR, out, element1);//���и�ʴ����
	dilate(image_MMR, in, element1);//�������Ͳ���
	imshow("MMR_UV", in);
	//indContours(InputOutputArray image, OutputArrayOfArrays contours,OutputArray hierarchy, int mode, int method, Point offset = Point());//������ȡ����
	
	//imshow("ZAF_UV", image_ZAF);
	Curve(image_ZAF, 3);
	imshow("ZAF_UV", image_ZAF);
	threshold(image_ZAF, image_ZAF, 0, 255, THRESH_OTSU);//��ֵ��
	imshow("ZAF_��ֵͼ", image_ZAF);

	cv::waitKey(0);
	return 0;
}