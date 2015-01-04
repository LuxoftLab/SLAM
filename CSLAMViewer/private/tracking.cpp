
#include <vector>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <PointTracker/PointTracker.h>
#include <Common/common.h>

int main() {
    cv::VideoCapture capture("/home/gorz/VID_20150114_111402"
                             ".mp4");
    if(!capture.isOpened()) {
        return 1;
    }
    cv::Mat frame;
    PointTracker tracker(cv::Size(21, 21), 5, 0, 50);
    SensorData s;
    std::vector<PointTrack> points;
    capture.grab();
    capture.retrieve(frame);
    cv::resize(frame, frame, cv::Size(800, 600));
    tracker.setFirstFrame(frame, points);
    std::cout << points.size() << std::endl;
    for(int i = 0; i < points.size(); i++) {
        cv::Point2f p = points[i].points[0];
        cv::circle(frame, p, 10, cv::Scalar(i*5, i*5, 0));
    }
    cv::imshow("video", frame);
    cv::waitKey(100);
    while(capture.grab()) {
        capture.retrieve(frame);
        cv::resize(frame, frame, cv::Size(800, 600));
        tracker.findNewFeaturePositions(frame, points, s);
        for(int i = 0; i < points.size(); i++) {
            for(int j = 0; j < points[i].points.size(); j++) {
                cv::Point2f p = points[i].points[j];
                cv::circle(frame, p, 10, cv::Scalar(i*5, i*5, 0));
                if(j) {
                    cv::line(frame, p, points[i].points[j-1], cv::Scalar(i*5, i*5, 0));
                }
            }
        }
        cv::imshow("video", frame);
        cv::waitKey(100);
    }
    return 0;
}
