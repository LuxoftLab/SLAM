#ifndef C_FRAME_H
#define C_FRAME_H

#include <boost/shared_ptr.hpp>
#include <boost/circular_buffer.hpp>

#include <opencv2/opencv.hpp>

#include <map>


#include "Common.hpp"

class CFrame;
#include "PointTracker/IPointTracker.hpp"

class CFrame {
    IPointTracker::tPointTracks & mTracks;
public:
    std::map<int, PointTrack::tPoint2fPtr> points;

    CFrame(IPointTracker::tPointTracks & tracks);
    ~CFrame();

};


#endif
