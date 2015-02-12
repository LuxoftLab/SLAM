
#include "PointTracker/Tracker/CLKTracker.hpp"
#include "COpticalFlowFeatureExtractor.hpp"


CLKTracker::CLKTracker(cv::Size winSize, int maxLevel, int maxPoints) :
    winSize(winSize),
    maxLevel(maxLevel),
    extractor(new COpticalFlowFeatureExtractor(maxPoints))
{
}

void CLKTracker::setFirstFrame(cv::Mat &frame, std::vector<cv::Point2f> &fetures) {
    extractor->findFeature(frame, fetures);
    buildPyramid(frame, lastPyr);
}

void CLKTracker::findNewFeatures(cv::Mat &frame, std::vector<cv::Point2f> &fetures, std::vector<cv::Point2f> &old) {
    extractor->findFeature(frame, fetures, old);
}

void CLKTracker::findNewFeaturesPosition(cv::Mat &frame, std::vector<cv::Point2f> &prevFeatures,
                                        std::vector<cv::Point2f> &features, std::vector<uchar>& status) {
    std::vector<float> error;
    std::vector<cv::Mat> curPyr;
    buildPyramid(frame, curPyr);
    cv::calcOpticalFlowPyrLK(lastPyr, curPyr, prevFeatures, features,
                             status, error, winSize, maxLevel);
    lastPyr.swap(curPyr);
}

void CLKTracker::buildPyramid(cv::Mat &frame, std::vector<cv::Mat> &pyr) {
    cv::buildOpticalFlowPyramid(frame, pyr, winSize, maxLevel, true);
}
