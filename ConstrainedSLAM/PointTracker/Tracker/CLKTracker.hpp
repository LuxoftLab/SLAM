#ifndef C_LKTracker_H
#define C_LKTracker_H

#include <boost/shared_ptr.hpp>

#include "ITracker.hpp"
#include "private/COpticalFlowFeatureExtractor.hpp"

class CLKTracker : public ITracker {
    std::vector<cv::Mat> lastPyr;
    cv::Size winSize;
    int maxLevel;
    boost::shared_ptr<IOpticalFlowFeatureExtractor> extractor;

    void buildPyramid(cv::Mat& frame, std::vector<cv::Mat>& pyr);

public:
    CLKTracker(cv::Size winSize, int maxLevel, int maxPoints);

    void setFirstFrame(cv::Mat& frame, std::vector<cv::Point2f>& fetures);
    void findNewFeatures(cv::Mat& frame, std::vector<cv::Point2f>& fetures, std::vector<cv::Point2f>& old);
    void findNewFeaturesPosition(cv::Mat& frame, std::vector<cv::Point2f>& prevFetures,
                                 std::vector<cv::Point2f>& fetures, std::vector<uchar>& status);
};

#endif
