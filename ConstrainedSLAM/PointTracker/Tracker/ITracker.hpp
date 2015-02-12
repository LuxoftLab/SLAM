#ifndef I_TRACKER_H
#define I_TRACKER_H

#include <opencv2/opencv.hpp>
#include <vector>

class ITracker {
public:
   virtual void setFirstFrame(const cv::Mat & img, const cv::Mat & grayImg,
                              std::vector<cv::Point2f> & fetures) = 0;

   virtual void findNewFeatures(const cv::Mat & img, const cv::Mat & grayImg,
                                std::vector<cv::Point2f>& fetures,
                                const std::vector<cv::Point2f>& old) = 0;

   virtual void findNewFeaturesPosition(const cv::Mat & img,
                                        const cv::Mat & grayImg,
                                        const std::vector<cv::Point2f>& prevFetures,
                                        std::vector<cv::Point2f>& fetures,
                                        std::vector<uchar>& status) = 0;
};

#endif
