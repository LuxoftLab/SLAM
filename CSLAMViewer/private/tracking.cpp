
#include <map>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <list>
#include <PointTracker/CPointTracker.hpp>
#include <Common/Common.hpp>
#include "Common/LogUtils/Logger.hpp"


int main() {
   CVNAR_LOGGER_INIT
   CVNAR_LOGGER_SET(TO_CONSOLE)
   CVNAR_LOG(ERROR) << "yep";

   cv::VideoCapture capture("/home/gorz/VID_20150114_111402.mp4");
   if(!capture.isOpened()) {
      return 1;
   }
   cv::Mat frame, grayFrame;
   CPointTracker tracker(10, 49, 50);
   SensorData s;
   const IPointTracker::tPointTracks & tracks = tracker.getTracks();
   for(int i = 0; i < 3 && capture.grab(); i++)
   //while(capture.grab())
   {
      capture.retrieve(frame);
      cv::resize(frame, frame, cv::Size(800, 600));
      cv::cvtColor(frame, grayFrame, CV_BGR2GRAY);
      tracker.processFrame(frame, grayFrame, s);

      std::cout << "found tracks: " << tracks.size() << std::endl;
//      for(auto it = tracks.begin(); it != tracks.end(); it++)
//      {
//         for(auto itr = it->second.points.begin(); itr != it->second.points.end(); itr++)
//         {
//            cv::circle(frame, **itr, 10, cv::Scalar(it->first*5, it->first*5, 0));
//         }
//      }
//      cv::imshow("video", frame);
//      cv::waitKey();
   }
   capture.release();
   return 0;
}
