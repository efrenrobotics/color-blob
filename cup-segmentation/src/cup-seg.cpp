#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <iostream>

#include "opencv_hw/ColorFilter.h"
#include "opencv_hw/ROSInterface.h"



int main(int argc, char **argv) {
    ros::init(argc, argv, "image_out");
    
    ColorFilter cf;

    ROSInterface rosInterface(cf);

    ros::spin();

    return 0;
}