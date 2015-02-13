#ifndef C_PROFILER_H
#define C_PROFILER_H

#include <string>

#include <boost/chrono.hpp>

#define START_PROFILING(var) CProfiler var(__FILE__, __FUNCTION__, __LINE__)

class CProfiler {
   typedef boost::chrono::microseconds tMicroseconds;
   typedef boost::chrono::high_resolution_clock tClock;

   const std::string mFile;
   const std::string mFunction;
   const int mLine;

   tClock::time_point mStart;

public:
   CProfiler(const char * file, const char * function, const int line);
   ~CProfiler();
};

#endif
