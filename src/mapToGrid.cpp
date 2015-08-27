#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"

#include <iostream>
#include <queue>
#include <stdio.h>

#include "constants.h"
#include "helpers.h"

#include "mapToGrid.h"
#include "display.h"


cv::Point detectGlare(cv::Mat eyeROI, cv::Point pupil, bool isLeft, double faceWidth) {

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
	
	cv::Mat eq;
	cv::equalizeHist(eyeROI_gray, eq);

	threshold(eq, thresh, 35, 255, 0);

	circle(eyeROI_gray, pupil, 3, 1234);

	imshow("aa", eyeROI_gray);
	imshow("aaa", thresh);
	imwrite("thresh.png",thresh);
	imwrite("eyeROI.png",eyeROI_gray);


	if(isLeft) {
		imshow(kleft_eye_window_name,eyeROI);
	}
	else {
		imshow(kright_eye_window_name,eyeROI);
	}
	return pupil;
}

int mapToGrid(cv::Mat frame, NumData numData) {
	cv::Point leftGlarePoint;
	cv::Point rightGlarePoint;
	leftGlarePoint = detectGlare((frame(numData.face))(numData.leftEyeRegion), numData.leftPupil, true, numData.face.width);
	rightGlarePoint = detectGlare((frame(numData.face))(numData.rightEyeRegion), numData.rightPupil, false, numData.face.width);

	//If board worked - there would be a kNN algorhm here which would self correct based on whether the board's change affected the detected glare
	
	cv::rectangle(frame,numData.face, 255);
	imwrite("frame.png",frame);
	return 0;
}