#pragma once
#include "main.h"
enum CurveType {
	B = 0,
	R_DIFF_G = 1,
	G = 2,
	B_DIFF_R = 3,
	R = 4,
	R_DIFF_B = 5,
	G_DIFF_B = 6
};
/// <summary>
/// ͳ�Ʒ������������ظ���
/// �����ͼ��ӦΪ��ͨ��ͼ��
/// </summary>
/// <param name="img">�����ͼ��</param>
/// <param name="minValue">����ֵ��С��ֵ</param>
/// <param name="maxValue">����ֵ�����ֵ</param>
/// <returns>�������������ظ���</returns>
int pixelCount(Mat& img,uchar minValue,uchar maxValue);
/// <summary>
/// ��֪��ϣ�㷨
/// �Ƚ�����ͼ������Ƴ̶�
/// ����ͼ��ӦΪ�Ҷ�ͼ
/// </summary>
/// <param name="src">���ڱȽϵ�ԭͼ</param>
/// <param name="target">���ڱȽϵ�Ŀ��ͼ</param>
/// <returns>64�������в�ͬ�����ظ�����5��������˵�����ƶȽϸߣ�10��������˵�����ƶȽϵ�</returns>
int perceptualHash(const Mat& src, const Mat& target);
/// <summary>
/// ��ͨ���ںϷ���
/// </summary>
/// <param name="src">ԭͼ,RBG��ɫͼ</param>
/// <param name="dst">���ͼ�񣬻Ҷ�ͼ</param>
/// <param name="num">�������</param>
void curve(const Mat& src, Mat& dst, CurveType num);
/// <summary>
/// ����ģ��ƥ�䣬��matchTemplate�����ķ�װ
/// </summary>
/// <param name="src">ԭͼ</param>
/// <param name="patternPath">ƥ��ͼ</param>
/// <param name="maxVal">���ֵ</param>
/// <param name="minVal">��Сֵ</param>
/// <param name="method">ƥ�䷽ʽ</param>
void quickMatchTemplate(InputArray src,const string& patternPath,double* maxVal,double* minVal, TemplateMatchModes method);
