#ifndef C_LKTracker_H
#define C_LKTracker_H

#include <boost/shared_ptr.hpp>

#include "ITracker.hpp"
#include "private/COpticalFlowFeatureExtractor.hpp"

class CLKTracker : public ITracker {
   static const cv::Size sWinSize;
   static const int sMaxLevel;

   std::vector<cv::Mat> mLastPyramid;
   boost::shared_ptr<IOpticalFlowFeatureExtractor> mExtractor;

public:
   CLKTracker(const int maxPoints);

   void setFirstFrame(const cv::Mat & img, const cv::Mat & grayImg,
                      std::vector<cv::Point2f> & features);

   void findNewFeatures(const cv::Mat & img, const cv::Mat & grayImg,
                        std::vector<cv::Point2f>& features,
                        const std::vector<cv::Point2f>& old);

   void findNewFeaturesPosition(const cv::Mat & img,const cv::Mat & grayImg,
                                const std::vector<cv::Point2f>& prevFeatures,
                                std::vector<cv::Point2f>& features,
                                std::vector<uchar>& status);
};

#endif
