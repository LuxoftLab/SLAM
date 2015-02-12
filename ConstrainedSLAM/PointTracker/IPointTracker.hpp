#ifndef I_POINT_TRACKER_H
#define I_POINT_TRACKER_H

#include <opencv2/opencv.hpp>

#include "Common/Common.hpp"
#include "Common/CFrame.hpp"

#include "Tracker/ITracker.hpp"

class IPointTracker {
public:
    virtual void setFirstFrame(cv::Mat& frame) = 0;
    virtual void findNewFeaturePositions(cv::Mat& frame, SensorData& sensors) = 0;
    virtual const PointTracks & getTracks() const = 0;
    virtual const Frames & getFrames() const = 0;
};

#endif
