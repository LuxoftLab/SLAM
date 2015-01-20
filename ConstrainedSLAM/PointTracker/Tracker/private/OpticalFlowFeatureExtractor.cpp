
#include "OpticalFlowFeatureExtractor.h"

const double OpticalFlowFeatureExtractor::minDistance = 30;
const double OpticalFlowFeatureExtractor::qualityLevel = 0.01;

OpticalFlowFeatureExtractor::OpticalFlowFeatureExtractor(int maxCorners) : maxCorners(maxCorners) {

}

void OpticalFlowFeatureExtractor::findFeature(cv::Mat &frame, std::vector<cv::Point2f> &features) {
    cv::goodFeaturesToTrack(frame, features, maxCorners, qualityLevel, minDistance);
}

void OpticalFlowFeatureExtractor::findFeature(cv::Mat &frame, std::vector<cv::Point2f> &features, std::vector<cv::Point2f> &old) {
    cv::Mat mask(frame.rows, frame.cols, CV_8UC1, cv::Scalar(255));
    for(int i = 0; i < old.size(); i++) {
        cv::circle(mask, old[i], minDistance/2, cv::Scalar(0));
    }
    cv::goodFeaturesToTrack(frame, features, maxCorners - old.size(), qualityLevel, minDistance, mask);
}
