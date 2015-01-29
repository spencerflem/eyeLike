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

/**
 * @function main
 */
int main( int argc, const char** argv ) {
  CvCapture* capture;
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
  cv::namedWindow(kleft_eye_window_name,CV_WINDOW_NORMAL);
  cv::moveWindow(kleft_eye_window_name, 10, 100);
  cv::namedWindow(kright_eye_window_name,CV_WINDOW_NORMAL);
  cv::moveWindow(kright_eye_window_name, 10, 100);
  cv::namedWindow(debugWindow + " Mask",CV_WINDOW_NORMAL);
  cv::namedWindow("Right Eye",CV_WINDOW_NORMAL);
  cv::moveWindow("Right Eye", 10, 600);
  cv::namedWindow("Left Eye",CV_WINDOW_NORMAL);
  cv::moveWindow("Left Eye", 10, 800);
  cv::namedWindow("aa",CV_WINDOW_NORMAL);
  cv::moveWindow("aa", 10, 800);
  cv::namedWindow("aaa",CV_WINDOW_NORMAL);
  cv::moveWindow("aaa", 10, 800);

  ellipse(skinCrCbHist, cv::Point(113, 155.6), cv::Size(23.4, 15.2),
          43.0, 0.0, 360.0, cv::Scalar(255, 255, 255), -1);

   // Read the video stream
  capture = cvCaptureFromCAM( -1 );
  if( capture ) {
    while( true ) {
      frame = cvQueryFrame( capture );
      // mirror it
      cv::flip(frame, frame, 1);
      frame.copyTo(debugImage);

      // Apply the classifier to the frame
      if( !frame.empty() ) {
        detectAndDisplay( frame );
      }
      else {
        printf(" --(!) No captured frame -- Break!");
        break;
      }

      int c = cv::waitKey(10);
      if( (char)c == 'c' ) { break; }
      else if( (char)c == 'f' ) {
        imwrite("frame.png",frame);
      }
	  else if( (char)c == 'g' ) {
        printFrame(frame, true);
      }
	  else if( (char)c == 'h' ) {
        printFrame(frame, false);
      }

    }
  }
  else {
	  printf(" --(!) No captured frame -- Break!");
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
	 gridNumber = mapToGrid(frame, numData);
	 display(frame, numData, gridNumber);
  }
  else {
    displayFrame(frame);
  }
}
