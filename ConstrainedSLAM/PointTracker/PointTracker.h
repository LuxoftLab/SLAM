
#include <Common/common.h>
#include "Tracker/tracker.h"

class IPointTracker {
public:
    void virtual setFirstFrame(cv::Mat& frame, std::vector<PointTrack>& points) = 0;
    void virtual findNewFeaturePositions(cv::Mat& frame, std::vector<PointTrack>& points, SensorData& sensors) = 0;
};

class PointTracker : public IPointTracker {
    int frameNumber;
    ITracker * tracker;
public:
    PointTracker(cv::Size winSize, int maxLevel, int minPoints, int maxPoints);
    ~PointTracker();

    void setFirstFrame(cv::Mat& frame, std::vector<PointTrack>& points);
    void findNewFeaturePositions(cv::Mat& frame, std::vector<PointTrack>& points, SensorData& sensors);
};
