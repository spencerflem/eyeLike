#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "findEyeCenter.h"
#include "mapToGrid.h"
#include "structs.h"
#include "display.h"

//REDUCE LAG ON IMAGE!

/** Constants **/


/** Function Headers */
void detectAndDisplay( cv::Mat frame );

/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
cv::String face_cascade_name = "C:/Users/Katherine Hoffman/Desktop/haarcascade_frontalface_alt.xml";
cv::String face_cascade_name_two = "C:/Users/Me/Desktop/haarcascade_frontalface_alt.xml";
cv::CascadeClassifier face_cascade;
cv::RNG rng(12345);
cv::Mat debugImage;
cv::Mat skinCrCbHist = cv::Mat::zeros(cv::Size(256, 256), CV_8UC1);
int frameNumber = 0;
int threshNumber = 10;

/**
 * @function main
 */
int main( int argc, const char** argv ) {
  cv::VideoCapture capture;
  cv::Mat frame;

  // Load the cascades
  if( !face_cascade.load( face_cascade_name) && !face_cascade.load( face_cascade_name_two)) {
	printf("--(!)Error loading face cascade, please change face_cascade_name in source code.\n");
	return -1;
  }

  cv::namedWindow(kmain_window_name,CV_WINDOW_NORMAL);
  cv::moveWindow(kmain_window_name, 400, 100);
  cv::namedWindow(kface_window_name,CV_WINDOW_NORMAL);
  cv::moveWindow(kface_window_name, 10, 100);
  //cv::namedWindow(kleft_eye_window_name,CV_WINDOW_NORMAL);
  //cv::moveWindow(kleft_eye_window_name, 10, 100);
  cv::namedWindow(kright_eye_window_name,CV_WINDOW_NORMAL);
  cv::moveWindow(kright_eye_window_name, 10, 100);
  //cv::namedWindow(debugWindow + " Mask",CV_WINDOW_NORMAL);
  //cv::namedWindow("Right Eye",CV_WINDOW_NORMAL);
  //cv::moveWindow("Right Eye", 10, 600);
  //cv::namedWindow("Left Eye",CV_WINDOW_NORMAL);
  //cv::moveWindow("Left Eye", 10, 800);
  //cv::namedWindow("aa",CV_WINDOW_NORMAL);
  //cv::moveWindow("aa", 10, 200);
  //cv::namedWindow("aaa",CV_WINDOW_NORMAL);
  //cv::moveWindow("aaa", 10, 300);
  cv::namedWindow("ff",CV_WINDOW_NORMAL);
  cv::moveWindow("ff", 10, 500);

  ellipse(skinCrCbHist, cv::Point(113, 155.6), cv::Size(23.4, 15.2),
          43.0, 0.0, 360.0, cv::Scalar(255, 255, 255), -1);

   // Read the video stream
  capture.open(-1);
  capture >> frame;
  //frame = cv::imread("g32756.png");
  //cv::flip(frame, frame, 1);
	frame = cv::imread("default.png");
	cv::flip(frame, frame, 1);
  while( true ) {
	  if( capture.isOpened() ) {
		  capture >> frame;
		  cv::flip(frame, frame, 1);
	  }
	  
      int c = cv::waitKey(10);
	  char gFrame = 'g';
	  char nFrame = 'n';
	  char xFrame = (char)c;
	  printf("%c", xFrame);
	  
      if( (char)c == 'c' ) { break; }
      else if( (char)c == 'f' ) {
        imwrite("frame.png",frame);
      }
	  else if( (char)c == 'q' ) {
		  capture.release();
      }
	  else if( (char)c == 'w' ) {
		  capture.open(-1);
      }
	  else if( (char)c == '=' ) {
        printFrame(frame, gFrame);
      }
	  else if( (char)c == '-' ) {
        printFrame(frame, nFrame);
      }
	  else if( (char)c == 'g' ) {
        frame = cv::imread("g32756.png");
		cv::flip(frame, frame, 1);
      }
	  else if( (char)c == 'n' ) {
        frame = cv::imread("n32734.png");
		cv::flip(frame, frame, 1);
      }
	  else if( (char)c == '0') {
		if(threshNumber > 10) {
			threshNumber =  0;
		}
		else if (threshNumber < 10) {
			threshNumber = threshNumber*10;
			threshNumber += 0;
		}
	  }
	  else if( (char)c == '9') {
		if(threshNumber > 10) {
			threshNumber =  9;
		}
		else if (threshNumber < 10) {
			threshNumber = threshNumber*10;
			threshNumber += 9;
		}
	  }
	  else if( (char)c == '8') {
		if(threshNumber > 10) {
			threshNumber =  8;
		}
		else if (threshNumber < 10) {
			threshNumber = threshNumber*10;
			threshNumber += 8;
		}
	  }
	  else if( (char)c == '7') {
		if(threshNumber > 10) {
			threshNumber =  7;
		}
		else if (threshNumber < 10) {
			threshNumber = threshNumber*10;
			threshNumber += 7;
		}
	  }
	  else if( (char)c == '6') {
		if(threshNumber > 10) {
			threshNumber =  6;
		}
		else if (threshNumber < 10) {
			threshNumber = threshNumber*10;
			threshNumber += 6;
		}
	  }
	  else if( (char)c == '1') {
		if(threshNumber > 10) {
			threshNumber =  1;
		}
		else if (threshNumber < 10) {
			threshNumber = threshNumber*10;
			threshNumber += 1;
		}
	  }
	  else if( (char)c == '2') {
		if(threshNumber > 10) {
			threshNumber =  2;
		}
		else if (threshNumber < 10) {
			threshNumber = threshNumber*10;
			threshNumber += 2;
		}
	  }
	  else if( (char)c == '3') {
		if(threshNumber > 10) {
			threshNumber =  3;
		}
		else if (threshNumber < 10) {
			threshNumber = threshNumber*10;
			threshNumber += 3;
		}
	  }
	  else if( (char)c == '4') {
		if(threshNumber > 10) {
			threshNumber =  4;
		}
		else if (threshNumber < 10) {
			threshNumber = threshNumber*10;
			threshNumber += 4;
		}
	  }
	  else if( (char)c == '5') {
		if(threshNumber > 10) {
			threshNumber =  5;
		}
		else if (threshNumber < 10) {
			threshNumber = threshNumber*10;
			threshNumber += 5;
		}
	  }

	  else if( (char)c == '!') {
		std::string path;
		std::cin >> path;
		frame = cv::imread(path);
		cv::flip(frame, frame, 1);
	  }

	  //printf("%d",threshNumber);
	  else if ( c != -1) {
		  printFrame(frame, xFrame);
	  }
	  if( !frame.empty() ) {
        detectAndDisplay( frame );
      }
      else {
        printf(" --(!) No captured frame -- Break!");
        break;
      }

    }
  return 0;
}

NumData findEyes(cv::Mat frame_gray, cv::Rect face) {
  cv::Mat faceROI = frame_gray(face);
  cv::Mat debugFace = faceROI;

  if (kSmoothFaceImage) {
    double sigma = kSmoothFaceFactor * face.width;
    GaussianBlur( faceROI, faceROI, cv::Size( 0, 0 ), sigma);
  }
  //-- Find eye regions and draw them
  int eye_region_width = face.width * (kEyePercentWidth/100.0);
  int eye_region_height = face.width * (kEyePercentHeight/100.0);
  int eye_region_top = face.height * (kEyePercentTop/100.0);
  cv::Rect leftEyeRegion(face.width*(kEyePercentSide/100.0),
                         eye_region_top,eye_region_width,eye_region_height);
  cv::Rect rightEyeRegion(face.width - eye_region_width - face.width*(kEyePercentSide/100.0),
                          eye_region_top,eye_region_width,eye_region_height);

  //-- Find Eye Centers
  cv::Point leftPupil = findEyeCenter(faceROI,leftEyeRegion,"Left Eye");
  cv::Point rightPupil = findEyeCenter(faceROI,rightEyeRegion,"Right Eye");
  // change eye centers to face coordinates
  rightPupil.x += rightEyeRegion.x;
  rightPupil.y += rightEyeRegion.y;
  leftPupil.x += leftEyeRegion.x;
  leftPupil.y += leftEyeRegion.y;

  NumData numData;

  numData.face = face;
  numData.leftEyeRegion = leftEyeRegion;
  numData.rightEyeRegion = rightEyeRegion;
  numData.leftPupil = leftPupil;
  numData.rightPupil = rightPupil;

//  cv::Rect roi( cv::Point( 0, 0 ), faceROI.size());
//  cv::Mat destinationROI = debugImage( roi );
//  faceROI.copyTo( destinationROI );
  return numData;
}

/**
 * @function detectAndDisplay
 */
void detectAndDisplay( cv::Mat frame ) {
  std::vector<cv::Rect> faces;
  //cv::Mat frame_gray;

  std::vector<cv::Mat> rgbChannels(3);
  cv::split(frame, rgbChannels);
  cv::Mat frame_gray = rgbChannels[2];

  //cvtColor( frame, frame_gray, CV_BGR2GRAY );
  //equalizeHist( frame_gray, frame_gray );
  //cv::pow(frame_gray, CV_64F, frame_gray);
  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(150, 150) );
  //  findSkin(debugImage);

  //-- Show what you got
   if (faces.size() > 0) {
     int gridNumber;
	 NumData numData;
     numData = findEyes(frame_gray, faces[0]);
	 gridNumber = mapToGrid(frame, numData, threshNumber);
	 if (frameNumber == 0) {
		displayText(numData);
		display(frame, numData, gridNumber);
		 //imshow(kmain_window_name,frame);
		frameNumber = 0;
	 } else {
		frameNumber++;
	 }
  }
  else {
  
    displayFrame(frame);
  }
}
