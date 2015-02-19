#include <iostream>

#include "CProfileManager.hpp"

CProfileManager & CProfileManager::getInstance()
{
   static CProfileManager singleton;
   return singleton;
}

CProfileManager::Info::Info(const std::string &function, const tTime time) :
   mFunction(function),
   mCallsNum(1),
   mAverageTime(time),
   mMaxTime(time),
   mMinTime(time)
{
}

CProfileManager::CProfileManager()
{
}

CProfileManager::~CProfileManager()
{
   for(auto it = mProfiles.begin(); it != mProfiles.end(); it++)
   {
      Info & info = it->second;
      std::cout << std::endl
                << it->first << std::endl
                << "\tFunction: " << info.mFunction << std::endl
                << "\tNumber of calls: " << info.mCallsNum << std::endl
                << "\tAverage time: " << info.mAverageTime << " microseconds" << std::endl
                << "\tMax time: " << info.mMaxTime << " microseconds" << std::endl
                << "\tMin time: " << info.mMinTime << " microseconds" << std::endl;
   }
}

void CProfileManager::addResult(const std::string &id,
                                const std::string &function, const tTime time)
{
   auto it = mProfiles.find(id);
   if(it == mProfiles.end())
   {
      Info info(function, time);
      mProfiles.insert(std::pair<const std::string, Info>(id, info));
      return;
   }
   Info & info = it->second;
   //TODO change this code! Once there will be an overflow
   tTime callsNum = info.mCallsNum;
   info.mAverageTime = (info.mAverageTime * callsNum + time) / (callsNum + 1);
   info.mCallsNum++;

   if(info.mMaxTime < time)
   {
      info.mMaxTime = time;
   }
   else if(info.mMinTime > time)
   {
      info.mMinTime = time;
   }

}
