#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include "opencv_hw/ROSInterface.h"
    

// ROSInterface constructor. Initializes a subscriber node that provides the vanilla video. 
// Initializes four seperate advertisers, which will display the video data for each condition.
// Initialize the ColorFilter reference.
ROSInterface::ROSInterface(ColorFilter &cf) : _it(_nh)   {
    _sub = _it.subscribe("/kinect2/hd/image_color", 1, &ROSInterface::imageCb, this);

    _bluePub = _it.advertise("blue_cup", 1);
    _greenPub = _it.advertise("green_cup", 1);
    _redPub = _it.advertise("red_cup", 1);
    _bgrPub = _it.advertise("bgr_cups", 1);

    _cf = cf;
}

// ROSInterface destructor
ROSInterface::~ROSInterface(){}

// Image Callback, publishes each video stream into its appropriate advertiser.
void ROSInterface::imageCb(const sensor_msgs::ImageConstPtr& msg) {
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    _cf.processImage(cv_ptr -> image);

    sensor_msgs::ImagePtr blueImage = cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getBlueImage()).toImageMsg();
    _bluePub.publish(blueImage);
    sensor_msgs::ImagePtr greenImage = cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getGreenImage()).toImageMsg();
    _greenPub.publish(greenImage);
    sensor_msgs::ImagePtr redImage = cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getRedImage()).toImageMsg();
    _redPub.publish(redImage);
    sensor_msgs::ImagePtr bgrImage = cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getBGRImage()).toImageMsg();
    _bgrPub.publish(bgrImage);
}


