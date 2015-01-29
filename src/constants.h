#ifndef CONSTANTS_H
#define CONSTANTS_H


// Debugging
const bool kPlotVectorField = false;

// Size constants
const int kEyePercentTop = 25;
const int kEyePercentSide = 13;
const int kEyePercentHeight = 30;
const int kEyePercentWidth = 35;

// Preprocessing
const bool kSmoothFaceImage = false;
const float kSmoothFaceFactor = 0.005;

// Algorithm Parameters
const int kFastEyeWidth = 50;
const int kWeightBlurSize = 5;
const bool kEnableWeight = false;
const float kWeightDivisor = 150.0;
const double kGradientThreshold = 50.0;

// Postprocessing
const bool kEnablePostProcess = false;
const float kPostProcessThreshold = 0.97;

// Eye Corner
const bool kEnableEyeCorner = false;

// Display
const std::string kmain_window_name = "Capture - Face detection";
const std::string kface_window_name = "Capture - Face";
const std::string kleft_eye_window_name = "Capture - Left Eye";
const std::string kright_eye_window_name = "Capture - Right Eye";
const std::string debugWindow = "DEBUG";


#endif