#include "Common/LogUtils/CProfiler.hpp"

#include <iostream>

CProfiler::CProfiler(const char * file, const char * function, const int line) :
   mFile(file),
   mFunction(function),
   mLine(line),
   mStart(tClock::now())
{
}

CProfiler::~CProfiler()
{
   using boost::chrono::duration_cast;
   tClock::duration mc = tClock::now() - mStart;
   std::cout << std::endl << "Profile info:" << std::endl
             << "File: " << mFile << std::endl
             << "Function: " << mFunction << std::endl
             << "Profiling starts at line " << mLine << ": "
             << duration_cast<tMicroseconds>(mc) << std::endl << std::endl;
}
