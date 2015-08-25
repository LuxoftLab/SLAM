#include <iostream>

#include "PointTracker/CPointTracker.hpp"
#include "PointTracker/Tracker/CLKTracker.hpp"
#include "PointTracker/Tracker/CSteinTracker.hpp"

#include "Common/LogUtils/CProfiler.hpp"

#define DEBUG(v) std::cout << #v << " = " << v << "\n";

CPointTracker::CPointTracker(const int framesNumber, const size_t minPoints,
                             const int maxPoints) :
   mFrames(framesNumber),
   mMinPoints(minPoints),
   mFrameNumber(0),
   mNextId(0),
   mTracker(new CSteinTracker(maxPoints))
   //mTracker(new CLKTracker(maxPoints))
{

}

void CPointTracker::processFrame(const cv::Mat & img, const cv::Mat & grayImg,
                                 const SensorData & sensors)
{
   START_PROFILING(profiler);
   if(mFrameNumber == 0) {
      processFirstFrame(img, grayImg);
      return;
   }

   std::vector<cv::Point2f> features;
   std::vector<uchar> status;
   mTracker->findNewFeaturesPosition(img, grayImg, mPrevFeatures, features, status);

   std::cout << "mPrevFeatures.size() = "<<mPrevFeatures.size() << std::endl;
   std::cout << "features = "<< features.size() << std::endl;
   std::cout << "mTracks.size: " << mTracks.size() << "\n";

   mPrevFeatures.clear();
   tFramePtr frame(new CFrame(mTracks));
   auto it = mTracks.begin();


   std::cout << "start update tracks"<< std::endl;
   std::vector<int> deletions;

   int goodLastFrame = 0;
   int goodStatus = 0;
   for(; it != mTracks.end(); it++)
   {
       if(it->second.lastFrame == mFrameNumber)
           goodLastFrame++;
   }
   it = mTracks.begin();

   for(size_t i = 0; i < features.size(); i++, it++)
   {
      while(1)
      {
          if(it->second.lastFrame == mFrameNumber)
              break;
         it++;
      }
      if(status[i] != 0)
      {
         PointTrack::tPoint2fPtr temp(new cv::Point2f(features[i]));
         frame->points[it->first] = temp;
         mPrevFeatures.push_back(features[i]);
         it->second.lastFrame++;
         //std::cout << "push_back " << *temp << " to " << *(it->second.points.back()) << "\n";
         it->second.points.push_back(temp);
         goodStatus++;
      }
      else
      {
          if(it->second.points.size() == 1 && mFrameNumber > 2)
          {
             deletions.push_back(it->first);
          }
      }
   }
   DEBUG(goodLastFrame);
   DEBUG(goodStatus);
   DEBUG(deletions.size());
   for(auto del = deletions.begin(); del != deletions.end(); del++)
   {
       mTracks.erase(*del);
   }
   std::cout << "finish update tracks"<< std::endl;

   mFrameNumber++;

//   if(mPrevFeatures.size() < mMinPoints)
//   {
//      std::vector<cv::Point2f> newPoints;
//      mTracker->findNewFeatures(img, grayImg, newPoints, mPrevFeatures);
//      std::cout << "new points: " << newPoints.size() << std::endl;
//      addNewPoints(frame, newPoints);
//      mPrevFeatures.insert(mPrevFeatures.end(), newPoints.begin(), newPoints.end());
//   }

   mFrames.push_back(frame);
}

const IPointTracker::tPointTracks & CPointTracker::getTracks() const
{
   return mTracks;
}

const IPointTracker::tFrames & CPointTracker::getFrames() const
{
   return mFrames;
}

void CPointTracker::processFirstFrame(const cv::Mat & img, const cv::Mat & grayImg)
{
   mFrameNumber = 1;
   mTracker->setFirstFrame(img, grayImg, mPrevFeatures);

   std::cout << "found features: " << mPrevFeatures.size() << std::endl;
   tFramePtr frame(new CFrame(mTracks));
   addNewPoints(frame, mPrevFeatures);
   mFrames.push_back(frame);
}

void CPointTracker::addNewPoints(tFramePtr frame,
                                 const std::vector<cv::Point2f> & points)
{
   for(size_t i = 0; i < points.size(); i++)
   {
      int id = mNextId++;
      PointTrack track;
      track.firstFrame = mFrameNumber;
      track.lastFrame = mFrameNumber;
      PointTrack::tPoint2fPtr temp(new cv::Point2f(points[i]));
      track.points.push_back(temp);
      frame->points[id] = temp;
      mTracks[id] = track;
   }
}

