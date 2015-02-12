#ifndef C_POINT_TRACKER_H
#define C_POINT_TRACKER_H

#include <vector>
#include <map>

#include <boost/circular_buffer.hpp>
#include <boost/shared_ptr.hpp>

#include "Common/Common.hpp"
#include "Common/CFrame.hpp"
#include "IPointTracker.hpp"

class CPointTracker : public IPointTracker {
    int frameNumber, nextId, minPoints;
    Frames frames;
    PointTracks tracks;
    boost::shared_ptr<ITracker> tracker;
    std::vector<cv::Point2f> prevFeatures;

public:
    CPointTracker(cv::Size winSize, int maxLevel, int minPoints, int maxPoints);

    void setFirstFrame(cv::Mat& frame);
    void findNewFeaturePositions(cv::Mat& frame, SensorData& sensors);
    const PointTracks & getTracks() const;
    const Frames & getFrames() const;

    void addNewPoints(FramePtr frame, std::vector<cv::Point2f> & points);
};

#endif
