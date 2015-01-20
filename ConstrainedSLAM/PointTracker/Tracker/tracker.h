#ifndef TRACKER_H
#define TRACKER_H

#include <Common/common.h>
#include "private/OpticalFlowFeatureExtractor.h"

class ITracker {
public:
    virtual void setFirstFrame(cv::Mat& frame, std::vector<cv::Point2f>& fetures) = 0;
    virtual void findNewFeatures(cv::Mat& frame, std::vector<cv::Point2f>& fetures, std::vector<cv::Point2f>& old) = 0;
    virtual void findNewFeaturesPosition(cv::Mat& frame, std::vector<cv::Point2f>& prevFetures,
                                 std::vector<cv::Point2f>& fetures, std::vector<uchar>& status) = 0;
};

class LKTracker : public ITracker {
    std::vector<cv::Mat> lastPyr;
    cv::Size winSize;
    int maxLevel;
    IOpticalFlowFeatureExtractor * extractor;

    void buildPyramid(cv::Mat& frame, std::vector<cv::Mat>& pyr);

public:
    LKTracker(cv::Size winSize, int maxLevel, int maxPoints);
    ~LKTracker();

    void setFirstFrame(cv::Mat& frame, std::vector<cv::Point2f>& fetures);
    void findNewFeatures(cv::Mat& frame, std::vector<cv::Point2f>& fetures, std::vector<cv::Point2f>& old);
    void findNewFeaturesPosition(cv::Mat& frame, std::vector<cv::Point2f>& prevFetures,
                                 std::vector<cv::Point2f>& fetures, std::vector<uchar>& status);
};

#endif
