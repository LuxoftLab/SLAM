#ifndef FRAME_H
#define FRAME_H

#include <boost/shared_ptr.hpp>
#include <boost/circular_buffer.hpp>

#include <opencv2/opencv.hpp>

#include <map>


#include "Common.hpp"

class CFrame {
    PointTracks & tracks;
public:
    std::map<int, Point2fPtr> points;

    CFrame(PointTracks & tracks);
    ~CFrame();

};

typedef boost::shared_ptr<CFrame> FramePtr;
typedef boost::circular_buffer<FramePtr> Frames;

#endif
