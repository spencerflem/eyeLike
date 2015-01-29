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

/*
ALL DISPLAY COMMANDS
circle(debugFace, rightPupil, 3, 1234);
circle(debugFace, leftPupil, 3, 1234);

imshow(face_window_name, faceROI);

rectangle(face,eye,1234);


cv::namedWindow(main_window_name,CV_WINDOW_NORMAL);
cv::moveWindow(main_window_name, 400, 100);
cv::namedWindow(face_window_name,CV_WINDOW_NORMAL);
cv::moveWindow(face_window_name, 10, 100);
cv::namedWindow("Right Eye",CV_WINDOW_NORMAL);
cv::moveWindow("Right Eye", 10, 600);
cv::namedWindow("Left Eye",CV_WINDOW_NORMAL);
cv::moveWindow("Left Eye", 10, 800);

why???
cv::namedWindow("aa",CV_WINDOW_NORMAL);
cv::moveWindow("aa", 10, 800);
cv::namedWindow("aaa",CV_WINDOW_NORMAL);
cv::moveWindow("aaa", 10, 800);

ellipse(skinCrCbHist, cv::Point(113, 155.6), cv::Size(23.4, 15.2),
        43.0, 0.0, 360.0, cv::Scalar(255, 255, 255), -1);

imshow(debugWindow,gradientX);

imshow(main_window_name,debugImage);

rectangle(mat,cv::Rect(0,0,mat.cols,mat.rows),255);

for( int i = 0; i < faces.size(); i++ )
{
  rectangle(debugImage, faces[i], 1234);
}

*/

#include <stdlib.h>
#include <time.h>
#include <string> 

void displayText(NumData numData) {
	printf("Face size: %ix%i, Eye sizes: %ix%i, %ix%i, Eye points: (%i,%i), (%i,%i)\n", 
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

	imshow(kface_window_name,faceFrame);
	//displayText(numData);
}

void displayFrame(cv::Mat frame) {
	imshow(kmain_window_name,frame);
}

void printFrame(cv::Mat frame, bool glare) {
	srand (time(NULL));
	std::string randomNumber = std::to_string(static_cast<unsigned long long>(rand()));
	std::string imgName;
	if (glare) {
		imgName = "gframe-" + randomNumber + ".png";
	}
	else {
		imgName = "hframe-" + randomNumber + ".png";
	}
	std::cout << imgName;
	imwrite(imgName,frame);
}