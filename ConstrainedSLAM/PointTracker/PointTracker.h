
#include <Common/common.h>

#include <vector>
#include <map>

#include <boost/circular_buffer.hpp>

#include "Tracker/tracker.h"

class IPointTracker {
public:
    virtual void setFirstFrame(cv::Mat& frame) = 0;
    virtual void findNewFeaturePositions(cv::Mat& frame, SensorData& sensors) = 0;
    virtual std::map<int, PointTrack> & getTracks() = 0;
};

class PointTracker : public IPointTracker {
    int frameNumber, nextId, minPoints;
    boost::circular_buffer<FramePtr> frames;
    std::map<int, PointTrack> tracks;
    ITracker * tracker;
    std::vector<cv::Point2f> prevFeatures;

public:
    PointTracker(cv::Size winSize, int maxLevel, int minPoints, int maxPoints);
    ~PointTracker();

    void setFirstFrame(cv::Mat& frame);
    void findNewFeaturePositions(cv::Mat& frame, SensorData& sensors);
    std::map<int, PointTrack> & getTracks();
};
