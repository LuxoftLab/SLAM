#ifndef C_OPTICAL_FLOW_H
#define C_OPTICAL_FLOW_H

#include "IOpticalFlowFeatureExtractor.hpp"

class COpticalFlowFeatureExtractor : public IOpticalFlowFeatureExtractor {
    static const double qualityLevel, minDistance;
    int maxCorners;
public:
    COpticalFlowFeatureExtractor(int maxCorners);
    void findFeature(cv::Mat& frame, std::vector<cv::Point2f>& features);
    void findFeature(cv::Mat &frame, std::vector<cv::Point2f> &features, std::vector<cv::Point2f>& old);
};

#endif
