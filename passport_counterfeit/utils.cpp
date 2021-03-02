#include "utils.h"


int pixelCount(Mat& img, uchar minValue, uchar maxValue) {
	int res = 0;
	for (Mat_<uchar>::iterator it = img.begin<uchar>(); it != img.end<uchar>(); it++) {
		if ((*it) >= minValue && (*it) <= maxValue)
			res++;
	}
	return res;
}