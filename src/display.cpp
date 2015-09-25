#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <queue>
#include <stdio.h>

#include "constants.h"
#include "helpers.h"
#include "structs.h"

#include "display.h"

#include <stdlib.h>
#include <time.h>
#include <string> 

void displayText(NumData numData) {
	printf("Face size: %ix%i, Eye sizes: %ix%i&%ix%i, Eye points: (%i,%i)&(%i,%i)\n", 
		numData.face.width,
		numData.face.height,
		numData.leftEyeRegion.width,
		numData.leftEyeRegion.height,
		numData.rightEyeRegion.width,
		numData.rightEyeRegion.height,
		numData.leftPupil.x,
		numData.leftPupil.y,
		numData.rightPupil.x,
		numData.rightPupil.y);
}


void display(cv::Mat frame, NumData numData, int gridNumber) {
	imshow(kmain_window_name,frame);

	cv::Mat faceFrame = frame(numData.face);

	circle(faceFrame, numData.rightPupil, 3, 1234);
	circle(faceFrame, numData.leftPupil, 3, 1234);

	cv::Mat eyeROI = faceFrame(numData.rightEyeRegion);

	/*
	cv::Mat thresh;
	std::vector<cv::Mat> rgbChannels(3);
    cv::split(faceFrame, rgbChannels);
    cv::Mat faceFrame_gray = rgbChannels[2];
	double threshValue = 125;
	threshold(faceFrame_gray, thresh, threshValue, 120, 0);
	*/
	//circle(faceFrame, numData.leftPupil, 3, 1234);
	//circle(faceFrame, numData.rightPupil, 3, 1234);

	//imshow(kface_window_name,faceFrame);

	imshow(kright_eye_window_name,eyeROI);
	//displayText(numData);
}

void displayFrame(cv::Mat frame) {
	imshow(kmain_window_name,frame);
}

void printFrame(cv::Mat frame, char id) {
	srand (time(NULL));
	std::stringstream ss;
	std::string strid;
	ss << id;
	ss >> strid;
	std::string randomNumber = std::to_string(static_cast<unsigned long long>(rand()));
	std::string imgName;
	imgName = "";
	//imgName += "C:/Users/Katherine Hoffman/";
	imgName += strid;
	imgName += randomNumber;
	imgName += ".png";
	std::cout << imgName;
	imwrite(imgName,frame);
}