#ifndef C_POINT_TRACKER_H
#define C_POINT_TRACKER_H

#include <vector>
#include <map>

#include <boost/circular_buffer.hpp>
#include <boost/shared_ptr.hpp>

#include "Common/Common.hpp"
#include "Common/CFrame.hpp"
#include "IPointTracker.hpp"
#include "Tracker/ITracker.hpp"

class CPointTracker : public IPointTracker {
   int mFrameNumber;
   int mNextId;
   size_t mMinPoints;
   tPointTracks mTracks;
   tFrames mFrames;
   boost::shared_ptr<ITracker> mTracker;
   std::vector<cv::Point2f> mPrevFeatures;

   void processFirstFrame(const cv::Mat & img, const cv::Mat & grayImg);
   void addNewPoints(tFramePtr frame, const std::vector<cv::Point2f> & points);

public:
   CPointTracker(const int framesNumber, const size_t minPoints, const int maxPoints);

   void processFrame(const cv::Mat & img, const cv::Mat & grayImg,
                     const SensorData & sensors);

   const tPointTracks & getTracks() const;
   const tFrames & getFrames() const;
};

#endif
