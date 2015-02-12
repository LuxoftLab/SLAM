#ifndef C_POINT_TRACKER_H
#define C_POINT_TRACKER_H

#include "IPointTracker.hpp"

class PointTracker : public IPointTracker {
    int frameNumber, nextId, minPoints;
    boost::circular_buffer<FramePtr> frames;
    std::map<int, PointTrack> tracks;
    boost::shared_ptr<ITracker> tracker;
    std::vector<cv::Point2f> prevFeatures;

public:
    PointTracker(cv::Size winSize, int maxLevel, int minPoints, int maxPoints);

    void setFirstFrame(cv::Mat& frame);
    void findNewFeaturePositions(cv::Mat& frame, SensorData& sensors);
    std::map<int, PointTrack> & getTracks();

    void addNewPoints(FramePtr frame, std::vector<cv::Point2f> & points);
};

#endif
