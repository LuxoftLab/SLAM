#ifndef C_OPTICAL_FLOW_H
#define C_OPTICAL_FLOW_H

#include "IOpticalFlowFeatureExtractor.hpp"

class COpticalFlowFeatureExtractor : public IOpticalFlowFeatureExtractor {
   static const double sQualityLevel;
   static const double sMinDistance;
   int mMaxCorners;
public:
   COpticalFlowFeatureExtractor(const int maxCorners);
   void findFeature(const cv::Mat & grayImg,
                    std::vector<cv::Point2f>& features,
                    const std::vector<cv::Point2f>& old);
};

#endif
