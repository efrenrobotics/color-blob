#ifndef COLOR_FILTER_H
#define COLOR_FILTER_H

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

using namespace std;
using namespace cv;

class ColorFilter {
protected:
    cv::Mat _frame;
    std::vector<cv::Mat> _chans;
    cv::Mat _blueCup;
    cv::Mat _greenCup;
    cv::Mat _redCup;
    cv::Mat _output;

public:
    void processImage(cv::Mat img);
    void split();
    void findBlue();
    void findGreen();
    void findRed();
    void findBGR();
    void showResult();
    cv::Mat getBlueImage();
    cv::Mat getRedImage();
    cv::Mat getGreenImage();
    cv::Mat getBGRImage();
};

#endif