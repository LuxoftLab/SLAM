
#include <PointTracker/PointTracker.h>
#include <iostream>

PointTracker::PointTracker(cv::Size winSize, int maxLevel, int minPoints, int maxPoints) : frames(10), minPoints(minPoints) {
    tracker = new LKTracker(winSize, maxLevel, maxPoints);
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
    FramePtr f(new Frame(tracks));
    addNewPoints(f, prevFeatures);
    frames.push_back(f);
}

void PointTracker::findNewFeaturePositions(cv::Mat &frame, SensorData &sensors) {
    cv::Mat gray;
    cv::cvtColor(frame, gray, CV_BGR2GRAY);

    std::vector<cv::Point2f> features;
    std::vector<uchar> status;
    tracker->findNewFeaturesPosition(gray, prevFeatures, features, status);

    prevFeatures.clear();
    FramePtr f(new Frame(tracks));
    auto it = tracks.begin();

    std::cout << "start update tracks"<< std::endl;
    for(int i = 0; i < features.size(); i++, it++) {
        while(it->second.lastFrame != frameNumber)
            it++;
        if(status[i]) {
			Point2fPtr temp = Point2fPtr(new cv::Point2f(features[i]));;
            f->points[it->first] = temp;
            prevFeatures.push_back(features[i]);
            it->second.lastFrame++;
            it->second.points.push_back(temp);
        }
    }
    std::cout << "finish update tracks"<< std::endl;

    frameNumber++;

    if(prevFeatures.size() < minPoints) {
        std::vector<cv::Point2f> newPoints;
        tracker->findNewFeatures(gray, newPoints, prevFeatures);
        std::cout << "new points: " << newPoints.size() << std::endl;
        addNewPoints(f, newPoints);
        prevFeatures.insert(prevFeatures.end(), newPoints.begin(), newPoints.end());
    }

    frames.push_back(f);
}

std::map<int, PointTrack> & PointTracker::getTracks() {
    return tracks;
}

void PointTracker::addNewPoints(FramePtr frame, std::vector<cv::Point2f> & points) {
    for(int i = 0; i < points.size(); i++) {
        int id = nextId++;
        PointTrack track;
        track.firstFrame = track.lastFrame = frameNumber;
		Point2fPtr temp = Point2fPtr(new cv::Point2f(points[i]));
        track.points.push_back(temp);
        tracks[id] = track;
        frame->points[id] = temp;
    }
}

