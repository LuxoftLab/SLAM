
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
    FramePtr f(new Frame(this));
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
    FramePtr f(new Frame(this));
    std::map<int, PointTrack>::iterator it = tracks.begin();

    std::cout << "start update tracks"<< std::endl;
    for(int i = 0; i < features.size(); i++, it++) {
        while(it->second.lastFrame != frameNumber)
            it++;
        if(status[i]) {
			f->points[it->first] = Point2fPtr(new cv::Point2f);
            *(f->points[it->first]) = features[i];
            prevFeatures.push_back(features[i]);
            it->second.lastFrame++;
            it->second.points.push_back(features[i]);
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

void PointTracker::removeFrame(Frame * frame) {
    for(auto it = frame->points.begin(); it != frame->points.end(); it++) {
        PointTrack & track = tracks[it->first];
        if(track.points.size() == 1) {
            std::cout << "delete track: " << it->first << std::endl;
            tracks.erase(it->first);
        } else
            track.points.pop_front();
    }
}

void PointTracker::addNewPoints(FramePtr frame, std::vector<cv::Point2f> & points) {
    for(int i = 0; i < points.size(); i++) {
        int id = nextId++;
        PointTrack track;
        track.firstFrame = track.lastFrame = frameNumber;
        track.points.push_back(points[i]);
        tracks[id] = track;
		frame->points[id] = Point2fPtr(new cv::Point2f());
        *(frame->points[id]) = points[i];
    }
}

