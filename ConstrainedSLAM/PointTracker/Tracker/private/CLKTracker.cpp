
#include "PointTracker/Tracker/CLKTracker.hpp"
#include "COpticalFlowFeatureExtractor.hpp"

const cv::Size CLKTracker::sWinSize(21, 21);
const int CLKTracker::sMaxLevel = 5;

CLKTracker::CLKTracker(const int maxPoints) :
   mExtractor(new COpticalFlowFeatureExtractor(maxPoints))
{
}

void CLKTracker::setFirstFrame(const cv::Mat & img, const cv::Mat & grayImg,
                               std::vector<cv::Point2f> & features)
{
   std::vector<cv::Point2f> prevFeatures;
   mExtractor->findFeature(grayImg, features, prevFeatures);
   cv::buildOpticalFlowPyramid(grayImg, mLastPyramid, sWinSize, sMaxLevel, true);
}

void CLKTracker::findNewFeatures(const cv::Mat & img, const cv::Mat & grayImg,
                                 std::vector<cv::Point2f> & features,
                                 const std::vector<cv::Point2f>& old)
{
   mExtractor->findFeature(grayImg, features, old);
}

void CLKTracker::findNewFeaturesPosition(const cv::Mat & img,const cv::Mat & grayImg,
                                         const std::vector<cv::Point2f> & prevFeatures,
                                         std::vector<cv::Point2f>& features,
                                         std::vector<uchar>& status)
{
   std::vector<float> error;
   std::vector<cv::Mat> currentPyramid;
   cv::buildOpticalFlowPyramid(grayImg, currentPyramid, sWinSize, sMaxLevel, true);
   cv::calcOpticalFlowPyrLK(mLastPyramid, currentPyramid, prevFeatures, features,
                            status, error, sWinSize, sMaxLevel);
   mLastPyramid.swap(currentPyramid);
}
