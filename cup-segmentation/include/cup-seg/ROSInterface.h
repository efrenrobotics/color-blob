#ifndef ROS_INTERFACE_H
#define ROS_INTERFACE_H
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "ColorFilter.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <iostream>
#include <opencv_hw/ColorFilter.h>

using namespace std;


class ROSInterface{
    ColorFilter _cf;
    ros::NodeHandle _nh;
    image_transport::ImageTransport _it;
    image_transport::Publisher _bluePub;
    image_transport::Publisher _greenPub;
    image_transport::Publisher _redPub;
    image_transport::Publisher _bgrPub;
    image_transport::Subscriber _sub;

public: 
    ROSInterface(ColorFilter &cf);

    ~ROSInterface();

    void imageCb(const sensor_msgs::ImageConstPtr& msg);
};  

#endif