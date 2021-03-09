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
/// <summary>
/// 感知哈希算法
/// 比较两个图像的相似程度
/// 输入图像应为灰度图
/// </summary>
/// <param name="src">用于比较的原图</param>
/// <param name="target">用于比较的目标图</param>
/// <returns>64个像素中不同的像素个数，5个及以下说明相似度较高，10个及以上说明相似度较低</returns>
int perceptualHash(const Mat& src, const Mat& target);
