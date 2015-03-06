#include <iostream>

#include "CProfilesCollector.hpp"

CProfilesCollector & CProfilesCollector::getInstance()
{
   static CProfilesCollector singleton;
   return singleton;
}

CProfilesCollector::Info::Info(const char * function, const char * name,
                               const tTime & time) :
   mFunction(function),
   mName(name),
   mCallsNum(1),
   mAllTime(time),
   mMaxTime(time),
   mMinTime(time)
{
}

CProfilesCollector::CProfilesCollector()
{
}

CProfilesCollector::~CProfilesCollector()
{
   for(auto it = mProfiles.begin(); it != mProfiles.end(); it++)
   {
      Info & info = it->second;
      std::cout << std::endl
                << "Profiler: " << info.mName << std::endl
                << "\tFunction: " << info.mFunction << std::endl
                << "\tNumber of calls: " << info.mCallsNum << std::endl
                << "\tAverage time: " << info.mAllTime/info.mCallsNum
                << " microseconds" << std::endl
                << "\tMax time: " << info.mMaxTime
                << " microseconds" << std::endl
                << "\tMin time: " << info.mMinTime
                << " microseconds" << std::endl;
   }
}

void CProfilesCollector::addResult(const char * id, const char * function,
                                   const char * name, const tTime & time)
{
   auto it = mProfiles.find(id);
   if(it == mProfiles.end())
   {
      Info info(function, name, time);
      mProfiles.insert(std::pair<const char *, Info>(id, info));
      return;
   }
   Info & info = it->second;

   if(info.mMaxTime < time)
   {
      info.mMaxTime = time;
   }
   else if(info.mMinTime > time)
   {
      info.mMinTime = time;
   }

   //TODO change this code! Once there will be an overflow
   info.mAllTime += time;
   info.mCallsNum++;

   tTime avr = info.mAllTime/info.mCallsNum;
   if(avr < info.mMinTime || avr > info.mMaxTime)
   {
      std::cout << "Time overflow in profiler: " << id << std::endl;
   }

}
