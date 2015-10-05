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

#include "findEyeCenter.h"

//check if glare at all?
//if so, add to numData
//train numData with machne learning?
//guess reigon
//send to glas
//record result
//if good - keep!
//if not - try neighboring square & repeat!


//return point or bool?
//if cv::Point == 'null?' and keep point? YES OR NO?
bool isGlare(cv::Mat eyeROI, cv::Point pupil, bool isLeft, double faceWidth, int threshNumber) {

	//get images catagorized by glare or not to allow comparison

	//cv::Mat glareMat;
	//Gausian Blur
	/*if (kSmoothFaceImage) {
		double sigma = 5;
		GaussianBlur( eyeROI, eyeROI, cv::Size( 0, 0 ), sigma);
	}*/
	std::vector<cv::Mat> rgbChannels(3);
    cv::split(eyeROI, rgbChannels);
    cv::Mat eyeROI_gray = rgbChannels[2];

	cv::Mat thresh;
	
	cv::Mat eq;
	cv::equalizeHist(eyeROI_gray, eq);

	threshold(eq, thresh, threshNumber, 255, 0);

	cv::Mat floodFilled;
	thresh.copyTo(floodFilled);

	cv::floodFill(floodFilled, cv::Point(0,0), 50, (cv::Rect*)0, cv::Scalar(), 1);


	if(!isLeft) {
		//imshow("aa", eyeROI_gray);
		//imshow("aaa", thresh);
		imshow("ff", floodFilled);

		cv::Mat combined;
		std::vector<cv::Mat> all;

		cv::Mat combinedRed;
		cv::multiply(thresh, eyeROI_gray, combinedRed);

        all.push_back(rgbChannels[0]);
        all.push_back(rgbChannels[1]);
        all.push_back(thresh);

		cv::merge(all,combined);

		imshow("COMBINED",combined);

	}
	//imwrite("thresh.png",thresh);
	//imwrite("eyeROI.png",eyeROI_gray);


	if(isLeft) {
		//imshow(kleft_eye_window_name,eyeROI);
	}
	else {
		//imshow(kright_eye_window_name,eyeROI);
	}
	
	return true;
}

int mapToGrid(cv::Mat frame, NumData numData, int threshNumber) { //INCLUDE PAST HISTORY SOMEHOW?
	int gridNumber;
	bool isLeftGlare;
	bool isRightGlare;
	//isLeftGlare = isGlare((frame(numData.face))(numData.leftEyeRegion), numData.leftPupil, true, numData.face.width, threshNumber);
	isRightGlare = isGlare((frame(numData.face))(numData.rightEyeRegion), numData.rightPupil, false, numData.face.width, threshNumber);



	if (isLeftGlare == true || isRightGlare == true){
		//guess spot
	}
	//If board worked - there would be a kNN algorhm here which would self correct based on whether the board's change affected the detected glare
	
	cv::rectangle(frame,numData.face, 255);
	


	gridNumber = 0;
	return gridNumber;
}