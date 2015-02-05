#ifndef FRAME_H
#define FRAME_H

#include <boost/shared_ptr.hpp>
#include <map>
#include <opencv2/opencv.hpp>

class Frame;
typedef boost::shared_ptr<Frame> FramePtr;
typedef boost::shared_ptr<cv::Point2f> Point2fPtr;

#include<PointTracker/PointTracker.h>

class Frame {
    IPointTracker * tracker;
public:
    std::map<int, Point2fPtr> points;

    Frame(IPointTracker * tracker);
    ~Frame();

};

#endif
