
#include <map>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <list>
#include <PointTracker/PointTracker.h>
#include <Common/common.h>


int main() {
    cv::VideoCapture capture("/home/gorz/VID_20150114_111402.mp4");
    if(!capture.isOpened()) {
        return 1;
    }
    cv::Mat frame;
    PointTracker tracker(cv::Size(21, 21), 5, 49, 50);
    SensorData s;
    std::map<int, PointTrack> & tracks = tracker.getTracks();
    capture.grab();
    capture.retrieve(frame);
    cv::resize(frame, frame, cv::Size(800, 600));
    tracker.setFirstFrame(frame);
    std::cout << "before while" << std::endl;
    while(capture.grab()) {

        std::cout << "found tracks: " << tracks.size() << std::endl;
        for(auto it = tracks.begin(); it != tracks.end(); it++) {
            for(auto itr = it->second.points.begin(); itr != it->second.points.end(); itr++) {
                cv::circle(frame, **itr, 10, cv::Scalar(it->first*5, it->first*5, 0));
            }
        }
        std::cout << "before draw" << std::endl;
        cv::imshow("video", frame);
        cv::waitKey();

        capture.retrieve(frame);
        cv::resize(frame, frame, cv::Size(800, 600));
        tracker.findNewFeaturePositions(frame, s);
    }
    return 0;
}
