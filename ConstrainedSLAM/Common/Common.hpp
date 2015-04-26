#ifndef COMMON_H
#define COMMON_H

#include <opencv2/opencv.hpp>
#include <list>
#include <map>
#include <boost/shared_ptr.hpp>



struct PointTrack {
   typedef boost::shared_ptr<cv::Point2f> tPoint2fPtr;
   std::list<tPoint2fPtr> points;
   int firstFrame, lastFrame;
};


struct SensorData {

};



#endif
