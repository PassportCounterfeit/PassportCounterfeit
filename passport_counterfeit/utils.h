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
/// <summary>
/// 多通道融合分离
/// </summary>
/// <param name="src">原图,RBG彩色图</param>
/// <param name="dst">输出图像，灰度图</param>
/// <param name="num">差分类型</param>
void curve(const Mat& src, Mat& dst, CurveType num);
/// <summary>
/// 快速模板匹配，对matchTemplate函数的封装
/// </summary>
/// <param name="src">原图</param>
/// <param name="patternPath">匹配图</param>
/// <param name="maxVal">最大值</param>
/// <param name="minVal">最小值</param>
/// <param name="method">匹配方式</param>
void quickMatchTemplate(InputArray src,const string& patternPath,double* maxVal,double* minVal, TemplateMatchModes method);
