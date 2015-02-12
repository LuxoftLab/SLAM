
#include "COpticalFlowFeatureExtractor.hpp"

const double COpticalFlowFeatureExtractor::sMinDistance = 30;
const double COpticalFlowFeatureExtractor::sQualityLevel = 0.01;

COpticalFlowFeatureExtractor::COpticalFlowFeatureExtractor(const int maxCorners)
   : mMaxCorners(maxCorners)
{
}

void COpticalFlowFeatureExtractor::findFeature(const cv::Mat & grayImg,
                                               std::vector<cv::Point2f> & features,
                                               const std::vector<cv::Point2f> & old)
{
   cv::Mat mask(grayImg.rows, grayImg.cols, CV_8UC1, cv::Scalar(255));
   for(size_t i = 0; i < old.size(); i++)
   {
      cv::circle(mask, old[i], sMinDistance / 2, cv::Scalar(0));
   }
   cv::goodFeaturesToTrack(grayImg, features,
                           mMaxCorners - old.size(),
                           sQualityLevel, sMinDistance, mask);
}
