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

#define __LOG_VAL(v) std::cout << #v << " = " << v << "\n"
#define __LOG_MSG(v) std::cout << v << "\n"

class CSteinTracker : public ITracker {

    static const int sLBP_TRIT_SZ = 16; //feature length
    static const int sLBP_LENS = 5; //square side length around the feature
    static const int sLBP_EPS = 40;
    static const int sTO_SET = 1;
    static const int sMDP = 8; //max_discriminative_power, depends on sLBP_TRIT_SZ
    static const int sRow = 600;
    static const int sCol = 800;
    int frameCounter = 1;

public:
   CSteinTracker(int maxPoints);
   ~CSteinTracker();
   std::map<CTritset, std::vector<cv::Point2f> > *gTablePrevFrame;
   std::map<CTritset, std::vector<cv::Point2f> > *gTableCurrFrame;
   std::vector<cv::Point2f> gFeaturesFoundInTables;
   std::vector<cv::Point2f> gCorrespondenceHypotheses;
   std::vector<cv::Point2f> gFeatures2FramesAgo;
   std::set <CTritset> gListOfCandidates;
   CTritset gFeatureQueue[sRow][sCol];
   std::vector <CTritset> *gTritsetPrev;
   std::vector <CTritset> *gTritsetCur;

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
                          std::vector<cv::Point2f>& features,
                          std::vector<uchar> &status);

   int isFeature(int elem, int p);
   bool notEnoughMemory(int x, int y);
   void lbpFeatureColRow(const cv::Mat & img);
   void lbpFeatureOptimized(const cv::Mat & img);
   void setFirstFrameOptimized(const cv::Mat & img, const cv::Mat & grayImg,
                      std::vector<cv::Point2f> & features);
   void findNewFeaturesPositionOptimized(const cv::Mat & img,const cv::Mat & grayImg,
                                         const std::vector<cv::Point2f>& prevFeatures,
                                         std::vector<cv::Point2f>& features,
                                         std::vector<uchar>& status);

   CTritset lbpFeature(const cv::Mat & img, const long long x, const long long y);
};

#endif
