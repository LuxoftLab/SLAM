#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <opencv2/opencv.hpp>

struct PointTrack {
    std::vector<cv::Point2f> points;
    int lastFrame = 0;
};

struct SensorData {

};

#endif
