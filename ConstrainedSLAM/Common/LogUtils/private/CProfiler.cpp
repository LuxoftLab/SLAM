#include "Common/LogUtils/CProfiler.hpp"

#include <iostream>
#include <string>

CProfileManager & CProfiler::sProfileManager = CProfileManager::getInstance();

CProfiler::CProfiler(const char * file, const char * function) :
   mFile(file),
   mFunction(function),
   mStart(tClock::now())
{
}

CProfiler::~CProfiler()
{
   using boost::chrono::duration_cast;
   typedef CProfileManager::tTimeAccuracy tTimeAccuracy;
   tClock::duration mc = tClock::now() - mStart;
   tTimeAccuracy tmp = duration_cast<tTimeAccuracy>(mc);
   sProfileManager.addResult(mFile, mFunction, tmp.count());
}
