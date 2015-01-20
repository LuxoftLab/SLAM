
#include <PointTracker/Tracker/tracker.h>

LKTracker::LKTracker(cv::Size winSize, int maxLevel, int maxPoints) :
    winSize(winSize),
    maxLevel(maxLevel) {
    extractor = new OpticalFlowFeatureExtractor(maxPoints);
}

LKTracker::~LKTracker() {
    delete extractor;
}

void LKTracker::setFirstFrame(cv::Mat &frame, std::vector<cv::Point2f> &fetures) {
    extractor->findFeature(frame, fetures);
    buildPyramid(frame, lastPyr);
}

void LKTracker::findNewFeatures(cv::Mat &frame, std::vector<cv::Point2f> &fetures, std::vector<cv::Point2f> &old) {
    extractor->findFeature(frame, fetures, old);
}

void LKTracker::findNewFeaturesPosition(cv::Mat &frame, std::vector<cv::Point2f> &prevFeatures,
                                        std::vector<cv::Point2f> &features, std::vector<uchar>& status) {
    std::vector<float> error;
    std::vector<cv::Mat> curPyr;
    buildPyramid(frame, curPyr);
    cv::calcOpticalFlowPyrLK(lastPyr, curPyr, prevFeatures, features,
                             status, error, winSize, maxLevel);
    lastPyr.swap(curPyr);
}

void LKTracker::buildPyramid(cv::Mat &frame, std::vector<cv::Mat> &pyr) {
    cv::buildOpticalFlowPyramid(frame, pyr, winSize, maxLevel, true);
}
