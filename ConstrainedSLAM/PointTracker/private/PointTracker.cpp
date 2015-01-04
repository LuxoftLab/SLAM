
#include <PointTracker/PointTracker.h>

PointTracker::PointTracker(cv::Size winSize, int maxLevel, int minPoints, int maxPoints) {
    tracker = new LKTracker(winSize, maxLevel, minPoints, maxPoints);
}

PointTracker::~PointTracker() {
    delete tracker;
}

void PointTracker::setFirstFrame(cv::Mat &frame, std::vector<PointTrack> &points) {
    frameNumber = 0;

    cv::Mat gray;
    cv::cvtColor(frame, gray, CV_BGR2GRAY);

    std::vector<cv::Point2f> features;
    tracker->setFirstFrame(gray, features);
    for(int i = 0; i < features.size(); i++) {
        PointTrack tmp;
        tmp.points.push_back(features[i]);
        points.push_back(tmp);
    }
}

void PointTracker::findNewFeaturePositions(cv::Mat &frame, std::vector<PointTrack> &points,
                                           SensorData &sensors) {
    cv::Mat gray;
    cv::cvtColor(frame, gray, CV_BGR2GRAY);

    std::vector<cv::Point2f> prevFeatures, features;
    std::vector<uchar> status;
    for(int i = 0; i < points.size(); i++) {
        if(points[i].lastFrame == frameNumber) {
            prevFeatures.push_back(points[i].points.back());
        }
    }
    tracker->findNewFeaturesPosition(gray, prevFeatures, features, status);
    for(int i = 0, j = 0; i < prevFeatures.size(); i++, j++) {
        while(points[j].lastFrame != frameNumber)
            j++;
        if(status[i]) {
            points[j].lastFrame++;
            points[j].points.push_back(features[i]);
        }
    }
    frameNumber++;
}

