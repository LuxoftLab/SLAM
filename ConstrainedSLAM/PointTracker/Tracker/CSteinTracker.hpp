#ifndef C_STEIINTracker_H
#define C_STEIINTracker_H

#include <map>
#include <set>
#include <boost/shared_ptr.hpp>

#include "ITracker.hpp"
#include "private/COpticalFlowFeatureExtractor.hpp"
#include "private/CTritset.hpp"

class CSteinTracker : public ITracker {

    static const int sLBP_TRIT_SZ = 16;
    static const int sLBP_LENS = 5;
    static const int sLBP_EPS = 10;
    static const int sTO_SET = 20;

public:
   CSteinTracker();
   std::map<CTritset<sLBP_TRIT_SZ>, long long> mapFeature;
   std::set <CTritset<sLBP_TRIT_SZ>> setFeature;

   void setFirstFrame(const cv::Mat & img, const cv::Mat & grayImg,
                      std::vector<cv::Point2f> & features);

   void findNewFeatures(const cv::Mat & img, const cv::Mat & grayImg,
                        std::vector<cv::Point2f>& features,
                        const std::vector<cv::Point2f>& old);

   void findNewFeaturesPosition(const cv::Mat & img,const cv::Mat & grayImg,
                                const std::vector<cv::Point2f>& prevFeatures,
                                std::vector<cv::Point2f>& features,
                                std::vector<uchar>& status);
   void toSet();

   int isFeature(int elem, int sLBP_EPS, int p);

   CTritset<sLBP_TRIT_SZ> lbpFeature(const cv::Mat & img, const long long x, const long long y);
};

#endif
