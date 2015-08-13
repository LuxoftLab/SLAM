
#include <map>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <list>
#include <PointTracker/CPointTracker.hpp>
#include <Common/Common.hpp>


int main() {
   cv::VideoCapture capture("/home/getupandgo/Downloads/black2.mp4");
   if(!capture.isOpened()) {
      return 1;
   }
   cv::Mat frame, grayFrame;
   CPointTracker tracker(10, 49, 50);
   SensorData s;
   const IPointTracker::tPointTracks & tracks = tracker.getTracks();
   int frameCounter = 1;

   while(capture.grab())
   {
      capture.retrieve(frame);
      cv::resize(frame, frame, cv::Size(800, 600));
      cv::cvtColor(frame, grayFrame, CV_BGR2GRAY);
      tracker.processFrame(frame, grayFrame, s);

      std::cout << "found tracks: " << tracks.size() << std::endl;
      if(frameCounter > 1) {
          for(auto it = tracks.begin(); it != tracks.end(); it++)
          {
              //std::cout << it->second.points.size() << "\n";
             for(auto itr = it->second.points.begin(); itr != it->second.points.end(); itr++)
             {
                 int dx = it->second.lastFrame - it->second.firstFrame + 1;
                cv::circle(frame, **itr, 10,
                           //cv::Scalar(it->first*5, it->first*5, 0));
                           cv::Scalar(255 - dx*40,
                                      255,
                                      255));
                //std::cout << (**itr).x << " " << (**itr).y << "\n";
                //cv::imshow("video", frame);
             }
             //cv::waitKey();
          }
          std::cout << "frame " << frameCounter << "\n";
      }
      frameCounter++;
      cv::imshow("video", frame);
      cv::waitKey();
   }
   capture.release();
   return 0;
}
