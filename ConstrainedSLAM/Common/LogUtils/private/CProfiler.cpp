#include "Common/LogUtils/CProfiler.hpp"

#include <iostream>
#include <string>

CProfilesCollector & CProfiler::sProfilesCollector = CProfilesCollector::getInstance();

CProfiler::CProfiler(const char * file, const char * function,
                     const char * description) :
   mFile(file),
   mFunction(function),
   mName(description),
   mStart(tClock::now())
{
}

CProfiler::~CProfiler()
{
   tClock::duration duration = tClock::now() - mStart;

   CProfilesCollector::tTimeAccuracy microseconds =
      boost::chrono::duration_cast<CProfilesCollector::tTimeAccuracy>(duration);

   sProfilesCollector.addResult(mFile, mFunction, mName, microseconds.count());
}
