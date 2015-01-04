
#include <Common/common.h>
#include "private/OpticalFlowFeatureExtractor.h"

class ITracker {
public:
    void virtual setFirstFrame(cv::Mat& frame, std::vector<cv::Point2f>& fetures) = 0;
    void virtual findNewFeaturesPosition(cv::Mat& frame, std::vector<cv::Point2f>& prevFetures,
                                 std::vector<cv::Point2f>& fetures, std::vector<uchar>& status) = 0;
};

class LKTracker : public ITracker {
    std::vector<cv::Mat> lastPyr;
    cv::Size winSize;
    int maxLevel;
    IOpticalFlowFeatureExtractor * extractor;

    void buildPyramid(cv::Mat& frame, std::vector<cv::Mat>& pyr);

public:
    LKTracker(cv::Size winSize, int maxLevel, int minPoints, int maxPoints);
    ~LKTracker();

    void setFirstFrame(cv::Mat& frame, std::vector<cv::Point2f>& fetures);
    void findNewFeaturesPosition(cv::Mat& frame, std::vector<cv::Point2f>& prevFetures,
                                 std::vector<cv::Point2f>& fetures, std::vector<uchar>& status);
};
