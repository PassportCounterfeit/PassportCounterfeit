#pragma once
#include "main.h"
/// <summary>
/// 统计符合条件的像素个数
/// 输入的图像应为单通道图像
/// </summary>
/// <param name="img">输入的图像</param>
/// <param name="minValue">像素值最小阈值</param>
/// <param name="maxValue">像素值最大阈值</param>
/// <returns>符合条件的像素个数</returns>
int pixelCount(Mat& img,uchar minValue,uchar maxValue);
