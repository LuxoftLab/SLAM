
#include <opencv2/opencv.hpp>
#include <vector>

class IOpticalFlowFeatureExtractor {
public:
    void virtual findFeature(cv::Mat& frame, std::vector<cv::Point2f>& features) = 0;
};

class OpticalFlowFeatureExtractor : public IOpticalFlowFeatureExtractor {
    static const double qualityLevel, minDistance;
    int maxCorners;
public:
    OpticalFlowFeatureExtractor(int maxCorners);
    void findFeature(cv::Mat& frame, std::vector<cv::Point2f>& features);
};
