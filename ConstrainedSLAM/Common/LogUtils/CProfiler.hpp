#ifndef C_PROFILER_H
#define C_PROFILER_H

#include <string>

#include <boost/chrono.hpp>

#include "private/CProfilesCollector.hpp"

#define _TO_STR(v) #v
#define TO_STR(v) _TO_STR(v)
#define START_PROFILING(var) CProfiler var(__FILE__ ":" TO_STR(__LINE__), __FUNCTION__)

class CProfiler {
   typedef boost::chrono::high_resolution_clock tClock;

   static CProfilesCollector & sProfilesCollector;

   const char * mFile;
   const char * mFunction;

   tClock::time_point mStart;

   CProfiler(const CProfiler &);
   const CProfiler & operator=(const CProfiler &);

public:
   CProfiler(const char * file, const char * function);
   ~CProfiler();
};

#endif
