
#include "OpticalFlowFeatureExtractor.h"

const double OpticalFlowFeatureExtractor::minDistance = 30;
const double OpticalFlowFeatureExtractor::qualityLevel = 0.01;

OpticalFlowFeatureExtractor::OpticalFlowFeatureExtractor(int maxCorners) : maxCorners(maxCorners) {

}

void OpticalFlowFeatureExtractor::findFeature(cv::Mat &frame, std::vector<cv::Point2f> &features) {
    cv::Mat mask(frame.rows, frame.cols, CV_8UC1, cv::Scalar(255));

    cv::goodFeaturesToTrack(frame, features, maxCorners, qualityLevel, minDistance, mask);
}
