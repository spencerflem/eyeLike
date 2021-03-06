#ifndef DISPLAY_H
#define DISPLAY_H

#include "structs.h"

void display(cv::Mat frame, NumData numData, int gridNumber);

void displayText(NumData numData);

void displayFrame(cv::Mat frame);

void printFrame(cv::Mat frame, char id);

#endif