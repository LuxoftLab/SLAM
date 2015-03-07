
#include <map>
#include <list>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <ceres/ceres.h>
#include "PointTracker/CPointTracker.hpp"
#include "Common/Common.hpp"
#include "Common/LogUtils/CProfiler.hpp"


struct Functor {
   const cv::Point2f & point1;
   const cv::Point2f & point2;

   Functor(cv::Point2f p1, cv::Point2f p2) :
      point1(p1),
      point2(p2)
   {
   }

   /**
    * Describe equation to find fundamental matrix
    *
    * @param m - fundamental matrix
    */
   template <typename T> bool operator()(const T * const m, T * residual) const
   {
      T x1(point1.x);
      T y1(point1.y);
      T x2(point2.x);
      T y2(point2.y);
      residual[0] = x1 * x2 * m[0] + x1 * y2 * m[3] + x1 * m[6] +
                    y1 * x2 * m[1] + y1 * y2 * m[4] + y1 * m[7] +
                    x2 * m[2] + y2 * m[5] + m[8];
      return true;
   }
};

int main() {
   cv::VideoCapture capture("/home/gorz/VID_20150114_111402.mp4");
   if(!capture.isOpened()) {
      return 1;
   }
   cv::Mat frame, grayFrame;
   CPointTracker tracker(10, 49, 50);
   SensorData s;
   const IPointTracker::tPointTracks & tracks = tracker.getTracks();
   const IPointTracker::tFrames & frames = tracker.getFrames();
   for(int i = 0; i < 2 && capture.grab(); i++)
   {
      capture.retrieve(frame);
      cv::resize(frame, frame, cv::Size(800, 600));
      cv::cvtColor(frame, grayFrame, CV_BGR2GRAY);
      tracker.processFrame(frame, grayFrame, s);
   }
   capture.release();


   typedef ceres::AutoDiffCostFunction<Functor, 1, 9> tCostFunction;

   ceres::Problem problem;
   //initial value of fundamental matrix
   double fundamental[9] = {1000, 1000, 1000,
                            1000, 1000, 1000,
                            1000, 1000, 1000};
   for(auto it = tracks.begin(); it != tracks.end(); it++)
   {
      std::map<int, PointTrack::tPoint2fPtr> & points1 = frames[0]->points;
      auto p1 = points1.find(it->first);
      if(p1 == points1.end()) {
         continue;
      }
      std::map<int, PointTrack::tPoint2fPtr> & points2 = frames[1]->points;
      auto p2 = points2.find(it->first);
      if(p2 == points2.end()) {
         continue;
      }
      Functor * functor = new Functor(*(p1->second), *(p2->second));
      tCostFunction * function = new tCostFunction(functor);
      problem.AddResidualBlock(function, NULL, fundamental);
   }

   ceres::Solver::Options options;
   options.minimizer_progress_to_stdout = true;
   ceres::Solver::Summary summary;
   {
      START_PROFILING("fundamental");
      ceres::Solve(options, &problem, &summary);
   }

   std::cout << summary.BriefReport() << std::endl;
   for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
         std::cout << fundamental[3 * i + j] << ' ';
      }
      std::cout << std::endl;
   }
   return 0;
}
