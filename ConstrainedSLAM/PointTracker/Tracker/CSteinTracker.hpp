#ifndef C_STEIINTracker_H
#define C_STEIINTracker_H

#include <map>
#include <set>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "ITracker.hpp"
#include "private/COpticalFlowFeatureExtractor.hpp"
#include "private/CTritset.hpp"

class CSteinTracker : public ITracker {

    static const int sLBP_TRIT_SZ = 16;
    static const int sLBP_LENS = 5;
    static const int sLBP_EPS = 10;
    static const int sTO_SET = 20;
    int frameCounter = 0;

public:
   CSteinTracker();
   std::map<CTritset, std::vector<cv::Point2f> > featuresMap;
   std::map<CTritset, std::vector<cv::Point2f> > featuresMapTemp;
   std::vector<cv::Point2f> hypoCor;
   std::vector<uchar> featuresStatus;
   std::set <CTritset> featuresSet;

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

   void compareMaps(std::map<CTritset, std::vector<cv::Point2f> > &m1,
                    std::map<CTritset, std::vector<cv::Point2f> > &m2);

   int isFeature(int elem, int sLBP_EPS, int p);

   CTritset lbpFeature(const cv::Mat & img, const long long x, const long long y);
};

#endif
