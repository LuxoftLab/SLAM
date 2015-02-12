#ifndef I_OPTICAL_FLOW_FEATURE_EXTRACTOR_H
#define I_OPTICAL_FLOW_FEATURE_EXTRACTOR_H

#include <opencv2/opencv.hpp>
#include <vector>

class IOpticalFlowFeatureExtractor {
public:
   void virtual findFeature(const cv::Mat & grayImg,
                            std::vector<cv::Point2f>& features,
                            const std::vector<cv::Point2f>& old) = 0;
};

#endif
