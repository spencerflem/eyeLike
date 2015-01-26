#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <queue>
#include <stdio.h>

#include "constants.h"
#include "helpers.h"

#include "mapToGrid.h"

cv::Point mapToGrid(EyeData eyeData) {
	cv::Point outputPoint;
	outputPoint = eyeData.rightPupil;
	return outputPoint;
}