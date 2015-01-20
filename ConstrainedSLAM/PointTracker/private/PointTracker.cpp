
#include <PointTracker/PointTracker.h>
#include <iostream>

PointTracker::PointTracker(cv::Size winSize, int maxLevel, int minPoints, int maxPoints) : frames(10), minPoints(minPoints) {
    tracker = new LKTracker(winSize, maxLevel, minPoints, maxPoints);
}

PointTracker::~PointTracker() {
    delete tracker;
}

void PointTracker::setFirstFrame(cv::Mat &frame) {
    frameNumber = 0;
    nextId = 0;
    tracks.clear();
    frames.clear();

    cv::Mat gray;
    cv::cvtColor(frame, gray, CV_BGR2GRAY);

    prevFeatures.clear();
    tracker->setFirstFrame(gray, prevFeatures);

    std::cout << "found features: " << prevFeatures.size() << std::endl;
    FramePtr f(new Frame);
    for(int i = 0; i < prevFeatures.size(); i++) {
        int id = nextId++;
        PointTrack track;
        track.points.resize(10);
        track.firstFrame = track.lastFrame = frameNumber;
        track.points.push_back(prevFeatures[i]);
        tracks[id] = track;
        f->points[id] = prevFeatures[i];
    }
    frames.push_back(f);
}

void PointTracker::findNewFeaturePositions(cv::Mat &frame, SensorData &sensors) {
    cv::Mat gray;
    cv::cvtColor(frame, gray, CV_BGR2GRAY);

    std::vector<cv::Point2f> features;
    std::vector<uchar> status;
    tracker->findNewFeaturesPosition(gray, prevFeatures, features, status);

    prevFeatures.clear();
    FramePtr f(new Frame);
    std::map<int, PointTrack>::iterator it = tracks.begin();
    for(int i = 0; i < features.size(); i++, it++) {
        while(it->second.lastFrame != frameNumber)
            it++;
        if(status[i]) {
            f->points[it->first] = features[i];
            prevFeatures.push_back(features[i]);
            it->second.lastFrame++;
            it->second.points.push_back(features[i]);
        }
    }



    frames.push_back(f);
    frameNumber++;
}

std::map<int, PointTrack> & PointTracker::getTracks() {
    return tracks;
}

