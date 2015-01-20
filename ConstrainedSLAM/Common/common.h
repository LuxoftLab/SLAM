#ifndef COMMON_H
#define COMMON_H

#include <opencv2/opencv.hpp>
#include <boost/circular_buffer.hpp>

struct PointTrack {
    boost::circular_buffer<cv::Point2f> points;
    int firstFrame, lastFrame;
};

struct SensorData {

};



#endif
