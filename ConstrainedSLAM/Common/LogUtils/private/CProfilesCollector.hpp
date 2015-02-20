#ifndef C_PROFILE_MANAGER_H
#define C_PROFILE_MANAGER_H

#include <map>
#include <string>

#include <boost/chrono.hpp>

class CProfilesCollector {
public:
   typedef boost::chrono::microseconds tTimeAccuracy;
   typedef tTimeAccuracy::rep tTime;

private:
   struct Info {
      const char * mFunction;
      tTime mCallsNum;
      tTime mAllTime;
      tTime mMaxTime;
      tTime mMinTime;

      Info(const char * function, const tTime & time);
   };

   std::map<const char *, Info> mProfiles;

   CProfilesCollector();
   CProfilesCollector(const CProfilesCollector &);
   ~CProfilesCollector();
   const CProfilesCollector & operator=(const CProfilesCollector &);

public:
   static CProfilesCollector & getInstance();

   void addResult(const char * id, const char * function,
                  const tTime & time);
};

#endif
