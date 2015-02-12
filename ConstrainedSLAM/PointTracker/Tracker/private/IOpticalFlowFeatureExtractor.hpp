#ifndef I_OPTICAL_FLOW_FEATURE_EXTRACTOR_H
#define I_OPTICAL_FLOW_FEATURE_EXTRACTOR_H

#include <opencv2/opencv.hpp>
#include <vector>

class IOpticalFlowFeatureExtractor {
public:
    void virtual findFeature(cv::Mat& frame, std::vector<cv::Point2f>& features) = 0;
    void virtual findFeature(cv::Mat& frame, std::vector<cv::Point2f>& features, std::vector<cv::Point2f>& old) = 0;
};

#endif
