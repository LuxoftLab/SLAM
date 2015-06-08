#ifndef I_POINT_TRACKER_H
#define I_POINT_TRACKER_H

#include <opencv2/opencv.hpp>

#include "Common/Common.hpp"

class IPointTracker;
#include "Common/CFrame.hpp"

class IPointTracker {
public:
   typedef boost::shared_ptr<CFrame> tFramePtr;
   typedef boost::circular_buffer<tFramePtr> tFrames;
   typedef std::map<int, PointTrack>  tPointTracks;

   virtual void processFrame(const cv::Mat & img, const cv::Mat & grayImg,
                             const SensorData & sensors) = 0;

   virtual const tPointTracks & getTracks() const = 0;
   virtual const tFrames & getFrames() const = 0;
};

#endif
