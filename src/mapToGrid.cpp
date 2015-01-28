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

	//Gausian Blur
	if (kSmoothFaceImage) {
		double sigma = kSmoothFaceFactor * faceWidth;
		GaussianBlur( eyeROI, eyeROI, cv::Size( 0, 0 ), sigma);
	}
	cv::Mat glareMat = cv::Mat::zeros(eyeROI.rows,eyeROI.cols,CV_32F);
	cv::Point maxP;
    double maxVal;
	cv::minMaxLoc(eyeROI,NULL,&maxVal,NULL,&maxP);

	//move to display
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