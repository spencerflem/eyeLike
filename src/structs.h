#ifndef STRUCTS_H
#define STRUCTS_H

struct NumData {
	cv::Rect face;
	cv::Rect leftEyeRegion;
	cv::Rect rightEyeRegion;
	cv::Point leftPupil;
	cv::Point rightPupil;
};

#endif