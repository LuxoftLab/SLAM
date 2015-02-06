#ifndef COMMON_H
#define COMMON_H

#include <opencv2/opencv.hpp>
#include <list>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<cv::Point2f> Point2fPtr;

struct PointTrack {
    std::list<cv::Point2f> points;
    int firstFrame, lastFrame;
};

struct SensorData {

};



#endif
