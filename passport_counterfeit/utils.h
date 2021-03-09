#pragma once
#include "main.h"
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
