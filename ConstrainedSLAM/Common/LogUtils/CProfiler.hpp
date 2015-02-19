#ifndef C_PROFILER_H
#define C_PROFILER_H

#include <string>

#include <boost/chrono.hpp>

#include "private/CProfileManager.hpp"

#define _TO_STR(v) #v
#define TO_STR(v) _TO_STR(v)
#define START_PROFILING(var) CProfiler var(__FILE__ ":" TO_STR(__LINE__), __FUNCTION__)

class CProfiler {
   typedef boost::chrono::high_resolution_clock tClock;

   static CProfileManager & sProfileManager;

   const std::string mFile;
   const std::string mFunction;

   tClock::time_point mStart;

public:
   CProfiler(const char * file, const char * function);
   ~CProfiler();
};

#endif
