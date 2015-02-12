#ifndef COMMON_H
#define COMMON_H

#include <opencv2/opencv.hpp>
#include <list>
#include <map>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<cv::Point2f> Point2fPtr;

struct PointTrack {
    std::list<Point2fPtr> points;
    int firstFrame, lastFrame;
};

typedef std::map<int, PointTrack>  PointTracks;

struct SensorData {

};



#endif
