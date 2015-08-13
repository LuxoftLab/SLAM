#ifndef C_STEIINTracker_H
#define C_STEIINTracker_H

#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "ITracker.hpp"
#include "private/COpticalFlowFeatureExtractor.hpp"
#include "private/CTritset.hpp"

class CSteinTracker : public ITracker {

    static const int sLBP_TRIT_SZ = 16; //feature length
    static const int sLBP_LENS = 5; //square side length around the feature
    static const int sLBP_EPS = 30;
    static const int sTO_SET = 5;
    static const int sMDP = 8; //max_discriminative_power, depends on sLBP_TRIT_SZ
    int frameCounter = 1;

public:
   CSteinTracker(const int maxPoints);
   std::map<CTritset, std::vector<cv::Point2f> > gTablePrevFrame;
   std::map<CTritset, std::vector<cv::Point2f> > gTableCurrFrame;
   std::vector<cv::Point2f> gFeaturesFoundInTables;
   std::vector<cv::Point2f> gCorrespondenceHypotheses;
   std::vector<cv::Point2f> gFeatures2FramesAgo;
   std::vector<uchar> gFeaturesStatus;
   std::set <CTritset> gListOfCandidates;

   std::vector <CTritset> gTritsetPrev;

   void setFirstFrame(const cv::Mat & img, const cv::Mat & grayImg,
                      std::vector<cv::Point2f> & features);

   void findNewFeatures(const cv::Mat & img, const cv::Mat & grayImg,
                        std::vector<cv::Point2f>& features,
                        const std::vector<cv::Point2f>& old);

   void findNewFeaturesPosition(const cv::Mat & img,const cv::Mat & grayImg,
                                const std::vector<cv::Point2f>& prevFeatures,
                                std::vector<cv::Point2f>& features,
                                std::vector<uchar>& status);
   void makeCandidatesList();

   void compareSignatures(const cv::Mat & img,const cv::Mat & grayImg,
                          std::map<CTritset, std::vector<cv::Point2f> > &m1,
                          std::map<CTritset, std::vector<cv::Point2f> > &m2,
                          const std::vector<cv::Point2f>& prevFeatures,
                          std::vector<cv::Point2f>& features);

   int isFeature(int elem, int sLBP_EPS, int p);

   CTritset lbpFeature(const cv::Mat & img, const long long x, const long long y);
};

#endif
