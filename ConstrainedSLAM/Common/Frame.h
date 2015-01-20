#ifndef FRAME_H
#define FRAME_H

#include <boost/shared_ptr.hpp>
#include <map>
#include <opencv2/opencv.hpp>

class Frame;
typedef boost::shared_ptr<Frame> FramePtr;

#include<PointTracker/PointTracker.h>

class Frame {
    IPointTracker * tracker;
public:
    std::map<int, cv::Point2f> points;

    Frame(IPointTracker * tracker);
    ~Frame();

};

#endif
