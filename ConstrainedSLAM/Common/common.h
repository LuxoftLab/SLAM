#ifndef COMMON_H
#define COMMON_H

#include <opencv2/opencv.hpp>
#include <list>

struct PointTrack {
    std::list<cv::Point2f> points;
    int firstFrame, lastFrame;
};

struct SensorData {

};



#endif
