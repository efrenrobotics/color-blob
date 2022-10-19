#include "opencv_hw/ColorFilter.h"

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    // showResult();
}

cv::Mat ColorFilter::getBlueImage(){
    return _blueCup;
}

cv::Mat ColorFilter::getGreenImage(){
    return _greenCup;
}

cv::Mat ColorFilter::getRedImage(){
    return _redCup;
}

cv::Mat ColorFilter::getBGRImage(){
    return _output;
}

void ColorFilter::split() {
    cv::split(_frame, _chans);
}

void ColorFilter::showResult() {
    // PROBLEM 1: Show 'vanilla' video
    // imshow("vanilla", _frame);

    // Show BLUE contrast video
    // PROBLEM 2: B
    // imshow("blue contrast", _chans[0]);

    // Show RED contrast video
    // PROBLEM 2: R
    // imshow("red contrast", _chans[1]);

    // Show GREEN contrast video
    // PROBLWEM 2: G
    // imshow("green constrast", _chans[2]);

    // PROBLEM 6: ALL THREE
    // imshow("ALL THREE", _output);
}

void ColorFilter::findBlue() {
    // PROBLEM 3: Blue Subtraction
    Mat bMinusR;
    subtract(_chans[0], _chans[2], bMinusR);
    // imshow("Blue Subtraction", bMinusR);
    // PROBLEM 3: Binary thresholding
    Mat thresh;
    threshold(bMinusR, thresh, 50, 255, THRESH_BINARY);
    // imshow("Blue Threshold", thresh);
    // PROBLEM 3: Compute mask
    vector<Mat> contours;
    vector<Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0; 

    for(int i = 0; i < contours.size(); i++){
        int contourSize = contourArea(contours[i]);
        if(contourSize > maxContourSize){
            maxSizeContour = i; 
            maxContourSize = contourSize;
        }
    }

    Mat contourMask = Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(contourMask, contours, maxSizeContour, Scalar(255), LineTypes::FILLED, 8, hierarchy);
    // imshow("Blue Mask", contourMask);
    // PROBLEM 3: Only blue cup
    _blueCup = Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(_blueCup, contourMask);
    // imshow("BLUE CUP", _blueCup);
}

void ColorFilter::findGreen() {
    // PROBLEM 4: Green Subtraction
    Mat gMinusB;
    // subtract green and blue, makes green cup brigtest
    subtract(_chans[1], _chans[0], gMinusB);
    // imshow("Green subtraction", gMinusB);
    // PROBLEM 4: Binary thresholding
    Mat thresh;
    threshold(gMinusB, thresh, 50, 255, THRESH_BINARY);
    // imshow("Green threshold", thresh);
    // PROBLEM 4: Compute mask
    vector<Mat> contours;
    vector<Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0; 

    for(int i = 0; i < contours.size(); i++){
        int contourSize = contourArea(contours[i]);
        if(contourSize > maxContourSize){
            maxSizeContour = i; 
            maxContourSize = contourSize;
        }
    }

    Mat contourMask = Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(contourMask, contours, maxSizeContour, Scalar(255), FILLED, 8, hierarchy);
    // imshow("Green Mask", contourMask);
    // PROBLEM 4: Only blue cup
    _greenCup = Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(_greenCup, contourMask);
    // imshow("Green Cup", _greenCup);
}

void ColorFilter::findRed() {
    // PROBLEM 4: Red Subtraction
    Mat rMinusG;
    // subtract red and green, makes red cup brigtest
    subtract(_chans[2], _chans[1], rMinusG);
    // imshow("Red Subtraction", rMinusG);
    // PROBLEM 4: Binary thresholding
    Mat thresh;
    threshold(rMinusG, thresh, 65, 255, THRESH_BINARY);
    // imshow("Red Threshold", thresh);
    // PROBLEM 4: Compute mask
    vector<Mat> contours;
    vector<Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0;
    int maxContourSize = 0; 

    for(int i = 0; i < contours.size(); i++){
        int contourSize = contourArea(contours[i]);
        if(contourSize > maxContourSize){
            maxSizeContour = i; 
            maxContourSize = contourSize;
        }
    }
    
    Mat contourMask = Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(contourMask, contours, maxSizeContour, Scalar(255), FILLED, 8, hierarchy);
    // imshow("Red Mask", contourMask);
    // PROBLEM 4: Only red cup
    _redCup = Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(_redCup, contourMask);
    // imshow("Red Cup", _redCup);
}

void ColorFilter::findBGR() {
    bitwise_or(_blueCup, _redCup, _output);
    bitwise_or(_output, _greenCup, _output);
}