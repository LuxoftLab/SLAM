#ifndef I_TRACKER_H
#define I_TRACKER_H

#include <opencv2/opencv.hpp>
#include <vector>

class ITracker {
public:
    virtual void setFirstFrame(cv::Mat& frame, std::vector<cv::Point2f>& fetures) = 0;
    virtual void findNewFeatures(cv::Mat& frame, std::vector<cv::Point2f>& fetures, std::vector<cv::Point2f>& old) = 0;
    virtual void findNewFeaturesPosition(cv::Mat& frame, std::vector<cv::Point2f>& prevFetures,
                                 std::vector<cv::Point2f>& fetures, std::vector<uchar>& status) = 0;
};

#endif
