#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <queue>
#include <stdio.h>

#include "constants.h"
#include "helpers.h"

#include "mapToGrid.h"


cv::Mat detectGlare(cv::Mat eyeROI, cv::Point pupil, bool isLeft, double faceWidth) {

	cv::Mat glareMat;
	//Gausian Blur
	if (kSmoothFaceImage) {
		double sigma = 5;
		GaussianBlur( eyeROI, eyeROI, cv::Size( 0, 0 ), sigma);
	}
	std::vector<cv::Mat> rgbChannels(3);
    cv::split(eyeROI, rgbChannels);
    cv::Mat eyeROI_gray = rgbChannels[2];

	cv::Mat thresh;
	uchar thresholdThreshold = eyeROI_gray.at<uchar>(pupil);
	std::cout << thresholdThreshold;
	threshold(eyeROI_gray, thresh, thresholdThreshold, 255, 1);

	cv::Point maxP;
    double maxVal;
	cv::minMaxLoc(eyeROI_gray,NULL,&maxVal,NULL,&maxP);
	//std::cout << maxVal << " -- " << maxP;


	//lame
	cv::Mat outSum = cv::Mat::zeros(eyeROI.rows,eyeROI.cols,CV_64F);

	//move to display

	circle(eyeROI_gray, maxP, 3, 1234);
	imshow("aa", eyeROI_gray);
	imshow("aaa", thresh);

	if(isLeft) {
		imshow(kleft_eye_window_name,eyeROI);
	}
	else {
		imshow(kright_eye_window_name,eyeROI);
	}
	return glareMat;
}

int mapToGrid(cv::Mat frame, NumData numData) {
	cv::Mat leftGlareMat;
	cv::Mat rightGlareMat;
	leftGlareMat = detectGlare((frame(numData.face))(numData.leftEyeRegion), numData.leftPupil, true, numData.face.width);
	rightGlareMat = detectGlare((frame(numData.face))(numData.rightEyeRegion), numData.rightPupil, false, numData.face.width);



	return 0;
}