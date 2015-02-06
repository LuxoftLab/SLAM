#ifndef FRAME_H
#define FRAME_H

#include <boost/shared_ptr.hpp>
#include <map>
#include <opencv2/opencv.hpp>

#include "common.h"

class Frame;
typedef boost::shared_ptr<Frame> FramePtr;

class Frame {
    std::map<int, PointTrack> &tracks;
public:
    std::map<int, Point2fPtr> points;

    Frame(std::map<int, PointTrack> & tracks);
    ~Frame();

};

#endif
