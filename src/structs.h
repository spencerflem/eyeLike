#ifndef STRUCTS_H
#define STRUCTS_H

struct EyeData {
	cv::Rect face;
	cv::Rect leftEyeRegion;
	cv::Rect rightEyeRegion;
	cv::Point leftPupil;
	cv::Point rightPupil;
};

struct DisplayData {
	cv::Mat debugImage;
	cv::Mat faceROI;
	cv::Mat leftEye;
	cv::Mat rightEye;
};

#endif