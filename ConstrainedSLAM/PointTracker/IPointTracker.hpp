#ifndef I_POINT_TRACKER_H
#define I_POINT_TRACKER_H

#include <vector>
#include <map>

#include <boost/circular_buffer.hpp>
#include <boost/shared_ptr.hpp>

class IPointTracker;

#include <Common/common.h>
#include <Common/Frame.h>

#include "Tracker/tracker.h"

class IPointTracker {
public:
    virtual void setFirstFrame(cv::Mat& frame) = 0;
    virtual void findNewFeaturePositions(cv::Mat& frame, SensorData& sensors) = 0;
    virtual const PointTracks & getTracks() const = 0;
    virtual const Frames & getFrames() const = 0;
};

#endif
