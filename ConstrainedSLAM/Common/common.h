#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <map>
#include <opencv2/opencv.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/circular_buffer.hpp>

struct PointTrack {
    boost::circular_buffer<cv::Point2f> points;
    int firstFrame, lastFrame;
};

struct SensorData {

};

struct Frame {
    std::map<int, cv::Point2f> points;
};

typedef boost::shared_ptr<Frame> FramePtr;


#endif
